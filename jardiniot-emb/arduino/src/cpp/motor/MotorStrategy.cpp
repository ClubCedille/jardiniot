#include "include/motor/MotorStrategy.h" //include the declaration for this class

//<<constructor>>
MotorStrategy::MotorStrategy(byte idController, ControllerType type, std::vector<short> inputPin, std::vector<short> outputPin): Controller(idController, type, inputPin, outputPin){
}

MotorStrategy::MotorStrategy(){
}

//<<destructor>>
MotorStrategy::~MotorStrategy(){
}

void MotorStrategy::modify(JardinCommand &jCommand){
    this->setInput(jCommand.getInputPin());
    this->delayTime = jCommand.getDelay();
}

void MotorStrategy::setDelayTime(short delayTime){
    this->delayTime = delayTime;
}

short MotorStrategy::activate(){
    return 0;
}

short MotorStrategy::stop(){
    return 0;
}

void MotorStrategy::setInput(std::vector<short> input){
    this->inputPin.clear();
    this->inputPin = input;
}
