#ifndef SensorStrategy_H
#define SensorStrategy_H

#include "include/Controller.h"
#include "include/command/JardinCommand.h"

/**
    Définit le comportement de base pour les senseurs
*/
class SensorStrategy: public Controller {
protected:
    short delayTime;
public:
    virtual char* read();
    virtual int write();
    virtual String toString();
    virtual void setInput(std::vector<short> inputPin);

    // constructor
    SensorStrategy();
    SensorStrategy(byte idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin);
    virtual ~SensorStrategy();

    void setDelayTime(short delayTime);
    void modify(JardinCommand &jCommand);
};

#endif
