#ifndef ServoMotor_H
#define ServoMotor_H

#include "ActuatorStrategy.h"
#include <string>

class ServoMotor: public ActuatorStrategy {
private:
    unsigned char servoPin;
    //Servo servo;
    short delayTime = 1000;
public:
    // constructor
    ServoMotor();
    ServoMotor(unsigned char idController, unsigned char pin);
    ~ServoMotor();

    void reset();

    // Méthode hérité de la classe MotorStrategy
    short activate();
    short stop();

    bool isAttached();
};

#endif
