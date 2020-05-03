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
