// https://www.arduino.cc/en/Reference/Serv
// https://github.com/arduino-libraries/Servo/blob/master/src/Servo.h

#ifndef SERVO_H
#define SERVO_H

#include "Arduino.h"

class Servo
{
public:
    Servo() {this->pin = 0;} // 0 n'étant pas une pin valide, attached() retournera false.
    uint8_t attach(int pin) {return this->pin = pin;}
    void write(int value) {std::cout << "Servo pin: " << pin << ". Angle set to : " << value << "°" << std::endl;}
    bool attached() {return this->pin;}

private:
    int pin;
};
#endif
