/* Code pour le Arduino Uno et le DHT22 */
#include "DHT.h"
#include <SoftwareSerial.h>
#include <string.h>
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
  float h = dht.readHumidity();           // humidité
  float t = dht.readTemperature(false);        // temp (Celcius)

  if (isnan(h) || isnan(t)) {
    Serial.println("Echec de lecture du DHT!");
  } else {
    //float hic = dht.computeHeatIndex(t, h, false);

    //pour faire flasher la led
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);

    //convertion de temperature en string
    char tempString[8];
    dtostrf(t, 6, 2, tempString);
    //convertion de l'humidite en string
    char humidityString[8];
    dtostrf(h, 6, 2, humidityString);

    //met les infos dans un char array (sprintf ne prends plus de float (%f) en parametre)
    char sensorStatus[50];
    sprintf(sensorStatus, "\"temperature\":%s,\"humidite\":%s",tempString,humidityString);

    // Send data to ESP
    ESPserial.write(sensorStatus);

    // Listen for communication from ESP
    readInfoFromESP();
  }
}

void readInfoFromESP(){

  if (ESPserial.available()) {
    String value = ESPserial.readString();
    Serial.print("Value received :");
    Serial.println(value);

    //int info = atoi(value.c_str());
    //convertInfoFromESP(info);
  }
}

void convertInfoFromESP(int info){
  // Extraire les infos contenu dans le int reçu
  int red = (info & 0xff000000) >> 24;
	int blue = (info & 0xff0000) >> 16;
	int green = (info & 0xff00) >> 8;
  int fans = (info & 0xff);

  Serial.print("Rouge :");
  Serial.println(red);
  Serial.print("Green :");
  Serial.println(green);
  Serial.print("Bleu :");
  Serial.println(blue);
  Serial.print("Fans :");
  Serial.println(fans);
}
