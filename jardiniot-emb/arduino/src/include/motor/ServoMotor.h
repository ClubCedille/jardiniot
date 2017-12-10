#ifndef ServoMotor_H
#define ServoMotor_H

#include "MotorStrategy.h"
#include <Arduino.h>
#include <string.h>
#include <Servo.h>

class ServoMotor: public MotorStrategy {
private:
    int servoPin;
    Servo servo;
    int delayTime = 1000;
public:
    // constructor
    ServoMotor();
    ServoMotor(int idController, int pin);
    ~ServoMotor();

    void reset();

    // Méthode hérité de la classe MotorStrategy
    int activate();
    int stop();

    bool isAttached();
};

#endif
