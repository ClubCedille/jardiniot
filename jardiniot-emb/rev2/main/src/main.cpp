#include "system_init.h"

#include <iostream>


#include <string.h>
#include <sys/param.h>


extern "C" {
	void app_main(void);
}




void app_main(void)
{
    //systemInit();
    wifi_system_initialization();

}
