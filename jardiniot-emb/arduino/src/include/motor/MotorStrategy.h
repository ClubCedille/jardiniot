#ifndef MotorStrategy_H
#define MotorStrategy_H

#include "include/Controller.h"
#include "include/command/JardinCommand.h"

class MotorStrategy: public Controller {
protected:
    short delayTime;
public:
    virtual short activate();
    virtual short stop();

    // constructor
    MotorStrategy();
    MotorStrategy(byte idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin);
    MotorStrategy(byte idController, ControllerType type, short output, short input);
    virtual ~MotorStrategy();

    void setDelayTime(short delayTime);
    void modify(JardinCommand &jCommand);
};

#endif
