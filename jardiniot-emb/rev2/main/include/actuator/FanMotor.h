#ifndef FanMotor_H
#define FanMotor_H

#include "ActuatorStrategy.h"
#include <string>

class FanMotor: public ActuatorStrategy {
private:
    unsigned char fanPin;
    unsigned char fanSpeed;
public:
    // constructor
    FanMotor();
    FanMotor(unsigned char idController, std::vector<short> inputPins, std::vector<short> outputPins, short delay);
    ~FanMotor();

    void reset();

    // Méthode hérité de la classe MotorStrategy
    short activate();
    short stop();

    void setInput(std::vector<short> inputPins);
};

#endif
