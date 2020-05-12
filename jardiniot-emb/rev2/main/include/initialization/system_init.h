  
// Copyright (C) 2020   Vincent Perrier
//
// JardinIoT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JardinIoT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with JardinIoT.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#ifdef __cplusplus
extern "C"{
#endif 

    //Fonction utilisé en premier lieu pour configurer le ESP32 en routeur pour la configuration.
    void wifi_access_point();

    //Fonctionn utilisé en deuxieme lieu pour connecter le ESP32 en client wifi
    // en utilisant les crédentiels obtenus avec wifi_access_point
    void wifi_station(char *SSID, char *pw);

#ifdef __cplusplus
}
#endif

#endif