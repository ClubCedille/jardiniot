#ifndef A_LEDSensor_H
#define A_LEDSensor_H

#include "include/PreprocessorConstants.h"

#include "SensorStrategy.h"
#ifdef Arduino
    #include <Arduino.h>
#elif defined Pc
    #include "include/arduinoEmulator/Arduino.h"
#endif
#include <string.h>

class A_LEDSensor: public SensorStrategy {
private:
    // Définition des pins
    byte whiteLEDPin;
    byte blueLEDPin;
    byte redLEDPin;

    // Définition des valeurs par défaut
    byte whiteValue = 255;
    byte blueValue = 255;
    byte redValue = 255;
public:
    A_LEDSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay);
    ~A_LEDSensor();

    char* read();
    int write();
    void setInput(std::vector<short> input);

    String toString();
};

#endif
