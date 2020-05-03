#ifndef MotorStrategy_H
#define MotorStrategy_H

#include <iostream>

#include "Controller.h"
#include "JardinCommand.h"
#include "GPIOstrategy.hpp"

/**
    Définit le comportement de base pour les moteurs
*/
class ActuatorStrategy: public Controller {
protected:
    short delayTime;
public:
    virtual short activate();
    virtual short stop();

    // constructor
    ActuatorStrategy();
    ActuatorStrategy(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin, GPIOstrategy * board);
    ActuatorStrategy(unsigned char idController, ControllerType type, short output, short input, GPIOstrategy * board);
    virtual ~ActuatorStrategy();

    void setDelayTime(short delayTime);
    void modify(JardinCommand &jCommand);
    virtual void setInput(std::vector<short> input);
};

#endif
