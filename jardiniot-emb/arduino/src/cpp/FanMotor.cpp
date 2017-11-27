#include "include/FanMotor.h"
#include "include/ControllerType.h"//include the declaration for this class

//<<constructor>>
FanMotor::FanMotor(int idController, int pin, int speed):MotorStrategy(){
    fanPin = pin;
    fanSpeed = speed;
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
