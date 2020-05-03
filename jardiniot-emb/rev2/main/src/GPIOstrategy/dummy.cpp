#include <dummy.hpp>

dummy::dummy()
{
    
}

dummy::~dummy()
{

}

bool dummy::initialize()
{
    return true;
}

bool dummy::read(int gpio)
{
    (void) gpio;
    return true;
}

int dummy::read_analog(int gpio)
{
    (void) gpio;
    return 255;
}

bool dummy::write(int gpio, bool state)
{
    (void) gpio;
    (void) state;
    return true;
}

bool dummy::write_analog(int gpio, int state)
{
    (void) gpio;
    (void) state;
    return true;
}