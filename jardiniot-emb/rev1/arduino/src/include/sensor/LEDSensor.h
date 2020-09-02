#ifndef LEDSensor_H
#define LEDSensor_H

#include "SensorStrategy.h"
#include <Arduino.h>
#include <string.h>

class LEDSensor : public SensorStrategy
{
  private:
    byte ledPin;

  public:
    LEDSensor(byte idController, std::vector<short> input, std::vector<short> output, short delay);
    ~LEDSensor();

    String read();
    int write();

    void on();
    void off();
    void blink();

    String toString();
};

#endif
