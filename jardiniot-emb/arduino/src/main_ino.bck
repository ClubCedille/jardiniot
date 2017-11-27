// JardinIOT
// Copyright (C) 2016-2017  Alexandre-Xavier Labonté-Lamoureux
// Copyright (C) 2017       Alexandre Brochu
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

/* Code pour le Arduino Uno et le DHT22 */
#include "DHT.h"
#include <SoftwareSerial.h>
#include <string.h>
#include <stdlib.h> /* strtoul */
#include "Timer.h"
// Si y'a un erreur parce que DHT.h n'est pas trouvé, exécutez la commande:
// platformio lib install "DHT sensor library"

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
Timer timer;

// http://www.martyncurrey.com/arduino-to-esp8266-serial-commincation/
SoftwareSerial ESPserial(3, 4); // pin 3 à TX du ESP | pin 4 à RX du ESP

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESPserial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
  }

  dht.begin();  // part le DHT!

  Serial.println("Preparation...");
  // Démarrer les ventilateurs à puissance maximale
  analogWrite(6, 255);  // Fan de heat-sink tourne toujours à vitesse maximale
  analogWrite(5, 255);

  // À chaque 2 secondes fait un send des infos
  int idTimerEvent = timer.every(2000,sendStatusToESP);
}

void loop() {
  timer.update();

  // Listen for communication from ESP
  readInfoFromESP();
}

void sendStatusToESP(){
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();           // humidité
  float t = dht.readTemperature(false);   // temp (Celcius)

  if (isnan(h) || isnan(t)) {
    Serial.println("Echec de lecture du DHT!");
  } else {
    //convertion de temperature en string
    char tempString[8];
    dtostrf(t, 6, 2, tempString);
    //convertion de l'humidite en string
    char humidityString[8];
    dtostrf(h, 6, 2, humidityString);

    //met les infos dans un char array (sprintf ne prends plus de float (%f) en parametre)
    char sensorStatus[50];
    sprintf(sensorStatus, "\"temperature\":%s,\"humidite\":%s", tempString, humidityString);

    // Send data to ESP
    ESPserial.write(sensorStatus);
  }
}

void readInfoFromESP()
{
  if (ESPserial.available()) {
    String value = ESPserial.readString();
    // Si la chaine de caractère n'est pas vide
    if(value.length() != 0){
      Serial.print("Value received: ");
      Serial.println(value);

      unsigned long info = strtoul(value.c_str(), NULL, 10 );
      convertInfoFromESP(info);
    }
  }
}

void convertInfoFromESP(unsigned long info)
{
  // Extraire les infos contenu dans le int reçu
  unsigned char bleu = (info & 0xff000000) >> 24;
  unsigned char blanc = (info & 0xff0000) >> 16;
  unsigned char rouge = (info & 0xff00) >> 8;
  unsigned char fan = (info & 0xff);

  // Envoyer les valeurs aux différents senseurs
  analogWrite(9, blanc);   // blanches
  analogWrite(10, bleu);   // bleues
  analogWrite(11, rouge);  // rouges
  analogWrite(5, fan);     // fan sur le coté du bucket
}
