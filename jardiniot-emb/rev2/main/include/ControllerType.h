
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
#ifndef ControllerType_h
#define ControllerType_h

// ControllerType available
// ADAFRUIT_DHT = 0
// LED = 1
// A_LED = 2		(DEL sous le heatsink du capeau du bucket)
// SoilMoisture = 3
// FAN = 4
// VALVE = 5
enum ControllerType { ADAFRUIT_DHT, LED, A_LED, SoilMoisture, FAN, VALVE };

enum Type { Sensor, Motor, Both, UNDEF };

class ControllerTypeValidator {
public:
  static bool validateCtrlType( int typeId ) {
    if ( typeId >= 0 && typeId <= 5 ) {
      return true;
    }
    return false;
  }

  static Type getTypeFromController( ControllerType ctrType ) {
    if ( ctrType == ADAFRUIT_DHT || ctrType == LED || ctrType == A_LED ||
         ctrType == SoilMoisture ) {
      return Sensor;
    }
    if ( ctrType == FAN || ctrType == VALVE ) {
      return Motor;
    }
    return UNDEF;
  }
};

#endif