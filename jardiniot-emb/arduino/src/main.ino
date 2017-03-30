/* Code pour le Arduino Uno et le DHT22 */
#include "DHT.h"
#include <SoftwareSerial.h>
// Si y'a un erreur parce que DHT.h n'est pas trouvé, exécutez la commande:
// platformio lib install "DHT sensor library"

int ledPin = 13;                 // LED connected to digital pin 13

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// http://www.martyncurrey.com/arduino-to-esp8266-serial-commincation/
SoftwareSerial ESPserial(3, 4); // pin 3 à TX du ESP | pin 4 à RX du ESP

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESPserial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
  }

  dht.begin();  // part le DHT!

  Serial.println("Ready soon!");

  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

/*
  digitalWrite(ledPin, LOW);
  delay(5);

  if (Serial.available()) {
    // Lit ce que j'écris puis le print au serial monitor
    byte byteRead = Serial.read();
    Serial.write(byteRead);
    // Flash la lumière!
    digitalWrite(ledPin, HIGH);
    delay(10);
  }
*/

  // Boucle de lecture-écriture pour tester
  /*while (ESPserial.available()) {
    Serial.write(ESPserial.read());
  }
  while (Serial.available()) {
    ESPserial.write(Serial.read());
  }*/

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

    // Envoyer la temperature
    ESPserial.print("\"temperature\":");
    ESPserial.print(t);
    ESPserial.print("°C");

    // Envoyer l'humidité
    ESPserial.print(",\"humidite\":");
    ESPserial.print(h);
    ESPserial.print("%");

    while (ESPserial.available()) {
      Serial.write(ESPserial.read());
    }
  }
}
