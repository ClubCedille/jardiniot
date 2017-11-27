#ifndef MotorStrategy_H
#define MotorStrategy_H

#include "Controller.h"
#include "JardinCommand.h"

class MotorStrategy: public Controller {
protected:
    int delayTime;
public:
    virtual int activate();
    virtual int stop();

    // constructor
    MotorStrategy();
    MotorStrategy(int idController, ControllerType type, std::vector<int> outputPin, std::vector<int> inputPin);
    MotorStrategy(int idController, ControllerType type, int output, int input);
    ~MotorStrategy();

    void setDelayTime(int delayTime);
    void modify(JardinCommand &jCommand);
};

#endif
