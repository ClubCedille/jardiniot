#ifndef CommandManager_H
#define CommandManager_H

#include <Arduino.h>
#include <string.h>
#include <StandardCplusplus.h>
#include <vector>
#include "ControllerType.h"
#include "sensor/SensorStrategy.h"
#include "ControllerFactory.h"
#include "command/JardinCommand.h"
#include "motor/MotorStrategy.h"

/**
    Gestionnaire des commandes reçues
*/
class CommandManager {
private:
    ControllerFactory* factory;
    std::vector<SensorStrategy*> sensorList;
    std::vector<MotorStrategy*> motorList;
    String addController(JardinCommand &jCommand);
    String modifyController(JardinCommand &jCommand);
    String removeController(JardinCommand &jCommand);

    short getSensor(std::vector<SensorStrategy*>::iterator it, SensorStrategy *sensor, byte idController);
    short getMotor(std::vector<MotorStrategy*>::iterator it, MotorStrategy *motor, byte idController);
    bool isIdControllerUsed(byte idController);
public:
    CommandManager();
    ~CommandManager();
    String executeCommand(String command);

    std::vector<SensorStrategy*> getSensorList();
    std::vector<MotorStrategy*> getMotorList();
};

#endif
