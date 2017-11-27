#include "include/ControllerFactory.h" //include the declaration for this class
#include "include/LEDSensor.h"

//<<constructor>>
ControllerFactory::ControllerFactory(){}

//<<destructor>>
ControllerFactory::~ControllerFactory(){/*nothing to destruct*/}

// Private method
Type ControllerFactory::getType(ControllerType ctrlType){
    return Sensor;
}

SensorStrategy* ControllerFactory::createSensor(int idController, ControllerType type, int delay, std::vector<int> outputPin, std::vector<int> inputPin){
    // SensorStrategy* sensor = NULL;
    switch (type) {
        case LED:
            return new LEDSensor(idController, inputPin[0], delay);
            break;
        //TODO Ajouter les autres
    }
    return NULL;
}

// Public method
Controller* ControllerFactory::createController(int idController, ControllerType ctrlType, int delay, std::vector<int> outputPin, std::vector<int> inputPin){

    Type type = getType(ctrlType);
    switch(type)
    {
        case Sensor: return createSensor(idController, ctrlType, delay, outputPin, inputPin);    break;
        case Motor: return NULL; //createMotor();
        break;
        case Both: return NULL; //createSensorMotor();
        break;
    }
    return NULL;
}
