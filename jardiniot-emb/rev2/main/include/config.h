/*
* Fichier contenant des macros pour la configuration du projet
*/

#ifndef CONFIG_H
#define CONFIG_H

#ifdef __cplusplus
extern "C"{
#endif 


    #define ESP_WIFI_SSID "EXEMPLESSID"
    #define ESP_WIFI_PASS "EXEMPLEPASSWD"

    void wifi_system_initialization();

#ifdef __cplusplus
}
#endif

#endif