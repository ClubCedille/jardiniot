#include "include/motor/FanMotor.h"
#include "include/ControllerType.h"//include the declaration for this class

//<<constructor>>
FanMotor::FanMotor(int idController, std::vector<InputPin*> input):MotorStrategy(){
    fanPin = input[0]->getPin();
    fanSpeed = input[0]->getValue();
}

//<<destructor>>
FanMotor::~FanMotor(){/*nothing to destruct*/}

int FanMotor::activate(){
        analogWrite(fanPin, fanSpeed);
        return fanPin;
}


void FanMotor::reset(){

}

int FanMotor::stop(){
    return 0;
}
