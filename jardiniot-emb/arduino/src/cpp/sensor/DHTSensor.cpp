#include "include/sensor/DHTSensor.h"

//<<constructor>>
DHTSensor::DHTSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay):SensorStrategy(idController, ControllerType::A_LED, inputPins, outputPins){

    byte DHTPin = (this->inputPin[0] & 0xff00)>> 8;
    byte DHTTYPE = (this->inputPin[0] & 0xff);

    dht = new DHT(DHTPin, DHTTYPE);
    dht->begin();

    SensorStrategy::setDelayTime(delay);
}

//<<destructor>>
DHTSensor::~DHTSensor(){
    delete dht;
}

char* DHTSensor::read(){
    char sensorStatus[50];

    float h = dht->readHumidity();           // humidité
    float t = dht->readTemperature(false);   // temp (Celcius)

    if (isnan(h) || isnan(t)) {
        strcpy(sensorStatus, "Echec de lecture du DHT!");
    } else {
        //convertion de temperature en string
        char tempString[8];
        dtostrf(t, 6, 2, tempString);
        //convertion de l'humidite en string
        char humidityString[8];
        dtostrf(h, 6, 2, humidityString);

        //met les infos dans un char array (sprintf ne prends plus de float (%f) en parametre)

        sprintf(sensorStatus, "\"temperature\":%s,\"humidite\":%s", tempString, humidityString);

    }

    return sensorStatus;
}

int DHTSensor::write(){
    return 0;
}

String DHTSensor::toString(){
    String s1= "";
    return s1;
}
