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

#include "Arduino.h"

Arduino arduino;

// Variables utilisée pour la fonction freeRam() de main.cpp
// Jusqu'à preuve du contraire, on suppose qu'il est inutile de les initialiser
int __heap_start, *__brkval;

void analogWrite(uint8_t pin, int value) {
    arduino.pins[pin].value = value;
    std::cout << "Pin: " << static_cast<int>(pin) << " Value: " << value << std::endl;
}

void pinMode(uint8_t pin, PinMode mode) {
    arduino.pins[pin].mode = mode;
    auto stringPinMode = pinModeToString.at(mode);
    std::cout << "Pin: " << static_cast<int>(pin) << " Mode: " << stringPinMode << std::endl;
}

void digitalWrite(uint8_t pin, uint8_t value) {
    arduino.pins[pin].value = value;
    auto stringVoltage = pinVoltageToString.at(static_cast<PinVoltage>(value));
    std::cout << "Pin: " << static_cast<int>(pin) << " Voltage: " << stringVoltage << std::endl;
}

int digitalRead(uint8_t pin) {
    return arduino.pins[pin].voltage;
}

void delay(int ms) {
    auto debut = std::chrono::steady_clock::now();
    auto courant = debut;
    while(std::chrono::duration<double, std::milli>(courant-debut).count() < ms) {
        courant = std::chrono::steady_clock::now();
    };
}

void delayMicroseconds(unsigned int us) {
    auto debut = std::chrono::steady_clock::now();
    auto courant = debut;
    while(std::chrono::duration<double, std::micro>(courant-debut).count() < us) {
        courant = std::chrono::steady_clock::now();
    };
}

unsigned long millis(void){
    auto courant = std::chrono::steady_clock::now();
    auto temps = std::chrono::duration<double, std::milli>(courant-arduino.initialTime).count();
    return static_cast<unsigned long>(temps);
};

int microsecondsToClockCycles(int microseconds) {
    return CLOCKS_PER_SEC*microseconds/1000000;
}

void interrupts() {}
void noInterrupts() {}

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
