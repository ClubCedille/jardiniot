// https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Arduino.h

#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>
#include <sstream>
#include <inttypes.h>
#include <math.h> // Est importé par le Arduino.h original
#include <stdlib.h>
#include <chrono>
#include "include/arduinoEmulator/String.h"

typedef unsigned int byte;
typedef bool bolean;

enum PinMode {INPUT, OUTPUT, INPUT_PULLUP};
enum PinVoltage {HIGH, LOW};

void analogWrite(short pin, short value);
void pinMode(byte pin, PinMode mode);
void digitalWrite(byte pin, PinVoltage value);
void delay(int ms);

// http://svn.savannah.gnu.org/viewvc/avr-libc/trunk/avr-libc/libc/stdlib/dtostrf.c?revision=1944&view=markup
char* dtostrf (double val, signed char width, unsigned char prec, char *sout);

//https://github.com/esp8266/Arduino/blob/master/cores/esp8266/WString.h
std::string F(std::string str);

// pour ne pas avoir à retaper le code partout
std::string numberToString(int n);



#endif
