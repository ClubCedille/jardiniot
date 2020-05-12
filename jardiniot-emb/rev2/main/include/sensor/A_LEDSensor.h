  
// Copyright (C) 2017-2018 Alexandre-Xavier Labonté-Lamoureux
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
#ifndef A_LEDSensor_H
#define A_LEDSensor_H

#include "SensorStrategy.h"
#include <Arduino.h>
#include <string.h>

class A_LEDSensor: public SensorStrategy {
private:
    // Définition des pins
    unsigned char whiteLEDPin;
    unsigned char blueLEDPin;
    unsigned char redLEDPin;

    // Définition des valeurs par défaut
    unsigned char whiteValue = 255;
    unsigned char blueValue = 255;
    unsigned char redValue = 255;
public:
    A_LEDSensor(unsigned char idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay);
    ~A_LEDSensor();

    String read();
    int write();
    void setInput(std::vector<short> input);

    String toString();
};

#endif
