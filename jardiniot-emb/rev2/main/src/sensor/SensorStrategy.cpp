#include "SensorStrategy.hpp" //include the declaration for this class
#include "GPIOstrategy.hpp"

//<<constructor>>
SensorStrategy::SensorStrategy(unsigned char idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin, GPIOstrategy *board): Controller(idController, type, inputPin, outputPin, board){
}

SensorStrategy::SensorStrategy(){
}

//<<destructor>>
SensorStrategy::~SensorStrategy(){
}

void SensorStrategy::modify(JardinCommand &jCommand){
    this->setInput(jCommand.getInputPin());
    this->delayTime = jCommand.getDelay();
}

void SensorStrategy::setDelayTime(short delayTime){
    this->delayTime = delayTime;
}

std::string SensorStrategy::read(){
    return "";
}

int SensorStrategy::write(){
    return 0;
}

void SensorStrategy::setInput(std::vector<short> input){
    this->inputPin.clear();
    this->inputPin = input;
}

std::string SensorStrategy::toString(){
    return "";
}