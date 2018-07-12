// Copyright (C) 2018 Io Andes Daza-Dillon
//
// JardinIoT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JardinIoT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with JardinIoT.  If not, see <http://www.gnu.org/licenses/>.

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
