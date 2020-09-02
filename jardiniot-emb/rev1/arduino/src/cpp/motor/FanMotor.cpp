#include "include/motor/FanMotor.h"
#include "include/ControllerType.h"

//<<constructor>>
FanMotor::FanMotor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay)
    : MotorStrategy(idController, ControllerType::FAN, inputPins, outputPins)
{
    fanPin = (inputPins[0] & 0xff00) >> 8;
    fanSpeed = (inputPins[0] & 0xff);
}

//<<destructor>>
FanMotor::~FanMotor()
{ /*nothing to destruct*/
}

short FanMotor::activate()
{
    analogWrite(fanPin, fanSpeed);
    return fanSpeed;
}

void FanMotor::reset()
{
}

short FanMotor::stop()
{
    analogWrite(fanPin, 0);
    return 0;
}

void FanMotor::setInput(std::vector<short> inputPins)
{
    fanPin = (inputPins[0] & 0xff00) >> 8;
    fanSpeed = (inputPins[0] & 0xff);
}
