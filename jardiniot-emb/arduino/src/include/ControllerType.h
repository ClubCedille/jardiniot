#ifndef ControllerType_h
#define ControllerType_h

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
};

#endif
