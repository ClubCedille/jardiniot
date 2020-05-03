#ifndef ControllerType_h
#define ControllerType_h

// ControllerType available
// ADAFRUIT_DHT = 0
// LED = 1
// A_LED = 2		(DEL sous le heatsink du capeau du bucket)
// SoilMoisture = 3
// FAN = 4
// VALVE = 5
enum ControllerType { ADAFRUIT_DHT, LED, A_LED, SoilMoisture, FAN, VALVE};

enum Type{Sensor, Motor, Both, UNDEF};

class ControllerTypeValidator {
	public:
	static bool validateCtrlType(int typeId) {
		if (typeId >= 0 && typeId <= 5) {
			return true;
		}
		return false;
	}

	static Type getTypeFromController(ControllerType ctrType) {
		if (ctrType == ADAFRUIT_DHT || ctrType == LED || ctrType == A_LED || ctrType == SoilMoisture) {
			return Sensor;
		}
		if (ctrType == FAN || ctrType == VALVE) {
			return Motor;
		}
		return UNDEF;
	}
};

#endif