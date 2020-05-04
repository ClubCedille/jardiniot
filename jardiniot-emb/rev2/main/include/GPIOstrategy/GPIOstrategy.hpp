#ifndef GPIOSTRATEGY_H
#define GPIOSTRATEGY_H

#include <iostream>
#include <functional>
class GPIOstrategy
{
    public:
        virtual ~GPIOstrategy() = 0;
        virtual bool initialize() = 0;
        virtual bool read(int gpio) = 0;
        virtual int read_analog(int gpio) = 0;
        virtual bool write(int gpio, bool state) = 0;
        virtual bool write_analog(int gpio, int state) = 0;
        virtual bool attach_interrupt(int gpio, std::function<void(void)>) = 0;
};

#endif