#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <vector>
#include "SensorStrategy.hpp"

class CommandManager
{
    public:
        CommandManager();
        ~CommandManager();

        std::string executeCommand();

        std::vector<SensorStrategy> getSensorList();
        //std::vector<ActuatorStrategy> getSensorList();

    private:

};


#endif