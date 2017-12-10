#ifndef Controller_H
#define Controller_H

#include <Arduino.h>
#include <string.h>
#include <StandardCplusplus.h>
#include <vector>
#include "ControllerType.h"
#include "include/command/InputPin.h"

class Controller {
private:
    int idController;
    ControllerType type;
protected:
    std::vector<int> outputPin;
    std::vector<InputPin*> inputPin;
public:
    Controller();
    Controller(int idController, ControllerType type, std::vector<InputPin*> inputPin, std::vector<int> outputPin);
    // Controller(int idController, ControllerType type, int outputPin, int inputPin);
    ~Controller();
    String getName();

    virtual int getIdController();
    virtual ControllerType getControllerType();
};

#endif
