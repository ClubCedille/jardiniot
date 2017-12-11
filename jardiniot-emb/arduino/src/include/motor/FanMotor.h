#ifndef FanMotor_H
#define FanMotor_H

#include "MotorStrategy.h"
#include <Arduino.h>
#include <string.h>

class FanMotor: public MotorStrategy {
private:
    byte fanPin;
    byte fanSpeed;
public:
    // constructor
    FanMotor();
    FanMotor(byte idController, std::vector<short> input);
    ~FanMotor();

    void reset();

    // Méthode hérité de la classe MotorStrategy
    int activate();
    int stop();
};

#endif
