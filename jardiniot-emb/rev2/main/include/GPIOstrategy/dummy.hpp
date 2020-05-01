#include <GPIOstrategy.hpp>


class dummy : GPIOstrategy
{
    public:
        dummy();
        ~dummy();

        virtual bool initialize();
        virtual bool read(int gpio);
        virtual int read_analog(int gpio);
        virtual bool write(int gpio, bool state);
        virtual bool write_analog(int gpio, int state);

    private:
};