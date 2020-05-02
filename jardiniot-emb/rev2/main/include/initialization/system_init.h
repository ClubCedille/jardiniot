#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#ifdef __cplusplus
extern "C"{
#endif 

    #include "config.h"

    void wifi_system_initialization(char SSID[32], char pw[64]);

#ifdef __cplusplus
}
#endif

#endif