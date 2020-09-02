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

#ifndef LEDSensor_H
#define LEDSensor_H

#include "SensorStrategy.h"
#include <Arduino.h>
#include <string.h>

class LEDSensor : public SensorStrategy
{
  private:
    byte ledPin;

  public:
    LEDSensor(byte idController, std::vector<short> input, std::vector<short> output, short delay);
    ~LEDSensor();

    String read();
    int write();

    void on();
    void off();
    void blink();

    String toString();
};

#endif
