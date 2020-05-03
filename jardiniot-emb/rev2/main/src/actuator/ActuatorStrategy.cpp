#include "ActuatorStrategy.hpp"
#include "GPIOstrategy.hpp"
//<<constructor>>
ActuatorStrategy::ActuatorStrategy(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin, GPIOstrategy * board): Controller(idController, type, inputPin, outputPin, board){
}

ActuatorStrategy::ActuatorStrategy(){
}

//<<destructor>>
ActuatorStrategy::~ActuatorStrategy(){
}

void ActuatorStrategy::modify(JardinCommand &jCommand){
    this->setInput(jCommand.getInputPin());
    this->delayTime = jCommand.getDelay();
}

void ActuatorStrategy::setDelayTime(short delayTime){
    this->delayTime = delayTime;
}

short ActuatorStrategy::activate(){
    return 0;
}

short ActuatorStrategy::stop(){
    return 0;
}

void ActuatorStrategy::setInput(std::vector<short> input){
    this->inputPin.clear();
    this->inputPin = input;
}