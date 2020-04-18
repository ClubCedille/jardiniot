#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <iostream>
#include <vector>
#include "ControllerFactory.hpp"
#include "SensorStrategy.hpp"
#include "ActuatorStrategy.hpp"

class CommandManager
{
    public:
        CommandManager();
        ~CommandManager();

        std::string executeCommand(std::string argument);


        std::vector<SensorStrategy*> sensorList;
        std::vector<ActuatorStrategy*> actuatorList;

        std::vector<SensorStrategy*> getSensorList();
        std::vector<ActuatorStrategy*> getActuatorList();


    private:
        ControllerFactory * factory;

        bool isIdControllerUsed(unsigned char idController);

        short getSensor(SensorStrategy * sensor, unsigned char idController);
        short getActuator(ActuatorStrategy * motor, unsigned char idController);

        std::string addController(JardinCommand & j);
        std::string modifyController(JardinCommand & j);
        std::string removeController(JardinCommand & j);

};


#endif