#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  while (!Serial) {
     ; // wait for serial port to connect. Needed for native USB port only
   }
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    mySerial.write(Serial.read());
  }
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
