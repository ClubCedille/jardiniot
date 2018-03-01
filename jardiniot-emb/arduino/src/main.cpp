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
#include <SoftwareSerial.h>
#include <stdlib.h> /* strtoul */

// http://www.martyncurrey.com/arduino-to-esp8266-serial-commincation/
// SoftwareSerial ESPserial(3, 4); // pin 3 à TX du ESP | pin 4 à RX du ESP

// Fonction utilisée pour connaitre la RAM libre sur le Arduino lorsque la RAM est pleine le arduino bloc et doit être redémarré
int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

CommandManager* cm;

int k = 0;

void setup(){
    Serial.begin(9600);
    cm = new CommandManager();

    // ESPserial.begin(9600);
    // while (!Serial) {
    //   ; // wait for serial port to connect. Needed for native USB port only
    // }
}

// À Décommenter une fois que le ESP sera connecté
// void readInfoFromESP()
// {
//   if (ESPserial.available()) {
//     String command = ESPserial.readString();
//     // Si la chaine de caractère n'est pas vide
//     if(command.length() != 0){
//       Serial.print(F("Value received: "));
//       Serial.println(command);
//
//       cm->executeCommand(command);
//     }
//   }
// }

// TO BE REMOVED
void testArduino(){
	if(k == 0)
	{
		// Lumières DEL se trouvant sous le heatsink
		short red = 11*256+125;	// Pin 11 avec intensité de 125
		short blue = 10*256+160;	// Pin 10 avec intensité de 160
		short white = 9*256+50;	// Pin 9 avec intensité de 50
		cm->executeCommand("id 1 a 2 200 i " + String(white) + " " + String(blue) + " " + String(red));

		// Ajout de FAN
		cm->executeCommand("id 5 a 4 250 i " + String(5*256+255));		// Fan latérale (pin 5)
		cm->executeCommand("id 6 a 4 250 i " + String(6*256+255));		// Fan du heatsink

		// Ajout d'un DHT
		cm->executeCommand("id 7 a 0 250 i " + String(2*256+22));
	}
	// Ces deux prochaines conditions font flasher les lumières
	else if (k > 10 && k / 10 % 2 == 0)
	{
		short red = 11*256+10;	// Pin 11 avec intensité de 10
		short blue = 10*256+30;	// Pin 10 avec intensité de 30
		short white = 9*256+10;	// Pin 9 avec intensité de 10
		cm->executeCommand("id 1 c 2 200 i " + String(white) + " " + String(blue) + " " + String(red));

		cm->executeCommand("id 5 c 4 250 i " + String(5*256+255));
		cm->executeCommand("id 6 c 4 250 i " + String(6*256+255));
	}
	else if (k > 10 && k / 10 % 2 == 1)
	{
		short red = 11*256+125;	// Pin 11 avec intensité de 125
		short blue = 10*256+160;	// Pin 10 avec intensité de 160
		short white = 9*256+50;	// Pin 9 avec intensité de 50
		cm->executeCommand("id 1 c 2 200 i " + String(white) + " " + String(blue) + " " + String(red));

		cm->executeCommand("id 5 c 4 250 i " + String(5*256+0));
		cm->executeCommand("id 6 c 4 250 i " + String(6*256+0));
	}

	k++;
}

void loop(){

    // Éliminer le plus possible les serial.print puisqu'il coûte cher en mémoire
    // Si nécessaire utiliser F() pour storer les chaines de caractère dans la mémoire Flash au lieu de la mettre dans la mémoire Ram
    Serial.print(F("=========== Free memory "));
    Serial.println(freeRam());

    // Utiliser pour les tests seulement
    testArduino();

    // Boucle de gestion pour les sensors
    for(unsigned char i = 0; i < cm->getSensorList().size(); i++){
        // Écrit les valeurs au pin spécifié lors de la création/configuration
        cm->getSensorList()[i]->write();

        char* status = cm->getSensorList()[i]->read();
        if((status != NULL) && (status[0] != '\0')){
            // Test
            Serial.println(status);

            // Send data to ESP !!!! À Décommenter !!!!
            // ESPserial.write(status);
        }
    }

    // Boucle de gestion pour les moteurs
    for(unsigned char i = 0; i < cm->getMotorList().size(); i++){
        cm->getMotorList()[i]->activate();
    }

    // Listen for communication from ESP
    // readInfoFromESP(); !!!! À Décommenter !!!!

}
