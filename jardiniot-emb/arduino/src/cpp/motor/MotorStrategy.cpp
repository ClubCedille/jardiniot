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
    this->delayTime = jCommand.getDelay();
}

void MotorStrategy::setDelayTime(short delayTime){
    this->delayTime = delayTime;
}

int MotorStrategy::activate(){
    return 0;
}

int MotorStrategy::stop(){
    return 0;
}
