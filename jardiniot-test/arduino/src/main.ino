/* Code pour le Arduino Uno */
/* Copyright Alexandre-Xavier Labonté-Lamoureux, 2017
 * Distributed under the BSD license
*/
int ledPin = 13;                 // LED connected to digital pin 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Ready soon!");

  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(ledPin, LOW);
  delay(10);

  if (Serial.available()) {
    byte byteRead = Serial.read();
    Serial.write(byteRead);
    digitalWrite(ledPin, HIGH);
    delay(10);
  }
}
