#include "include/sensor/A_LEDSensor.h"
#include "include/ControllerType.h"//include the declaration for this class

//<<constructor>> setup the LED, make pin an OUTPUT
A_LEDSensor::A_LEDSensor(int idController, std::vector<InputPin*> inputPins, std::vector<int> outputPins, int delay):SensorStrategy(idController, ControllerType::A_LED, inputPins, outputPins){

    this->setInput(inputPins);

    pinMode(whiteLEDPin, OUTPUT); //make that pin an OUTPUT
    pinMode(blueLEDPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);

    SensorStrategy::setDelayTime(delay);
}

//<<destructor>>
A_LEDSensor::~A_LEDSensor(){/*nothing to destruct*/}

int A_LEDSensor::read(){
    return 0;
}

void A_LEDSensor::setInput(std::vector<InputPin *> input){
    this->inputPin.clear();
    this->inputPin = input;

    whiteLEDPin = this->inputPin[0]->getPin();
    whiteValue = this->inputPin[0]->getValue();
    blueLEDPin = this->inputPin[1]->getPin();
    blueValue = this->inputPin[1]->getValue();
    redLEDPin = this->inputPin[2]->getPin();
    redValue = this->inputPin[2]->getValue();

    // Les valeurs de la LED ne doit pas dépasser 255 ou être plus petit que 0
    if(whiteValue < 0 || whiteValue > 255){
        whiteValue = 127;
    }
    if(blueValue < 0 || blueValue > 255){
        blueValue = 127;
    }
    if(redValue < 0 || redValue > 255){
        redValue = 127;
    }
}

int A_LEDSensor::write(){
    analogWrite(whiteLEDPin, whiteValue);
    analogWrite(blueLEDPin, blueValue);
    analogWrite(redLEDPin, redValue);
    delay(this->delayTime);
    return 0;
}

String A_LEDSensor::toString(){
    String s1= "";
    s1.concat("WHITE : " + String(whiteLEDPin));
    s1.concat(" Value : " + String(whiteValue));
    s1.concat("\n");
    s1.concat("BLUE : " + String(blueLEDPin));
    s1.concat(" Value : " + String(blueValue));
    s1.concat("\n");
    s1.concat("RED : " + String(redLEDPin));
    s1.concat(" Value : " + String(redValue));
    s1.concat("\n");
    return s1;
}
