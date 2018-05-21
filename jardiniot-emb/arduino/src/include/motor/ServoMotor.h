#ifndef ServoMotor_H
#define ServoMotor_H

#include "include/PreprocessorConstants.h"

#include "MotorStrategy.h"
#ifdef Arduino
    #include <Arduino.h>
#elif defined Pc
    #include "include/arduinoEmulator/Arduino.h"
#endif
#include <string.h>
#ifdef Arduino
    #include <Servo.h>
#elif defined Pc
    #include "include/arduinoEmulator/Servo.h"
#endif

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
