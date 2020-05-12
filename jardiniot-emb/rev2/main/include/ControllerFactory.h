  
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
#ifndef ControllerFactory_H
#define ControllerFactory_H

#include <string.h>
#include "ControllerType.h"
#include "Controller.h"
#include "ActuatorStrategy.hpp"
#include "SensorStrategy.hpp"

/**
    Permet de créer des sensor et des moteurs de tout genre
*/
class ControllerFactory {
private:

public:
    ControllerFactory();
    ~ControllerFactory();

    SensorStrategy* createSensor(unsigned char idController, ControllerType type, short delay, std::vector<short> inputPin, std::vector<short> outputPin);
    ActuatorStrategy* createMotor(unsigned char idController, ControllerType type, short delay, std::vector<short> inputPin, std::vector<short> outputPin);
    Controller* createController(unsigned char idController, ControllerType ctrlType, short delay, std::vector<short> inputPin, std::vector<short> outputPin);
};

#endif
