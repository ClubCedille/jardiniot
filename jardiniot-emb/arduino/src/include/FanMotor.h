#ifndef FanMotor_H
#define FanMotor_H

#include "MotorStrategy.h"
#include <Arduino.h>
#include <string.h>

class FanMotor: public MotorStrategy {
private:
    int fanPin;
    int fanSpeed;
public:
    // constructor
    FanMotor();
    FanMotor(int idController, int pin, int speed);
    ~FanMotor();

    void reset();

    // Méthode hérité de la classe MotorStrategy
    int activate();
    int stop();
};

#endif
