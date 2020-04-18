#include "Controller.hpp"
#include <iostream>
#include <string>


//<<constructor>>
Controller::Controller(){
}

Controller::Controller( unsigned char idController, 
                        ControllerType type, 
                        std::vector<short> inputPin, 
                        std::vector<short> outputPin
                        ):
    idController(idController),
    type(type),
    outputPin(outputPin),
    inputPin(inputPin)
{

}


//<<destructor>>
Controller::~Controller(){
    this->inputPin.clear();
    this->outputPin.clear();
}

std::string Controller::getName(){
    std::string ctrlName;
    switch(this->type)
    {
        case ADAFRUIT_DHT   : ctrlName = "DHT";    break;
        case LED: ctrlName = "LED"; break;
        case A_LED: ctrlName = "A_LED"; break;
        case SoilMoisture: ctrlName = "SoilMoisture"; break;
        case FAN: ctrlName = "FAN"; break;
        case VALVE: ctrlName = "VALVE"; break;
    }
    return ctrlName;
}

unsigned char Controller::getIdController(){
    return this->idController;
}

ControllerType Controller::getControllerType(){
    return this->type;
}