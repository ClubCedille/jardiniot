// Copyright (C) 2016-2018 Alexandre-Xavier Labonté-Lamoureux
// Copyright (C) 2017      Alexandre Brochu
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

#ifndef ServoMotor_H
#define ServoMotor_H

#include "ActuatorStrategy.h"
#include <string>

class ServoMotor : public ActuatorStrategy
{
  private:
    unsigned char servoPin;
    // Servo servo;
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
