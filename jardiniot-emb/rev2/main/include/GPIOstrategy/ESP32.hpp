#ifndef ESP32GPIO
#define ESP32GPIO

#include "GPIOstrategy.hpp"

#include <functional>

/**
 * \class ESP32
 * This class abstracts the working of the GPIOS on the esp32 board. 
 * 
 */
class ESP32 : GPIOstrategy
{
    public:
    ESP32();
    ~ESP32();

    virtual bool initialize();
    virtual bool read(int gpio);
    virtual int read_analog(int gpio);
    virtual bool write(int gpio, bool state);
    virtual bool write_analog(int gpio, int state);
    virtual bool attach_interrupt(int gpio, std::function<void()>) = 0;

    private:
};

#endif