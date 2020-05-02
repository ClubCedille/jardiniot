#ifndef DHTSensor_H
#define DHTSensor_H

#include "SensorStrategy.hpp"
#include <string.h>
#include <stdlib.h> /* strtoul */

class DHTSensor: public SensorStrategy {
private:
    //DHT* dht;	// On pourrait surement faire que ce soit pas un pointeur
public:
    DHTSensor(unsigned char idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay);
    ~DHTSensor();

    std::string read();
    int write();

    std::string toString();
};

#endif
