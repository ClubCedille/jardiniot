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

// TO REMOVE
void testArduino(){

    if(k == 0){
        // cm->executeCommand("id 1 a 2 300 i 2504 2660 3016");

        // LED STANDARD
        cm->executeCommand("id 2 a 1 350 o 5");
        cm->executeCommand("id 3 a 1 250 o 4");
        cm->executeCommand("id 4 a 1 250 o 2");

        // Ajout de FAN
        cm->executeCommand("id 5 a 4 250 i 255");
        cm->executeCommand("id 6 a 4 250 i 255");

        // Ajout d'un DHT
        // cm->executeCommand("id 7 a 0 250 i 22");
    }

    if(k %3 ==0){
        // Serial.println(F("TEST DELETE "));
        cm->executeCommand("id 1 d 2");
        cm->executeCommand("id 3 d 1");
    }
    else if(k % 3 == 1){
        // Serial.println(F("TEST AJOUT"));
        short red = 11*256; // Pin 11 et value 0
        short blue = 10*256; // Pin 10 et value 0
        short green = 9*256+255; // Pin 9 et value 255
        cm->executeCommand("id 1 a 2 200 i " +String(green) + " " +String(blue) +" " + String(red));

    }
    else{
        // Serial.println(F("TEST Config"));
        short red = 11*256+random(55,156);
        short blue = 10*256+random(127,256);
        short green = 9*256+random(0,256);

        cm->executeCommand("id 1 c 2 200 i " +String(green) + " " +String(blue) +" " + String(red));
    }

    k++;
}
// END

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
            // Serial.println(status);

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
