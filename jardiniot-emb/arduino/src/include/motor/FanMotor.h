#ifndef FanMotor_H
#define FanMotor_H

#include "include/PreprocessorConstants.h"

#include "MotorStrategy.h"
#ifdef Arduino
    #include <Arduino.h>
#elif defined Pc
    #include "include/arduinoEmulator/Arduino.h"
#endif
#include <string.h>

class FanMotor: public MotorStrategy {
private:
    byte fanPin;
    byte fanSpeed;
public:
    // constructor
    FanMotor();
    FanMotor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay);
    ~FanMotor();

    void reset();

    // Méthode hérité de la classe MotorStrategy
    short activate();
    short stop();

    void setInput(std::vector<short> inputPins);
};

#endif
