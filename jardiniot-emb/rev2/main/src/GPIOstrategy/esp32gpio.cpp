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

#include "esp32gpio.hpp"
#include "driver/gpio.h"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"

#include <functional>
#include <iostream>

bool esp32gpio::initialize( ) {
    // Reset the inputs
    gpio_reset_pin( (gpio_num_t) CAPTEUR1 );
    gpio_reset_pin( (gpio_num_t) CAPTEUR2 );
    gpio_reset_pin( (gpio_num_t) CAPTEUR3 );
    gpio_reset_pin( (gpio_num_t) CAPTEUR4 );

    gpio_reset_pin( (gpio_num_t) BOUTON1 );
    gpio_reset_pin( (gpio_num_t) BOUTON2 );

    gpio_reset_pin( (gpio_num_t) ACTIONNEUR1 );
    gpio_reset_pin( (gpio_num_t) ACTIONNEUR2 );
    gpio_reset_pin( (gpio_num_t) ACTIONNEUR3 );
    gpio_reset_pin( (gpio_num_t) ACTIONNEUR4 );

    // ESP_ERROR_CHECK(    gpio_set_pull_mode(CAPTEUR1), )   );

    return false;
}

bool esp32gpio::read( int gpio ) { return false; }

int esp32gpio::read_analog( int gpio ) { return 0; }

bool esp32gpio::write( int gpio, bool state ) { return false; }

bool esp32gpio::write_analog( int gpio, int state ) { return false; }

bool attach_interrupt( int gpio, std::function<void( void )> ) { return false; }