// Copyright (C) 2017-2018 Alexandre-Xavier Labonté-Lamoureux
// Copyright (C) 2017      Alexandre Brochu
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

#include <include/CommandManager.h>
#ifdef Arduino
    #include <SoftwareSerial.h>
#elif defined Pc
    #include "include/arduinoEmulator/SoftwareSerial.h"
#endif
#include <stdlib.h> /* strtoul */
#ifdef Arduino
    #include "Timer.h"
#elif defined Pc
    #include <stdio.h> /*sprintf*/
    #include "include/arduinoEmulator/Timer.h"
#endif

// http://www.martyncurrey.com/arduino-to-esp8266-serial-commincation/
SoftwareSerial ESPserial(3, 4); // pin 3 à TX du ESP | pin 4 à RX du ESP
Timer timer;
unsigned long tick = 0;	// Compteur d'intérations de la boucle
CommandManager* cm;

String espval = "";

// Fonction utilisée pour connaitre la RAM libre sur le Arduino lorsque la RAM est pleine le arduino bloc et doit être redémarré
int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  #ifdef Arduino
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  #elif defined Pc // Vérifier si la ligne suivante fonctionne aussi sur Arduino
  return &v - (__brkval == 0 ? &__heap_start : __brkval);
  #endif
}

// Envoie de données
void sendStatusToESP() {
	// On met la valeur du tic dans le tableau de chars
	char s[12];
	sprintf(s,"%d", tick);

	espval = espval + ",\"tics\": " + tick;

	// Envoie des données au ESP8266
	ESPserial.write(espval.c_str());

	espval = "";	// Vider la variable
}

void setup(){
	Serial.begin(9600);
	ESPserial.begin(9600);

	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	Serial.println(F("Serial pret."));

	cm = new CommandManager();
	Serial.println(F("Command manager pret."));

	/******************* On met en place la configuration par défaut *******************/

	// Lumières DEL se trouvant sous le heatsink

	short red = 11*256+125;	// Pin 11 avec intensité de 125, de 2816 à 3071
	short blue = 10*256+160;	// Pin 10 avec intensité de 160, de 2560 à 2815
	short white = 9*256+50;	// Pin 9 avec intensité de 50, de 2304 à 2559

	cm->executeCommand("id 1 a 2 200 i " + String(white) + " " + String(blue) + " " + String(red));

	// Ajout de FAN
	cm->executeCommand("id 5 a 4 250 i " + String(5*256+255));		// Fan latérale (pin 5), de 1280 à 1535
	cm->executeCommand("id 6 a 4 250 i " + String(6*256+255));		// Fan du heatsink, de 1536 à 1791

	// Ajout d'un DHT
	// TODO: Si decommenté, cause problèmes de mémoire ou de socket error. Bouffe trop de mémoire, faut donc enlever d'autres senseurs.
	cm->executeCommand("id 7 a 0 250 i " + String(2*256+22));

	Serial.println(F("Config par defaut executee."));

	// À chaque 2 secondes fait un send des infos
	int idTimerEvent = timer.every(2000, sendStatusToESP);
	Serial.println(F("Timer pret."));
}

// Pour lire les commandes venant du ESP
void readInfoFromESP() {
	if (ESPserial.available()) {
		String command = ESPserial.readString();
		// On vérifie si la chaine de caractère est valide en ayant une taille minimale
		if(command.length() >= 8) {
			Serial.print(F("Received: "));
			Serial.print(command);
			Serial.println(F("."));

			// On fait certain que ce soit une vrai commande. Elles commencent tout le temps par 'id'.
			if (command[0] == 'i' && command[1] == 'd') {
				cm->executeCommand(command);
			} else {
				Serial.println(F("Not a command"));
			}
		}
	}
}

void loop() {
	// Éliminer le plus possible les serial.print puisqu'il coûte cher en mémoire
	// Si nécessaire utiliser F() pour storer les chaines de caractère dans la mémoire Flash au lieu de la mettre dans la mémoire Ram
	Serial.print(F("Free memory "));
	Serial.println(freeRam());

	timer.update();

	// Boucle de gestion pour les sensors
	for(unsigned char i = 0; i < cm->getSensorList().size(); i++) {
		// Écrit les valeurs au pin spécifié lors de la création/configuration
		cm->getSensorList()[i]->write();

		String status = cm->getSensorList()[i]->read();

		// Testé et fonctionnel avec le DHT
		if (status.length() > 0) {
			// Écriture des données dans une variable globale de type String
			Serial.println(status);
			espval = status;
		}
	}

	// Boucle de gestion pour les moteurs
	for(unsigned char i = 0; i < cm->getMotorList().size(); i++){
		cm->getMotorList()[i]->activate();
	}

	Serial.println("tic is " + String(tick++));

	// Listen for communication from ESP
	readInfoFromESP();
}

#if defined Pc
int main(void) {
    setup();
    while(true)
    { // boucle facile à stopper par commentaire
        loop();
        std::cout << std::endl;
        delay(1000); // pour que ça tourne moins vite
    }
}
#endif
