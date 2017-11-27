#ifndef SensorStrategy_H
#define SensorStrategy_H

#include "Controller.h"
#include "JardinCommand.h"

class SensorStrategy: public Controller {
protected:
    int delayTime;
public:
    virtual int read();
    virtual int write();

    // constructor
    SensorStrategy();
    SensorStrategy(int idController, ControllerType type, std::vector<int> outputPin, std::vector<int> inputPin);
    SensorStrategy(int idController, ControllerType type, int output, int input);
    ~SensorStrategy();

    void setDelayTime(int delayTime);
    void modify(JardinCommand &jCommand);
};

#endif
