#include "include/Controller.h"

//<<constructor>>
Controller::Controller()
{
}

Controller::Controller(byte idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin)
{
    this->idController = idController;
    this->inputPin = inputPin;
    this->outputPin = outputPin;
    this->type = type;
}

//<<destructor>>
Controller::~Controller()
{
    this->inputPin.clear();
    this->outputPin.clear();
}

String Controller::getName()
{
    String ctrlName;
    switch (this->type)
    {
    case ADAFRUIT_DHT:
        ctrlName = "DHT";
        break;
    case LED:
        ctrlName = "LED";
        break;
    case A_LED:
        ctrlName = "A_LED";
        break;
    case SoilMoisture:
        ctrlName = "SoilMoisture";
        break;
    case FAN:
        ctrlName = "FAN";
        break;
    case VALVE:
        ctrlName = "VALVE";
        break;
    }
    return ctrlName;
}

byte Controller::getIdController()
{
    return this->idController;
}

ControllerType Controller::getControllerType()
{
    return this->type;
}
