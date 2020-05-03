#include "ESP32.hpp"
#include "driver/gpio.h"
 

bool ESP32::initialize()
{

}

bool ESP32::read(int GPIO)
{
    return gpio_get_level(GPIO);
}

int ESP32::read_analog(int gpio)
{

}

bool ESP32::write(int gpio, bool state)
{

}

bool ESP32::write_analog(int gpio, int state)
{
    
}

bool ESP32::attach_interrupt(int gpio, std::function<void(void)>)
{

}