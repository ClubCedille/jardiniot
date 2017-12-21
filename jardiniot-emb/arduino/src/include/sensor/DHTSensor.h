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
    DHT* dht;
    byte DHTPin;
    byte DHTTYPE; // Les types sont DHT11, DHT22, DHT21
    char* sensorStatus;
public:
    DHTSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay);
    ~DHTSensor();

    char* read();
    int write();

    String toString();
};

#endif
