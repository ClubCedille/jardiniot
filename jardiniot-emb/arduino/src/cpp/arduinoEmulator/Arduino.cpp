#include "include/arduinoEmulator/Arduino.h"

// Variables utilisée pour la fonction freeRam() de main.cpp
// Jusqu'à preuve du contraire, on suppose qu'il est inutile de les initialiser
int __heap_start, *__brkval;

void analogWrite(short pin, short value) {
    std::cout << "Pin: " << pin << " Value: " << value << std::endl;
}

void pinMode(byte pin, PinMode mode) {
    std::cout << "Pin: " << pin << " Mode: " << mode << std::endl;
}

void digitalWrite(byte pin, PinVoltage value) {
    std::cout << "Pin: " << pin << " Voltage: " << value << std::endl;
}

void delay(int ms) {
    // met sur pause
}

std::string F(std::string str) {return str;};

// Implémentation stupide qui ignore la précision demandée
char* dtostrf (double val, signed char width, unsigned char prec, char *sout)
{
    std::ostringstream ss;
    ss << val;
    std::string str(ss.str());
    int i = 0;
    for(; i < width && i < (signed) str.length(); i++){
        sout[i] = str[i];
    }
    sout[i] = '\0';

    return sout;
}

std::string numberToString(int n) {
    std::ostringstream oss;
    oss << n;
    return oss.str();
}
