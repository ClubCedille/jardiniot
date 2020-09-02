// Copyright (C) 2020      Vincent Perrier
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

#include "Controller.h"
#include <iostream>
#include <string>

//<<constructor>>
Controller::Controller()
{
}

Controller::Controller(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin,
                       GPIOstrategy* board)
{
    this->idController = idController;
    this->inputPin = inputPin;
    this->outputPin = outputPin;
    this->type = type;
    this->GPIODevice = board;
}

//<<destructor>>
Controller::~Controller()
{
    this->inputPin.clear();
    this->outputPin.clear();
}

std::string Controller::getName()
{
    std::string ctrlName;
    switch (this->type)
    {
    case ADAFRUIT_DHT:
        ctrlName = "DHT";
        break;
    case LED:
        ctrlName = "LED";
        break;
    case A_LED:
        ctrlName = "A_LED";
        break;
    case SoilMoisture:
        ctrlName = "SoilMoisture";
        break;
    case FAN:
        ctrlName = "FAN";
        break;
    case VALVE:
        ctrlName = "VALVE";
        break;
    }
    return ctrlName;
}

unsigned char Controller::getIdController()
{
    return this->idController;
}

ControllerType Controller::getControllerType()
{
    return this->type;
}

void Controller::setStrategy(GPIOstrategy* newDevice)
{
    delete this->GPIODevice;
    this->GPIODevice = newDevice;
}