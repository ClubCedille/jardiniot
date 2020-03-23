#ifndef ControllerFactory_H
#define ControllerFactory_H

#include <string.h>
#include "ControllerType.h"
#include "Controller.h"

/**
    Permet de créer des sensor et des moteurs de tout genre
*/
class ControllerFactory {
private:

public:
    ControllerFactory();
    ~ControllerFactory();

    SensorStrategy* createSensor(byte idController, ControllerType type, short delay, std::vector<short> inputPin, std::vector<short> outputPin);
    MotorStrategy* createMotor(byte idController, ControllerType type, short delay, std::vector<short> inputPin, std::vector<short> outputPin);
    Controller* createController(byte idController, ControllerType ctrlType, short delay, std::vector<short> inputPin, std::vector<short> outputPin);
};

#endif
