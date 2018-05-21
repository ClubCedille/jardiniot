#ifndef Controller_H
#define Controller_H

#include "include/PreprocessorConstants.h"

#ifdef Arduino
    #include <Arduino.h>
#elif defined Pc
    #include "include/arduinoEmulator/Arduino.h"
#endif

#include <string.h>
#ifdef Arduino
    #include <StandardCplusplus.h>
#endif
#include <vector>
#include "ControllerType.h"

/**
    Représente un controller de n'importe quel type
*/
class Controller {
private:
    byte idController;
    ControllerType type;
protected:
    // Utilisation de short (16 bit) pour obtenir le pin ainsi que la valeur
    // Pin sur les 8 derniers bits
    // Valeur sur les 8 premiers
    std::vector<short> outputPin;
    std::vector<short> inputPin;
public:
    Controller();
    Controller(byte idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin);
    virtual ~Controller();
    String getName();

    virtual byte getIdController();
    virtual ControllerType getControllerType();
};

#endif
