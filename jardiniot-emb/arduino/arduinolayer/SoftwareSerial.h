// Copyright (C) 2018 Io Andes Daza-Dillon
//
// JardinIoT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JardinIoT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with JardinIoT.  If not, see <http://www.gnu.org/licenses/>.

// https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/libraries/SoftwareSerial/src/SoftwareSerial.h
#ifndef SoftwareSerial_h
#define SoftwareSerial_h

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
        std::cout << "Écriture sur tx-" << static_cast<int>(this->tx) << " rx-"
                << static_cast<int>(this->rx) << ". Valeur: "
                << static_cast<int>(*str) << std::endl;
        return strlen(str);
    }

    int available() {return 42;} // valeur bidon
    std::string readString() {return "id 1 a 1 111 i 1111 1111 1111";} // valeur bidon

    void begin(int speed) {}

private:
    uint8_t tx;
    uint8_t rx;
};

#endif
