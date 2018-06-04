#include "include/arduinoEmulator/Arduino.h"

Arduino arduino;

// Variables utilisée pour la fonction freeRam() de main.cpp
// Jusqu'à preuve du contraire, on suppose qu'il est inutile de les initialiser
int __heap_start, *__brkval;

// https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
void analogWrite(uint8_t pin, short value) {
    std::cout << "Pin: " << pin << " Value: " << value << std::endl;
}

// https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
void pinMode(uint8_t pin, PinMode mode) {
    std::cout << "Pin: " << pin << " Mode: " << mode << std::endl;
}

// https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/
void digitalWrite(uint8_t pin, uint8_t value) {
    std::cout << "Pin: " << pin << " Voltage: " << value << std::endl;
}

// Met sur pause pour la durée en millisecondes passée en paramètre.
// https://www.arduino.cc/reference/en/language/functions/time/delay/
void delay(int ms) {
    //std::clock_t debut = std::clock();
    auto debut = std::chrono::steady_clock::now();
    auto courant = debut;
    while(std::chrono::duration<double, std::milli>(courant-debut).count() < ms) {
        courant = std::chrono::steady_clock::now();
    };
}

// Donne le nombre de millisecondes écoulées depuis le début de l'exécution du programme.
// https://www.arduino.cc/reference/en/language/functions/time/millis/
unsigned long millis(void){
    auto courant = std::chrono::steady_clock::now();
    auto temps = std::chrono::duration<double, std::milli>(courant-arduino.initialTime).count();
    return static_cast<unsigned long>(temps);
};

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
