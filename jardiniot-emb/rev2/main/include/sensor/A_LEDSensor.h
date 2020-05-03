#ifndef A_LEDSensor_H
#define A_LEDSensor_H

#include "SensorStrategy.h"
#include <Arduino.h>
#include <string.h>

class A_LEDSensor: public SensorStrategy {
private:
    // Définition des pins
    unsigned char whiteLEDPin;
    unsigned char blueLEDPin;
    unsigned char redLEDPin;

    // Définition des valeurs par défaut
    unsigned char whiteValue = 255;
    unsigned char blueValue = 255;
    unsigned char redValue = 255;
public:
    A_LEDSensor(unsigned char idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay);
    ~A_LEDSensor();

    String read();
    int write();
    void setInput(std::vector<short> input);

    String toString();
};

#endif
