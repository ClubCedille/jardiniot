#ifndef ServoMotor_H
#define ServoMotor_H

#include "MotorStrategy.h"
#include <Arduino.h>
#include <string.h>
#include <Servo.h>

class ServoMotor: public MotorStrategy {
private:
    byte servoPin;
    Servo servo;
    short delayTime = 1000;
public:
    // constructor
    ServoMotor();
    ServoMotor(byte idController, byte pin);
    ~ServoMotor();

    void reset();

    // Méthode hérité de la classe MotorStrategy
    short activate();
    short stop();

    bool isAttached();
};

#endif
