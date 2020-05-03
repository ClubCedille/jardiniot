#include "system_init.h"
#include "CommandManager.hpp"
#include "Controller.h"
#include "dummy.hpp"

#include <iostream>
#include <vector>
#include "config.h"
#include "webConf.hpp"

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
    wifi_access_point();
    webConf * conf = new webConf();

    conf->configure(80);

    wifi_station((char *)conf->getSSID().c_str(), (char *)conf->getWifiPw().c_str());

    Controller a();
}
