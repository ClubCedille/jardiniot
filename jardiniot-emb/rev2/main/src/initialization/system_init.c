// Copyright (C) 2020   Vincent Perrier
//
// JardinIoT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JardinIoT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with JardinIoT.  If not, see <http://www.gnu.org/licenses/>.

#include "system_init.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include <string.h>

#include "lwip/err.h"
#include "lwip/sys.h"

#include "lwip/def.h"
#include "lwip/opt.h"

#include "tcpip_adapter.h"

#include <netinet/in.h>
#include <sys/socket.h>

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about
 * two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
#define CONFIG_ESP_MAXIMUM_RETRY 5

static const char *TAG = "wifi client";

static int s_retry_num = 0;

static void event_handler_sta( void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data ) {
    if ( event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START ) {
        esp_wifi_connect( );
    } else if ( event_base == WIFI_EVENT &&
                event_id == WIFI_EVENT_STA_DISCONNECTED ) {
        if ( s_retry_num < CONFIG_ESP_MAXIMUM_RETRY ) {
            esp_wifi_connect( );
            s_retry_num++;
            ESP_LOGI( TAG, "retry to connect to the AP" );
        } else {
            xEventGroupSetBits( s_wifi_event_group, WIFI_FAIL_BIT );
        }
        ESP_LOGI( TAG, "connect to the AP fail" );
    } else if ( event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP ) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        ESP_LOGI( TAG, "got ip:%s", ip4addr_ntoa( &event->ip_info.ip ) );
        s_retry_num = 0;
        xEventGroupSetBits( s_wifi_event_group, WIFI_CONNECTED_BIT );
    }
}

void wifi_init_as_station( char *SSID, char *pw ) {
    // Shutdown the accespoint interface and make space for the station mode
    ESP_ERROR_CHECK( esp_wifi_deauth_sta( 0 ) );
    ESP_ERROR_CHECK( esp_wifi_stop( ) );
    ESP_ERROR_CHECK( esp_wifi_deinit( ) );

    s_wifi_event_group = xEventGroupCreate( );
    tcpip_adapter_init( );

    // ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT( );
    ESP_ERROR_CHECK( esp_wifi_init( &cfg ) );

    ESP_ERROR_CHECK( esp_event_handler_register( WIFI_EVENT, ESP_EVENT_ANY_ID,
                                                 &event_handler_sta, NULL ) );
    ESP_ERROR_CHECK( esp_event_handler_register( IP_EVENT, IP_EVENT_STA_GOT_IP,
                                                 &event_handler_sta, NULL ) );

    wifi_config_t wifi_config = { };
    strcpy( (char *) wifi_config.sta.ssid, (char *) SSID );
    strcpy( (char *) wifi_config.sta.password, (char *) pw );

    ESP_ERROR_CHECK( esp_wifi_set_mode( WIFI_MODE_STA ) );
    ESP_ERROR_CHECK( esp_wifi_set_config( ESP_IF_WIFI_STA, &wifi_config ) );
    ESP_ERROR_CHECK( esp_wifi_start( ) );

    ESP_LOGI( TAG, "wifi_init_sta finished." );

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT)
     * or connection failed for the maximum number of re-tries (WIFI_FAIL_BIT).
     * The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits( s_wifi_event_group,
                                            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                            pdFALSE, pdFALSE, portMAX_DELAY );

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we
     * can test which event actually happened. */
    if ( bits & WIFI_CONNECTED_BIT ) {
        ESP_LOGI( TAG, "connected to ap SSID:%s password:%s", SSID, pw );
    } else if ( bits & WIFI_FAIL_BIT ) {
        ESP_LOGI( TAG, "Failed to connect to SSID:%s, password:%s", SSID, pw );
    } else {
        ESP_LOGE( TAG, "UNEXPECTED EVENT" );
    }

    ESP_ERROR_CHECK( esp_event_handler_unregister(
        IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler_sta ) );
    ESP_ERROR_CHECK( esp_event_handler_unregister( WIFI_EVENT, ESP_EVENT_ANY_ID,
                                                   &event_handler_sta ) );
    vEventGroupDelete( s_wifi_event_group );
}

void wifi_station( char *SSID, char *pw ) {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init( );
    if ( ret == ESP_ERR_NVS_NO_FREE_PAGES ||
         ret == ESP_ERR_NVS_NEW_VERSION_FOUND ) {
        ESP_ERROR_CHECK( nvs_flash_erase( ) );
        ret = nvs_flash_init( );
    }
    ESP_ERROR_CHECK( ret );

    ESP_LOGI( TAG, "ESP_WIFI_MODE_STA" );
    wifi_init_as_station( SSID, pw );
}

#define EXAMPLE_ESP_WIFI_SSID "Configure me"
#define EXAMPLE_ESP_WIFI_PASS "12345678"
#define EXAMPLE_ESP_WIFI_CHANNEL 1
#define EXAMPLE_MAX_STA_CONN 4

static const char *TAG2 = "wifi softAP";

static void wifi_event_handler( void *arg, esp_event_base_t event_base,
                                int32_t event_id, void *event_data ) {
    if ( event_id == WIFI_EVENT_AP_STACONNECTED ) {
        wifi_event_ap_staconnected_t *event =
            (wifi_event_ap_staconnected_t *) event_data;
        ESP_LOGI( TAG2, "station " MACSTR " join, AID=%d",
                  MAC2STR( event->mac ), event->aid );
    } else if ( event_id == WIFI_EVENT_AP_STADISCONNECTED ) {
        wifi_event_ap_stadisconnected_t *event =
            (wifi_event_ap_stadisconnected_t *) event_data;
        ESP_LOGI( TAG2, "station " MACSTR " leave, AID=%d",
                  MAC2STR( event->mac ), event->aid );
    }
}

void wifi_init_softap( void ) {
    tcpip_adapter_init( );
    ESP_ERROR_CHECK( esp_event_loop_create_default( ) );

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT( );
    ESP_ERROR_CHECK( esp_wifi_init( &cfg ) );

    ESP_ERROR_CHECK( esp_event_handler_register( WIFI_EVENT, ESP_EVENT_ANY_ID,
                                                 &wifi_event_handler, NULL ) );

    wifi_config_t wifi_config = {
        .ap = { .ssid = EXAMPLE_ESP_WIFI_SSID,
                .ssid_len = strlen( EXAMPLE_ESP_WIFI_SSID ),
                .password = EXAMPLE_ESP_WIFI_PASS,
                .max_connection = EXAMPLE_MAX_STA_CONN,
                .authmode = WIFI_AUTH_WPA_WPA2_PSK },
    };
    if ( strlen( EXAMPLE_ESP_WIFI_PASS ) == 0 ) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK( esp_wifi_set_mode( WIFI_MODE_AP ) );
    ESP_ERROR_CHECK( esp_wifi_set_config( ESP_IF_WIFI_AP, &wifi_config ) );
    ESP_ERROR_CHECK( esp_wifi_start( ) );

    ESP_LOGI( TAG2, "wifi_init_softap finished. SSID:%s password:%s",
              EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS );
}

void wifi_access_point( ) {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init( );
    if ( ret == ESP_ERR_NVS_NO_FREE_PAGES ||
         ret == ESP_ERR_NVS_NEW_VERSION_FOUND ) {
        ESP_ERROR_CHECK( nvs_flash_erase( ) );
        ret = nvs_flash_init( );
    }
    ESP_ERROR_CHECK( ret );

    ESP_LOGI( TAG2, "ESP_WIFI_MODE_AP" );
    wifi_init_softap( );
}
/*
void configureIP(unsigned char SSID[32], unsigned char pw[64])
{
    #define PORT 80
    int new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};


    char *hello = "<h1>Hello from server</h1>";
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    if (listen(sockfd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(sockfd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);
    printf(buffer);
    send(new_socket , hello , strlen(hello) , 0 );
    printf("<h1>Hello message sent</h1>");
}*/