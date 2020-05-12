// Copyright (C) 2020      Vincent Perrier
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

#include "ControllerFactory.h"

#include "ControllerFactory.h"
//#include "include/sensor/DHTSensor.h"
//#include "include/sensor/LEDSensor.h"
//#include "include/sensor/A_LEDSensor.h"
//#include "include/motor/FanMotor.h"

//<<constructor>>
ControllerFactory::ControllerFactory( ) {}

//<<destructor>>
ControllerFactory::~ControllerFactory( ) { /*nothing to destruct*/
}

SensorStrategy *ControllerFactory::createSensor(
    unsigned char idController, ControllerType type, short delay,
    std::vector<short> inputPin, std::vector<short> outputPin ) {
  /* switch (type) {
       //DHT Sensor
       case ADAFRUIT_DHT:
           return new DHTSensor(idController, inputPin, outputPin, delay);
           break;
       // Simple LED
       case LED:
           return new LEDSensor(idController, inputPin, outputPin, delay);
           break;
       // Analogique LED
       case A_LED:
           return new A_LEDSensor(idController, inputPin, outputPin, delay);
           break;
       // Humidité du sol
       case SoilMoisture:
           // TODO
           break;
       //TODO Ajouter les autres
   }*/
  return NULL;
}

ActuatorStrategy *
ControllerFactory::createMotor( unsigned char idController, ControllerType type,
                                short delay, std::vector<short> inputPin,
                                std::vector<short> outputPin ) {
  /*switch (type) {
      // Fan
      case FAN:
          return new FanMotor(idController, inputPin, outputPin, delay);
          break;
      // Valve
      case VALVE:
          // TODO
          break;
      // //TODO Ajouter les autres
  }*/
  return NULL;
}

// Public method
Controller *ControllerFactory::createController(
    unsigned char idController, ControllerType ctrlType, short delay,
    std::vector<short> inputPin, std::vector<short> outputPin ) {

  Type type = ControllerTypeValidator::getTypeFromController( ctrlType );
  /*switch(type)
  {
      case Sensor: return createSensor(idController, ctrlType, delay, inputPin,
  outputPin);    break; case Motor: return createMotor(idController, ctrlType,
  delay, inputPin, outputPin); break; case Both: return NULL;
  //createSensorMotor(); break;
  }*/
  return NULL;
}