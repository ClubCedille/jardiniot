#include "system_init.h"
#include "CommandManager.hpp"

#include <iostream>
#include <vector>
#include <sys/param.h>


extern "C" {
	void app_main(void);
}




void app_main(void)
{
    //systemInit();
    wifi_system_initialization();

}
