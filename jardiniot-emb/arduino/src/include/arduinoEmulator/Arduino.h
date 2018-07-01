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
#include "include/arduinoEmulator/String.h"

typedef uint8_t byte;
typedef bool boolean;

enum PinMode {INPUT, OUTPUT, INPUT_PULLUP};
enum PinVoltage {HIGH, LOW};

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
