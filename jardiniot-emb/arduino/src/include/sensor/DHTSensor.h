#ifndef DHTSensor_H
#define DHTSensor_H

#include "SensorStrategy.h"
#include <Arduino.h>
#include <string.h>
#include <stdlib.h> /* strtoul */

// Ajout des librairies pour les DHT
#include "Adafruit_Sensor.h"
#include "DHT.h"

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
