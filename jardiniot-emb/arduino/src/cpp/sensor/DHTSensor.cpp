#include "include/sensor/DHTSensor.h"
#include "include/PreprocessorConstants.h"

//<<constructor>>
/* Les instructions de préprocesseur suivantes ne sont nécessaires qu'en attendant de savoir
   s'il est possible d'utiliser la même ligne de code sur Pc et Arduino */
#ifdef Arduino
DHTSensor::DHTSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay):SensorStrategy(idController, ControllerType::A_LED, inputPins, outputPins){
#elif defined Pc
DHTSensor::DHTSensor(byte idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay):SensorStrategy(idController, A_LED, inputPins, outputPins){
#endif


    byte DHTPin = (this->inputPin[0] & 0xff00) >> 8;
    byte DHTTYPE = (this->inputPin[0] & 0xff);

    dht = new DHT(DHTPin, DHTTYPE);
    dht->begin();

    SensorStrategy::setDelayTime(delay);
}

//<<destructor>>
DHTSensor::~DHTSensor(){
    delete dht;
}

String DHTSensor::read(){
    char sensorStatus[50];

    float h = dht->readHumidity();           // humidité
    float t = dht->readTemperature(false);   // temp (Celcius)

    if (isnan(h) || isnan(t)) {
        strcpy(sensorStatus, "Echec de lecture du DHT!");
    } else {
        // Convertion de temperature en string
        char tempString[8];
        dtostrf(t, 6, 2, tempString);
        // Convertion de l'humidite en string
        char humidityString[8];
        dtostrf(h, 6, 2, humidityString);

        // Met les infos dans un char array (sprintf ne prends plus de float (%f) en parametre)
        sprintf(sensorStatus, "\"temperature\":%s,\"humidite\":%s", tempString, humidityString);
    }

    return String(sensorStatus);
}

int DHTSensor::write(){
    return 0;
}

String DHTSensor::toString(){
    String s1= "";
    return s1;
}
