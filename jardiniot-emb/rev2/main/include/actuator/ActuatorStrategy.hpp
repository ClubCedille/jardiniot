  
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


#ifndef MotorStrategy_H
#define MotorStrategy_H

#include <iostream>

#include "Controller.h"
#include "JardinCommand.h"
#include "GPIOstrategy.hpp"

/**
    Définit le comportement de base pour les moteurs
*/
class ActuatorStrategy: public Controller {
protected:
    short delayTime;
public:
    virtual short activate();
    virtual short stop();

    // constructor
    ActuatorStrategy();
    ActuatorStrategy(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin, GPIOstrategy * board);
    ActuatorStrategy(unsigned char idController, ControllerType type, short output, short input, GPIOstrategy * board);
    virtual ~ActuatorStrategy();

    void setDelayTime(short delayTime);
    void modify(JardinCommand &jCommand);
    virtual void setInput(std::vector<short> input);
};

#endif
