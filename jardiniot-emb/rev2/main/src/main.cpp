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
    unsigned char ESP_WIFI_SSID[32] = "SAS2020\0";
    unsigned char ESP_WIFI_PASS[64] = "29096820037102109822070104\0";
    wifi_access_point(NULL,NULL);
    Controller a();
}
