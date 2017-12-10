#ifndef SensorStrategy_H
#define SensorStrategy_H

#include "include/Controller.h"
#include "include/command/JardinCommand.h"

class SensorStrategy: public Controller {
protected:
    int delayTime;
public:
    virtual int read();
    virtual int write();
    virtual String toString();
    virtual void setInput(std::vector<InputPin*> inputPin);

    // constructor
    SensorStrategy();
    SensorStrategy(int idController, ControllerType type, std::vector<InputPin*> inputPin, std::vector<int> outputPin);
    ~SensorStrategy();

    void setDelayTime(int delayTime);
    void modify(JardinCommand &jCommand);
};

#endif
