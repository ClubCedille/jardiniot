#ifndef SensorStrategy_H
#define SensorStrategy_H

#include <vector>
#include <iostream>

#include "JardinCommand.h"
#include "Controller.h"
#include "ControllerType.h"
#include "GPIOstrategy.hpp"

/**
    Définit le comportement de base pour les senseurs
*/
class SensorStrategy: public Controller {
protected:
    short delayTime;
public:
    virtual std::string read();
    virtual int write();
    virtual std::string toString();
    virtual void setInput(std::vector<short> inputPin);

    // constructor
    SensorStrategy();
    SensorStrategy(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin, GPIOstrategy * board);
    virtual ~SensorStrategy();

    void setDelayTime(short delayTime);
    void modify(JardinCommand &jCommand);
};

#endif