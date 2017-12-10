#ifndef A_LEDSensor_H
#define A_LEDSensor_H

#include "SensorStrategy.h"
#include <Arduino.h>
#include <string.h>

class A_LEDSensor: public SensorStrategy {
private:
    int whiteLEDPin;
    int blueLEDPin;
    int redLEDPin;

    int whiteValue = 255;
    int blueValue = 255;
    int redValue = 255;
public:
    A_LEDSensor(int idController, std::vector<InputPin*> inputPins, std::vector<int> outputPins, int delay);
    ~A_LEDSensor();

    int read();
    int write();
    void setInput(std::vector<InputPin*> input);

    String toString();
};

#endif
