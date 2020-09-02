#ifndef Controller_H
#define Controller_H

#include "ControllerType.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <string.h>
#include <vector>

/**
    Représente un controller de n'importe quel type
*/
class Controller
{
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
