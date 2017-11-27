#include "include/MotorStrategy.h" //include the declaration for this class

//<<constructor>>
MotorStrategy::MotorStrategy(int idController, ControllerType type, std::vector<int> outputPin, std::vector<int> inputPin): Controller(idController, type, outputPin, inputPin){
}

MotorStrategy::MotorStrategy(int idController, ControllerType type, int outputPin, int inputPin) : Controller(idController, type, outputPin, inputPin){
}

MotorStrategy::MotorStrategy(){
}

//<<destructor>>
MotorStrategy::~MotorStrategy(){
}

void MotorStrategy::modify(JardinCommand &jCommand){
    this->delayTime = jCommand.getDelay();
}

void MotorStrategy::setDelayTime(int delayTime){
    this->delayTime = delayTime;
}
