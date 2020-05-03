#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#ifdef __cplusplus
extern "C"{
#endif 

    //Fonction utilisé en premier lieu pour configurer le ESP32 en routeur pour la configuration.
    void wifi_access_point();

    //Fonctionn utilisé en deuxieme lieu pour connecter le ESP32 en client wifi
    // en utilisant les crédentiels obtenus avec wifi_access_point
    void wifi_station(char * SSID, char * pw);

#ifdef __cplusplus
}
#endif

#endif