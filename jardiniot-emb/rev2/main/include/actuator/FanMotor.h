#ifndef FanMotor_H
#define FanMotor_H

#include "MotorStrategy.h"
#include <string.h>

class FanMotor: public MotorStrategy {
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
