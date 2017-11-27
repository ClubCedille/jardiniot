#include "include/LEDSensor.h"
#include "include/ControllerType.h"//include the declaration for this class

//<<constructor>> setup the LED, make pin an OUTPUT
LEDSensor::LEDSensor(int idController, byte led_pin, int delay):SensorStrategy(idController, ControllerType::LED, led_pin, -1){
    LED_PIN = led_pin;
    pinMode(LED_PIN, OUTPUT); //make that pin an OUTPUT
    SensorStrategy::setDelayTime(delay);
}

//<<destructor>>
LEDSensor::~LEDSensor(){/*nothing to destruct*/}

//turn the LED on
void LEDSensor::on(){
        digitalWrite(LED_PIN,HIGH); //set the pin HIGH and thus turn LED on
}

//turn the LED off
void LEDSensor::off(){
        digitalWrite(LED_PIN,LOW); //set the pin LOW and thus turn LED off
}

//blink the LED
void LEDSensor::blink(){
        on();                   //turn LED on
        delay(this->delayTime/2);  //wait half of the wanted period
        off();                  //turn LED off
        delay(this->delayTime/2);  //wait the last half of the wanted period
}

int LEDSensor::read(){
    return 0;
}

int LEDSensor::write(){
    this->blink();
    return 0;
}

String LEDSensor::getPin(){
    String s1(LED_PIN);
    return s1;
}
