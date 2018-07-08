// https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/libraries/SoftwareSerial/src/SoftwareSerial.h
#ifndef SoftwareSerial_h
#define SoftwareSerial_h

//#include <inttypes.h>
//#include <Stream.h> https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Stream.h
//https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Print.h

// https://github.com/arduino/ArduinoCore-avr/blob/3f63f2975e7183c3254b6794bfcc8f19ca0301c9/cores/arduino/USBAPI.h
class Serial_ {
public:
    Serial_() {}
    bool operator!() {return false;} // On suppose qu'on peut se permettre de toujours retourner false
    void print(std::string str) {std::cout << str;}
    void print(String str) {std::cout << str;}
    void println(std::string str) {std::cout << str << std::endl;}
    void println(int n) {std::cout << n << std::endl;}
    void begin(int speed) {}
};

// https://github.com/arduino/ArduinoCore-avr/blob/7d4bca50419f2b2e57f92e9bec1cbbbe6d846fc1/cores/arduino/CDC.cpp
Serial_ Serial;

class SoftwareSerial //: public Stream
{
public:
    SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false)
        {this->tx = receivePin; this->rx = transmitPin;}

    // https://cdn.arduino.cc/reference/en/language/functions/communication/serial/write/
    size_t write(const char *str) {
        std::cout << "Écriture sur tx-" << static_cast<int>(this->tx) << " rx-" << static_cast<int>(this->rx) << ". Valeur: " << static_cast<int>(*str) << std::endl;
        return strlen(str);
    }

    int available() {return 42;} // valeur bidon
    std::string readString() {return "id 1 a 1 111 i 1111 1111 1111";}

    void begin(int speed) {}

private:
    uint8_t tx;
    uint8_t rx;
};

#endif
