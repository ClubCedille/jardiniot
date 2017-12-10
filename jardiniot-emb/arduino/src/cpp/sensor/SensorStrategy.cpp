#include "include/sensor/SensorStrategy.h" //include the declaration for this class

//<<constructor>>
SensorStrategy::SensorStrategy(int idController, ControllerType type, std::vector<InputPin*> inputPin, std::vector<int> outputPin): Controller(idController, type, inputPin, outputPin){
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

void SensorStrategy::setDelayTime(int delayTime){
    this->delayTime = delayTime;
}

int SensorStrategy::read(){
    return 0;
}

int SensorStrategy::write(){
    return 0;
}

void SensorStrategy::setInput(std::vector<InputPin*> input){
    this->inputPin.clear();
    this->inputPin = input;
}

String SensorStrategy::toString(){
    return "";
}
