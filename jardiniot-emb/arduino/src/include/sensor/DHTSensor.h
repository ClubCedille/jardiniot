#ifndef DHTSensor_H
#define DHTSensor_H

#include "include/PreprocessorConstants.h"

#include "SensorStrategy.h"
#ifdef Arduino
    #include <Arduino.h>
#elif defined Pc
    #include "include/arduinoEmulator/Arduino.h"
#endif
#include <string.h>
#include <stdlib.h> /* strtoul */

// Ajout des librairies pour les DHT
#ifdef Arduino
    #include "Adafruit_Sensor.h"
    #include "DHT.h"
#elif defined Pc
    #include <stdio.h> /* sprintf */
    #include "include/arduinoEmulator/DHT.h"
#endif

class DHTSensor: public SensorStrategy {
private:
    DHT* dht;	// On pourrait surement faire que ce soit pas un pointeur
public:
    DHTSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay);
    ~DHTSensor();

    String read();
    int write();

    String toString();
};

#endif
