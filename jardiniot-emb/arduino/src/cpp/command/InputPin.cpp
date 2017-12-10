#include "include/command/InputPin.h"

/// Constructeur d'un inputPin
InputPin::InputPin(){
}

InputPin::InputPin(int pin, int val){
    this->pin = pin;
    this->value = val;

}

InputPin::~InputPin(){
}

// Getter pin
int InputPin::getPin(){
    return this->pin;
}

int InputPin::getValue(){
    return this->value;
}

String InputPin::toString(){
    String s1 = "";
    s1.concat("Pin : ");
    s1.concat(this->pin);
    s1.concat(", Value : ");
    s1.concat(this->value);
    return s1;
}
