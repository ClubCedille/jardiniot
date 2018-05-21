#include "include/sensor/LEDSensor.h"
#include "include/ControllerType.h"//include the declaration for this class

//<<constructor>> setup the LED, make pin an OUTPUT
/* Les instructions de préprocesseur suivantes ne sont nécessaires qu'en attendant de savoir
   s'il est possible d'utiliser la même ligne de code sur Pc et Arduino */
#ifdef Arduino
LEDSensor::LEDSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay):SensorStrategy(idController, ControllerType::LED, inputPins, outputPins){
#elif defined Pc
LEDSensor::LEDSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay):SensorStrategy(idController, LED, inputPins, outputPins){
#endif
    ledPin = outputPins[0];
    pinMode(ledPin, OUTPUT); //make that pin an OUTPUT
    SensorStrategy::setDelayTime(delay);
}

//<<destructor>>
LEDSensor::~LEDSensor(){/*nothing to destruct*/}

//turn the LED on
void LEDSensor::on(){
        digitalWrite(ledPin,HIGH); //set the pin HIGH and thus turn LED on
}

//turn the LED off
void LEDSensor::off(){
        digitalWrite(ledPin,LOW); //set the pin LOW and thus turn LED off
}

//blink the LED
void LEDSensor::blink(){
        on();                   //turn LED on
        delay(this->delayTime/2);  //wait half of the wanted period
        off();                  //turn LED off
        delay(this->delayTime/2);  //wait the last half of the wanted period
}

char* LEDSensor::read(){
    char sensorStatus[50];
    strcpy(sensorStatus, "");
    return sensorStatus;
}

int LEDSensor::write(){
    this->blink();
    return 0;
}

String LEDSensor::toString(){
    String s1(ledPin);
    return s1;
}
