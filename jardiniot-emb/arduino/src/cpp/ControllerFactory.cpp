#include "include/ControllerFactory.h"
#include "include/motor/FanMotor.h"
#include "include/sensor/A_LEDSensor.h"
#include "include/sensor/DHTSensor.h"
#include "include/sensor/LEDSensor.h"

//<<constructor>>
ControllerFactory::ControllerFactory()
{
}

//<<destructor>>
ControllerFactory::~ControllerFactory()
{ /*nothing to destruct*/
}

SensorStrategy* ControllerFactory::createSensor(byte idController, ControllerType type, short delay, std::vector<short> inputPin,
                                                std::vector<short> outputPin)
{
    switch (type)
    {
    // DHT Sensor
    case ADAFRUIT_DHT:
        return new DHTSensor(idController, inputPin, outputPin, delay);
        break;
    // Simple LED
    case LED:
        return new LEDSensor(idController, inputPin, outputPin, delay);
        break;
    // Analogique LED
    case A_LED:
        return new A_LEDSensor(idController, inputPin, outputPin, delay);
        break;
    // Humidité du sol
    case SoilMoisture:
        // TODO
        break;
        // TODO Ajouter les autres
    }
    return NULL;
}

MotorStrategy* ControllerFactory::createMotor(byte idController, ControllerType type, short delay, std::vector<short> inputPin,
                                              std::vector<short> outputPin)
{
    switch (type)
    {
    // Fan
    case FAN:
        return new FanMotor(idController, inputPin, outputPin, delay);
        break;
    // Valve
    case VALVE:
        // TODO
        break;
        // //TODO Ajouter les autres
    }
    return NULL;
}

// Public method
Controller* ControllerFactory::createController(byte idController, ControllerType ctrlType, short delay, std::vector<short> inputPin,
                                                std::vector<short> outputPin)
{

    Type type = ControllerTypeValidator::getTypeFromController(ctrlType);
    switch (type)
    {
    case Sensor:
        return createSensor(idController, ctrlType, delay, inputPin, outputPin);
        break;
    case Motor:
        return createMotor(idController, ctrlType, delay, inputPin, outputPin);
        break;
    case Both:
        return NULL; // createSensorMotor();
        break;
    }
    return NULL;
}
