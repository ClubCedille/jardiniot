#include <include/CommandManager.h>
#include <SoftwareSerial.h>
#include <stdlib.h> /* strtoul */

// http://www.martyncurrey.com/arduino-to-esp8266-serial-commincation/
SoftwareSerial ESPserial(1, 0); // pin 3 à TX du ESP | pin 4 à RX du ESP

String test= "";
// Timer timer;

// Fonction utilisée pour connaitre la RAM libre sur le Arduino lorsque la RAM est pleine le arduino bloc et doit être redémarré
int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

CommandManager* cm;
std::vector<SensorStrategy*> sensorList;
int k = 0;

void setup(){/*nothing to setup*/
    Serial.begin(9600);
    cm = new CommandManager();

    // ESPserial.begin(9600);
    // while (!Serial) {
    //   ; // wait for serial port to connect. Needed for native USB port only
    // }
}

void loop(){

    // Éliminer le plus possible les serial.print puisqu'il coûte cher en mémoire
    // Si nécessaire utiliser F() pour storer les chaines de caractère dans la mémoire Flash au lieu de la mettre dans la mémoire Ram
    Serial.print(F("=========== Free memory "));
    Serial.println(freeRam());

    // Serial.print(F("k = "));
    // Serial.println(k);
    if(k == 0){
        // cm->executeCommand("id 1 a 2 300 i 2504 2660 3016");

        // LED STANDARD
        cm->executeCommand("id 2 a 1 350 o 5");
        cm->executeCommand("id 3 a 1 250 o 4");
        cm->executeCommand("id 4 a 1 250 o 2");
    }

    sensorList = cm->getSensorList();

    for(unsigned char i = 0; i < sensorList.size(); i++){
        sensorList[i]->write();
    }


    if(k %3 ==0){
        // Serial.println(F("TEST DELETE "));
        cm->executeCommand("id 1 d 2");
        cm->executeCommand("id 3 d 1");
    }
    else if(k % 3 == 1){
        // Serial.println(F("TEST AJOUT"));
        short red = 11*256;
        short blue = 10*256;
        short green = 9*256+255;
        cm->executeCommand("id 1 a 2 200 i " +String(green) + " " +String(blue) +" " + String(red));

    }
    else{
        // Serial.println(F("TEST Config"));

        // cm->executeCommand("id 2 c 1 100 o 5");
        // cm->executeCommand("id 4 c 1 500 o 2");
        short red = 11*256+random(55,156);
        short blue = 10*256+random(127,256);
        short green = 9*256+random(0,256);
        // À vérifier le config ajoute quand il n'est pas présent
        cm->executeCommand("id 1 c 2 200 i " +String(green) + " " +String(blue) +" " + String(red));
    }

    k++;

}
