// Copyright (C) 2020      Vincent Perrier
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

#include "CommandManager.hpp"
#include "Controller.h"
#include "dummy.hpp"
#include "system_init.h"

#include "config.h"
#include "webConf.hpp"
#include <iostream>
#include <vector>

/*
 *   Le point d'entré dans un programme ESP-IDF
 *   est la routine "app_main". Cette routine doit être
 *   appellée avec un liage en C.
 */
extern "C" {
void app_main( void );
}

/*
 *   Point d'entré d'un logiciel ESP-IDF
 */
void app_main( void ) {
    wifi_access_point( );
    webConf *conf = new webConf( );

    conf->configure( 80 );

    wifi_station( (char *) conf->getSSID( ).c_str( ),
                  (char *) conf->getWifiPw( ).c_str( ) );

    Controller a( );
}
