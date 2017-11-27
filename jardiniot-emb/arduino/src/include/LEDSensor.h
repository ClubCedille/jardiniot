#ifndef LEDSensor_H
#define LEDSensor_H

#include "SensorStrategy.h"
#include <Arduino.h>
#include <string.h>

class LEDSensor: public SensorStrategy {
private:
    byte LED_PIN;
public:
    LEDSensor(int idController, byte led_pin, int delay);
    ~LEDSensor();

    int read();
    int write();

    void on();
    void off();
    void blink();

    String getPin();
};

#endif
