#include "include/sensor/A_LEDSensor.h"
#include "include/ControllerType.h"//include the declaration for this class
#include "include/PreprocessorConstants.h"

//<<constructor>> setup the LED, make pin an OUTPUT
/* Les instructions de préprocesseur suivantes ne sont nécessaires qu'en attendant de savoir
   s'il est possible d'utiliser la même ligne de code sur Pc et Arduino */
#ifdef Arduino
A_LEDSensor::A_LEDSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay):SensorStrategy(idController, ControllerType::A_LED, inputPins, outputPins){
#elif defined Pc
A_LEDSensor::A_LEDSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay):SensorStrategy(idController, A_LED, inputPins, outputPins){
#endif

    this->setInput(inputPins);

    pinMode(whiteLEDPin, OUTPUT); //make that pin an OUTPUT
    pinMode(blueLEDPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);

    SensorStrategy::setDelayTime(delay);
}

//<<destructor>>
A_LEDSensor::~A_LEDSensor(){/*nothing to destruct*/}

String A_LEDSensor::read(){
    return "";
}

void A_LEDSensor::setInput(std::vector<short> input){
    this->inputPin.clear();
    this->inputPin = input;

    whiteLEDPin = (this->inputPin[0] & 0xff00)>> 8;
    whiteValue = (this->inputPin[0] & 0xff);
    blueLEDPin = (this->inputPin[1] & 0xff00)>> 8;
    blueValue = (this->inputPin[1] & 0xff);
    redLEDPin = (this->inputPin[2] & 0xff00)>> 8;
    redValue = (this->inputPin[2] & 0xff);

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
