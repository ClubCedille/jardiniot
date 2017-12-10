#include "include/Controller.h"

//<<constructor>>
Controller::Controller(){
}

Controller::Controller(int idController, ControllerType type, std::vector<InputPin*> inputPin, std::vector<int> outputPin){
    this->idController = idController;
    this->inputPin = inputPin;
    this->outputPin = outputPin;
    this->type = type;
}

// Controller::Controller(int idController, ControllerType type, int output, int input){
//     std::vector<int> outputList;
//     if(output >= 0 && output <= 13){
//         outputList.push_back(output);
//     }
//
//     std::vector<int> inputList;
//     if(input >= 0 && input <= 13){
//         inputList.push_back(input);
//     }
//
//     this->idController = idController;
//     this->inputPin = inputList;
//     this->outputPin = outputList;
//     this->type = type;
// }


//<<destructor>>
Controller::~Controller(){
    this->inputPin.clear();
    this->outputPin.clear();
}

String Controller::getName(){
    String ctrlName;
    switch(this->type)
    {
        case DHT   : ctrlName = "DHT";    break;
        case LED: ctrlName = "LED"; break;
        case SoilMoisture: ctrlName = "SoilMoisture"; break;
        case FAN: ctrlName = "FAN"; break;
        case VALVE: ctrlName = "VALVE"; break;
    }
    return ctrlName;
}

int Controller::getIdController(){
    return this->idController;
}

ControllerType Controller::getControllerType(){
    return this->type;
}
