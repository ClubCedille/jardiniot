#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <vector>
#include "SensorStrategy.hpp"
#include "ActuatorStrategy.hpp"

class CommandManager
{
    public:
        CommandManager();
        ~CommandManager();

        std::string executeCommand();

        std::vector<SensorStrategy> getSensorList();
        std::vector<ActuatorStrategy> getActuatorList();

    private:

};


#endif