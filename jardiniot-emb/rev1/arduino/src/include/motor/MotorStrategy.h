#ifndef MotorStrategy_H
#define MotorStrategy_H

#include "include/Controller.h"
#include "include/command/JardinCommand.h"

/**
    Définit le comportement de base pour les moteurs
*/
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
    virtual void setInput(std::vector<short> input);
};

#endif
