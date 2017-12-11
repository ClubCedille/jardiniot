#ifndef Controller_H
#define Controller_H

#include <Arduino.h>
#include <string.h>
#include <StandardCplusplus.h>
#include <vector>
#include "ControllerType.h"

class Controller {
private:
    byte idController;
    ControllerType type;
protected:
    std::vector<short> outputPin;
    std::vector<short> inputPin;
public:
    Controller();
    Controller(byte idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin);
    // Controller(int idController, ControllerType type, int outputPin, int inputPin);
    ~Controller();
    String getName();

    virtual byte getIdController();
    virtual ControllerType getControllerType();
};

#endif
