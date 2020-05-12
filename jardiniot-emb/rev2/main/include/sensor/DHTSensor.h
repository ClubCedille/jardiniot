  
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
#ifndef DHTSensor_H
#define DHTSensor_H

#include "SensorStrategy.hpp"
#include <string.h>
#include <stdlib.h> /* strtoul */

class DHTSensor: public SensorStrategy {
private:
    //DHT* dht;	// On pourrait surement faire que ce soit pas un pointeur
public:
    DHTSensor(unsigned char idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay);
    ~DHTSensor();

    std::string read();
    int write();

    std::string toString();
};

#endif
