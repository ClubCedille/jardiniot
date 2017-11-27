#ifndef ControllerFactory_H
#define ControllerFactory_H

#include <Arduino.h>
#include <string.h>
#include "ControllerType.h"
#include "Controller.h"
#include "SensorStrategy.h"

class ControllerFactory {
private:
    // MotorStrategy* createMotor();
public:
    ControllerFactory();
    ~ControllerFactory();

    SensorStrategy* createSensor(int idController, ControllerType type, int delay, std::vector<int> outputPin, std::vector<int> inputPin);
    Controller* createController(int idController, ControllerType ctrlType, int delay, std::vector<int> outputPin, std::vector<int> inputPin);
};

#endif
