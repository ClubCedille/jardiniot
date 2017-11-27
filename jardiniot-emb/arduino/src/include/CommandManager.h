#ifndef CommandManager_H
#define CommandManager_H

#include <Arduino.h>
#include <string.h>
#include <StandardCplusplus.h>
#include <vector>
#include "ControllerType.h"
#include "SensorStrategy.h"
#include "ControllerFactory.h"
#include "JardinCommand.h"
#include "MotorStrategy.h"

class CommandManager {
private:
    ControllerFactory* factory;
    std::vector<SensorStrategy*> sensorList;
    std::vector<MotorStrategy*> motorList;
    String addController(JardinCommand &jCommand);
    String modifyController(JardinCommand &jCommand);
    String removeController(JardinCommand &jCommand);

    int getSensor(std::vector<SensorStrategy*>::iterator it, SensorStrategy *sensor, int idController);
    bool isIdControllerUsed(int idController);
public:
    CommandManager();
    ~CommandManager();
    String executeCommand(String command);

    std::vector<SensorStrategy*> getSensorList();
};

#endif
