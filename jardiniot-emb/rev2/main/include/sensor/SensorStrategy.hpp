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

#ifndef SensorStrategy_H
#define SensorStrategy_H

#include <iostream>
#include <vector>

#include "Controller.h"
#include "ControllerType.h"
#include "GPIOstrategy.hpp"
#include "JardinCommand.h"

/**
    Définit le comportement de base pour les senseurs
*/
class SensorStrategy : public Controller {
  protected:
    short delayTime;

  public:
    virtual std::string read( );
    virtual int write( );
    virtual std::string toString( );
    virtual void setInput( std::vector<short> inputPin );

    // constructor
    SensorStrategy( );
    SensorStrategy( unsigned char idController, ControllerType type,
                    std::vector<short> inputPin, std::vector<short> outputPin,
                    GPIOstrategy *board );
    virtual ~SensorStrategy( );

    void setDelayTime( short delayTime );
    void modify( JardinCommand &jCommand );
};

#endif