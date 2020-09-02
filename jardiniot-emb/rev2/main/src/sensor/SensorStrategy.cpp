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

#include "SensorStrategy.hpp" //include the declaration for this class
#include "GPIOstrategy.hpp"

//<<constructor>>
SensorStrategy::SensorStrategy(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin,
                               GPIOstrategy* board)
    : Controller(idController, type, inputPin, outputPin, board)
{
}

SensorStrategy::SensorStrategy()
{
}

//<<destructor>>
SensorStrategy::~SensorStrategy()
{
}

void SensorStrategy::modify(JardinCommand& jCommand)
{
    this->setInput(jCommand.getInputPin());
    this->delayTime = jCommand.getDelay();
}

void SensorStrategy::setDelayTime(short delayTime)
{
    this->delayTime = delayTime;
}

std::string SensorStrategy::read()
{
    return "";
}

int SensorStrategy::write()
{
    return 0;
}

void SensorStrategy::setInput(std::vector<short> input)
{
    this->inputPin.clear();
    this->inputPin = input;
}

std::string SensorStrategy::toString()
{
    return "";
}