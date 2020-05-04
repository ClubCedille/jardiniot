#include "esp32gpio.hpp"
#include "driver/gpio.h"

#include <iostream>
#include <functional>

bool esp32gpio::initialize()
{
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