#include "include/motor/FanMotor.h"
#include "include/ControllerType.h"//include the declaration for this class

//<<constructor>>
FanMotor::FanMotor(byte idController, std::vector<short> input):MotorStrategy(){
    fanPin = (input[0] & 0xff00) > 8;
    fanSpeed = (input[0] & 0xff);
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
