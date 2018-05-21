#include "include/motor/FanMotor.h"
#include "include/ControllerType.h"

//<<constructor>>
/* Les instructions de préprocesseur suivantes ne sont nécessaires qu'en attendant de savoir
   s'il est possible d'utiliser la même ligne de code sur Pc et Arduino */
#ifdef Arduino
FanMotor::FanMotor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay):MotorStrategy(idController, ControllerType::FAN, inputPins, outputPins){
#elif defined Pc
FanMotor::FanMotor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay):MotorStrategy(idController, FAN, inputPins, outputPins){
#endif
    fanPin = (inputPins[0] & 0xff00) >> 8;
    fanSpeed = (inputPins[0] & 0xff);
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

void FanMotor::setInput(std::vector<short> inputPins){
    fanPin = (inputPins[0] & 0xff00) >> 8;
    fanSpeed = (inputPins[0] & 0xff);
}
