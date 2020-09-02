#include "include/motor/ServoMotor.h"
#include "include/ControllerType.h" //include the declaration for this class

//<<constructor>>
ServoMotor::ServoMotor(byte idController, byte pin) : MotorStrategy()
{
    servoPin = pin;
    // We need to attach the servo to the used pin number
    servo.attach(servoPin);
}

//<<destructor>>
ServoMotor::~ServoMotor()
{ /*nothing to destruct*/
}

short ServoMotor::activate()
{

    // for(int i = 0; i < 180; i++){
    //     servo.write(i);
    //     delay(10);
    // }
    servo.write(0);
    delay(1000);
    servo.write(90);
    delay(1000);
    servo.write(180);
    return servoPin;
}

void ServoMotor::reset()
{
}

short ServoMotor::stop()
{
    return 0;
}

bool ServoMotor::isAttached()
{
    return servo.attached();
}
