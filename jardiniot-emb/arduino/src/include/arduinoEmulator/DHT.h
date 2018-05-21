// https://learn.adafruit.com/dht
// https://github.com/adafruit/DHT-sensor-library

#ifndef DHT_H
#define DHT_H

class DHT {
public:
    DHT(uint8_t pin, uint8_t type, uint8_t count=6) {this->pin = pin; this->type = type;};
    void begin(void) {};
    float readHumidity(bool force=false) {return 42.0;}; // retourne une valeur bidon
    float readTemperature(bool S=false, bool force=false) {return 42.0;}; // retourne une valeur bidon
private:
    // Il n'a pas encore été prouvé que ces valeurs nous sont utiles
    uint8_t pin;
    uint8_t type;
};
#endif
