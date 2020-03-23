#include "system_init.h"

#include <string.h>
#include <sys/param.h>
/* #include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>
*/

extern "C" {
	void app_main(void);
}

void app_main(void)
{
    //systemInit();
    wifi_system_initialization();

    //vTaskDelay(4000 / portTICK_PERIOD_MS);
    
}
