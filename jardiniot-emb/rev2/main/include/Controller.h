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
#ifndef Controller_H
#define Controller_H

#include "ControllerType.h"
#include "GPIOstrategy/GPIOstrategy.hpp"
#include "GPIOstrategy/dummy.hpp"
#include <string>
#include <vector>

/**
    Représente un controller de n'importe quel type
*/
class Controller
{
  private:
    unsigned char idController;
    ControllerType type;
    GPIOstrategy* GPIODevice = nullptr;

  protected:
    // Utilisation de short (16 bit) pour obtenir le pin ainsi que la valeur
    // Pin sur les 8 derniers bits
    // Valeur sur les 8 premiers
    std::vector<short> outputPin;
    std::vector<short> inputPin;

  public:
    Controller();
    Controller(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin, GPIOstrategy* board);
    virtual ~Controller();
    std::string getName();

    void setStrategy(GPIOstrategy* newDevice);

    virtual unsigned char getIdController();
    virtual ControllerType getControllerType();
};

#endif