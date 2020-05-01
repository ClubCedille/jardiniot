#include <iostream>

class GPIOstrategy
{
    public:
        virtual bool initialize() = 0;
        virtual bool read(int gpio) = 0;
        virtual int read_analog(int gpio) = 0;
        virtual bool write(int gpio, bool state) = 0;
        virtual bool write_analog(int gpio, int state) = 0;
};
