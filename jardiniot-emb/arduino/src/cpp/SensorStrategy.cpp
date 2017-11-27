#include "include/SensorStrategy.h" //include the declaration for this class

//<<constructor>>
SensorStrategy::SensorStrategy(int idController, ControllerType type, std::vector<int> outputPin, std::vector<int> inputPin): Controller(idController, type, outputPin, inputPin){
}

SensorStrategy::SensorStrategy(int idController, ControllerType type, int outputPin, int inputPin) : Controller(idController, type, outputPin, inputPin){
}

SensorStrategy::SensorStrategy(){
}

//<<destructor>>
SensorStrategy::~SensorStrategy(){
}

void SensorStrategy::modify(JardinCommand &jCommand){
    this->delayTime = jCommand.getDelay();
}

void SensorStrategy::setDelayTime(int delayTime){
    this->delayTime = delayTime;
}
