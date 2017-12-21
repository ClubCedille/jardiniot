#include "include/sensor/SensorStrategy.h" //include the declaration for this class

//<<constructor>>
SensorStrategy::SensorStrategy(byte idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin): Controller(idController, type, inputPin, outputPin){
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

char* SensorStrategy::read(){
    return NULL;
}

int SensorStrategy::write(){
    return 0;
}

void SensorStrategy::setInput(std::vector<short> input){
    this->inputPin.clear();
    this->inputPin = input;
}

String SensorStrategy::toString(){
    return "";
}
