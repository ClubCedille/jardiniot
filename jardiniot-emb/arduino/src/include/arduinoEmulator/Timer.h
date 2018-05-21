//https://github.com/JChristensen/Timer/blob/master/Timer.h
#ifndef Timer_h
#define Timer_h

#include <inttypes.h>

class Timer
{

public:
    Timer(void) {};
    int8_t every(unsigned long period, void (*callback)(void)) {};
    void update(void) {};

};

#endif
