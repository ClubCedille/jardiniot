#include "system_init.h"
#include "CommandManager.hpp"
#include "Controller.h"
#include "dummy.hpp"

#include <iostream>
#include <vector>
#include "config.h"

/*
*   Le point d'entré dans un programme ESP-IDF 
*   est la routine "app_main". Cette routine doit être
*   appellée avec un liage en C.
*/
extern "C" {
	void app_main(void);
}



/*
*   Point d'entré d'un logiciel ESP-IDF
*/
void app_main(void)
{
    char ESP_WIFI_SSID[32] = "test";
    char ESP_WIFI_PASS[64] = "test";
    wifi_system_initialization(ESP_WIFI_SSID, ESP_WIFI_PASS);
    Controller a();
}
