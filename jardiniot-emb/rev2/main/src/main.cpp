#include "system_init.h"
#include "CommandManager.hpp"

#include <iostream>
#include <vector>

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
    wifi_system_initialization();

}
