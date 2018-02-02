#include "include/motor/FanMotor.h"
#include "include/ControllerType.h"

//<<constructor>>
FanMotor::FanMotor(byte idController, std::vector<short> input):MotorStrategy(){
    fanPin = (input[0] & 0xff00) >> 8;
    fanSpeed = (input[0] & 0xff);
}

//<<destructor>>
FanMotor::~FanMotor(){/*nothing to destruct*/}

short FanMotor::activate(){
        analogWrite(fanPin, fanSpeed);
        return fanSpeed;
}


void FanMotor::reset(){

}

short FanMotor::stop(){
    analogWrite(fanPin, 0);
    return 0;
}
