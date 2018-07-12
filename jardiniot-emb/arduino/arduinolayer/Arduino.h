// Copyright (C) 2018 Io Andes Daza-Dillon
//
// JardinIoT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JardinIoT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with JardinIoT.  If not, see <http://www.gnu.org/licenses/>.

// https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Arduino.h

#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>
#include <sstream>
#include <inttypes.h>
#include <math.h> // Est importé par le Arduino.h original
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <array>
#include <map>
#include "String.h"

using byte = uint8_t;
using boolean = bool;

enum PinMode {INPUT, OUTPUT, INPUT_PULLUP};
enum PinVoltage {HIGH, LOW};



namespace {
    std::map<PinMode, String> pinModeToString = {{INPUT, String("INPUT")}, {OUTPUT, String("OUTPUT")}, {INPUT_PULLUP, String("INPUT_PULLUP")}};
    std::map<PinVoltage, String> pinVoltageToString = {{HIGH, "HIGH"}, {LOW, "LOW"}};
}

// https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
void analogWrite(uint8_t pin, int value);
// https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
void pinMode(uint8_t pin, PinMode mode);
// https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/
void digitalWrite(uint8_t pin, uint8_t value);
// https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
int digitalRead(uint8_t pin);


// Met sur pause pour la durée en millisecondes passée en paramètre.
// https://www.arduino.cc/reference/en/language/functions/time/delay/
void delay(int ms);

void delayMicroseconds(unsigned int us);

// Donne le nombre de millisecondes écoulées depuis le début de l'exécution du programme.
// https://www.arduino.cc/reference/en/language/functions/time/millis/
unsigned long millis(void);

int microsecondsToClockCycles(int microseconds);


// https://www.arduino.cc/reference/en/language/functions/interrupts/interrupts/
void interrupts(); // not implemented
void noInterrupts(); // not implemented


// http://svn.savannah.gnu.org/viewvc/avr-libc/trunk/avr-libc/libc/stdlib/dtostrf.c?revision=1944&view=markup
char* dtostrf (double val, signed char width, unsigned char prec, char *sout);

//https://github.com/esp8266/Arduino/blob/master/cores/esp8266/WString.h
std::string F(std::string str);

struct Pin {
    int value;
    PinMode mode;
    PinVoltage voltage;
};

class Arduino {
public:
    Arduino() {this->initialTime = std::chrono::steady_clock::now();}
    std::chrono::time_point<std::chrono::steady_clock> initialTime;
    std::array<Pin, 14> pins;
};

#endif
