#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include "ControllerType.h"

/**
    Représente un controller de n'importe quel type
*/
class Controller {
private:
    unsigned char idController;
    ControllerType type;
protected:
    // Utilisation de short (16 bit) pour obtenir le pin ainsi que la valeur
    // Pin sur les 8 derniers bits
    // Valeur sur les 8 premiers
    std::vector<short> outputPin;
    std::vector<short> inputPin;
public:
    Controller();
    Controller(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin);
    virtual ~Controller();
    std::string getName();

    virtual unsigned char getIdController();
    virtual ControllerType getControllerType();
};

#endif