#include "esp32gpio.hpp"
#include "driver/gpio.h"

#include <iostream>
#include <functional>

bool esp32gpio::initialize()
{
    //Reset the inputs 
    ESP_ERROR_CHECK(    gpio_reset_pin(CAPTEUR1)    );
    ESP_ERROR_CHECK(    gpio_reset_pin(CAPTEUR2)    );
    ESP_ERROR_CHECK(    gpio_reset_pin(CAPTEUR3)    );
    ESP_ERROR_CHECK(    gpio_reset_pin(CAPTEUR4)    );

    //Reset the dedicated boutons
    ESP_ERROR_CHECK(    gpio_reset_pin(BOUTON1)    );
    ESP_ERROR_CHECK(    gpio_reset_pin(BOUTON2)    );

    //Reset the dedicated outputs
    ESP_ERROR_CHECK(    gpio_reset_pin(ACTIONNEUR1)    );
    ESP_ERROR_CHECK(    gpio_reset_pin(ACTIONNEUR2)    );
    ESP_ERROR_CHECK(    gpio_reset_pin(ACTIONNEUR3)    );
    ESP_ERROR_CHECK(    gpio_reset_pin(ACTIONNEUR4)    );


    //ESP_ERROR_CHECK(    gpio_set_pull_mode(CAPTEUR1), )   );



    return false;
}

bool esp32gpio::read(int gpio)
{
    return false;
}

int esp32gpio::read_analog(int gpio) 
{
    return 0;
}

bool esp32gpio::write(int gpio, bool state)
{
    return false;
}

bool esp32gpio::write_analog(int gpio, int state) 
{
    return false;
}

bool attach_interrupt(int gpio, std::function<void(void)>)
{
    return false;
}