#ifndef LEDSensor_H
#define LEDSensor_H

#include "SensorStrategy.h"
#include <Arduino.h>
#include <string.h>

class LEDSensor: public SensorStrategy {
private:
    int ledPin;
public:
    LEDSensor(int idController, std::vector<InputPin*> input, std::vector<int> output, int delay);
    ~LEDSensor();

    int read();
    int write();

    void on();
    void off();
    void blink();

    String toString();
};

#endif
