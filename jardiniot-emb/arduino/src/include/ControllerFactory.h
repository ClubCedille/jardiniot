#ifndef ControllerFactory_H
#define ControllerFactory_H

#include <Arduino.h>
#include <string.h>
#include "ControllerType.h"
#include "Controller.h"
#include "sensor/SensorStrategy.h"
#include "motor/MotorStrategy.h"

class ControllerFactory {
private:

public:
    ControllerFactory();
    ~ControllerFactory();

    SensorStrategy* createSensor(int idController, ControllerType type, int delay, std::vector<InputPin*> inputPin, std::vector<int> outputPin);
    MotorStrategy* createMotor(int idController, ControllerType type, int delay, std::vector<InputPin*> inputPin, std::vector<int> outputPin);
    Controller* createController(int idController, ControllerType ctrlType, int delay, std::vector<InputPin*> inputPin, std::vector<int> outputPin);
};

#endif
