#ifndef MotorStrategy_H
#define MotorStrategy_H

#include <iostream>

#include "Controller.hpp"
#include "JardinCommand.hpp"

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
    ActuatorStrategy(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin);
    ActuatorStrategy(unsigned char idController, ControllerType type, short output, short input);
    virtual ~ActuatorStrategy();

    void setDelayTime(short delayTime);
    void modify(JardinCommand &jCommand);
    virtual void setInput(std::vector<short> input);
};

#endif
