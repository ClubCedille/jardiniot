
#ifndef ESP32GPIO_H
#define ESP32GPIO_H

#include "GPIOstrategy.hpp"
#include "driver/gpio.h"
#include <iostream>
#include <functional>


//Enum contenant les numéros de broches des GPIO reliés aux borniers à vis 
//  utilisé comme capteurs
enum capteurs
{
    CAPTEUR1 = 33,
    CAPTEUR2 = 32,
    CAPTEUR3 = 35,
    CAPTEUR4 = 34,
    BOUTON1 = 15,
    BOUTON2 = 2,
};

//Enum contenant les numéros de broches des GPIO reliés aux borniers à vis 
//  utilisé comme sortie
enum actionneurs
{
    ACTIONNEUR1 = 4,
    ACTIONNEUR2 = 16,
    ACTIONNEUR3 = 17,
    ACTIONNEUR4 = 5,
};

class esp32gpio: GPIOstrategy
{
    public:
        esp32gpio();
        ~esp32gpio();
        bool initialize() override;
        bool read(int gpio) override;
        int read_analog(int gpio) override;
        bool write(int gpio, bool state) override;
        bool write_analog(int gpio, int state) override;
        bool attach_interrupt(int gpio, std::function<void(void)>) override;

    private:


};

#endif