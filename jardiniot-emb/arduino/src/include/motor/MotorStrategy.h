#ifndef MotorStrategy_H
#define MotorStrategy_H

#include "include/Controller.h"
#include "include/command/JardinCommand.h"

class MotorStrategy: public Controller {
protected:
    int delayTime;
public:
    virtual int activate();
    virtual int stop();

    // constructor
    MotorStrategy();
    MotorStrategy(int idController, ControllerType type, std::vector<InputPin*> inputPin, std::vector<int> outputPin);
    MotorStrategy(int idController, ControllerType type, int output, int input);
    ~MotorStrategy();

    void setDelayTime(int delayTime);
    void modify(JardinCommand &jCommand);
};

#endif
