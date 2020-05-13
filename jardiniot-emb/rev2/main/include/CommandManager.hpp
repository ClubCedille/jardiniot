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
#ifndef CONFIG_H
#define CONFIG_H

#include "ActuatorStrategy.hpp"
#include "SensorStrategy.hpp"
#include <iostream>
#include <vector>

class CommandManager {
  public:
    CommandManager( );
    ~CommandManager( );

    std::string executeCommand( );

    std::vector<SensorStrategy> getSensorList( );
    std::vector<ActuatorStrategy> getActuatorList( );

  private:
};

#endif