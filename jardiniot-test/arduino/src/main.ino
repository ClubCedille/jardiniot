/* Code pour le Arduino Uno et le DHT22 */
/* Copyright Alexandre-Xavier Labonté-Lamoureux, 2017 */
#include "DHT.h"
// Si y'a un erreur parce que DHT.h n'est pas trouvé, exécutez la commande:
// platformio lib install "DHT sensor library"

int ledPin = 13;                 // LED connected to digital pin 13

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
  }

  dht.begin();  // part le DHT!

  Serial.println("Ready soon!");

  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(ledPin, LOW);
  delay(5);

/*
  if (Serial.available()) {
    byte byteRead = Serial.read();
    Serial.write(byteRead);
    digitalWrite(ledPin, HIGH);
    delay(10);
  }
*/

  float h = dht.readHumidity();           // humidité
  float t = dht.readTemperature(false);        // temp (Celcius)

  if (isnan(h) || isnan(t)) {
    Serial.println("Echec de lecture du DHT!");
  } else {
    float hic = dht.computeHeatIndex(t, h, false);

    digitalWrite(ledPin, HIGH);
    Serial.print("Humidité: ");
    Serial.print(h);
    Serial.println(" % ");
    Serial.print("Température: ");
    Serial.print(t);
    Serial.println(" °C ");
    Serial.print("Index de chaleur: ");
    Serial.print(hic);
    Serial.println(" °C ");
    Serial.println("");
    delay(20);
    digitalWrite(ledPin, LOW);
    delay(2000);
  }


}
