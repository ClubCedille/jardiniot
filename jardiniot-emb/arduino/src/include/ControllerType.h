#ifndef ControllerType_h
#define ControllerType_h

// ControllerType available
// DHT = 0
// LED = 1
// SoilMoisture = 2
// FAN = 3
// IRRIGATION = 4
enum ControllerType { DHT, LED, SoilMoisture, FAN, IRRIGATION};

enum Type{Sensor, Motor, Both};

class ControllerTypeValidator {
    public:
        static bool validateCtrlType(int typeId){
            if(typeId >= 0 && typeId <= 4){
                return true;
            }
            return false;
        }

        static Type getTypeFromController(ControllerType ctrType){
            if(ctrType == DHT || ctrType == LED || ctrType == SoilMoisture){
                return Sensor;
            }
            if(ctrType == FAN || ctrType == IRRIGATION){
                return Motor;
            }
        }
};

#endif
