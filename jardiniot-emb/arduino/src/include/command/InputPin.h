#ifndef InputPin_H
#define InputPin_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <string.h>

class InputPin {
private:
    int pin;
    int value;
public:
    InputPin();
    InputPin(int pin, int val);
    ~InputPin();

    int getPin();
    int getValue();

    String toString();
};

#endif
