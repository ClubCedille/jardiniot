#include <include/CommandManager.h>
#include <SoftwareSerial.h>

String test= "";

// std::vector<InputPin*> testvector;
// std::vector<int> testIntvector;
// std::vector<String> vecCommand;

int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
//
// int extractPin(std::vector<String> &vecCommand){
//     int index = 0;
//     int commandSize = vecCommand.size();
//     int value = 0;
//     InputPin* input;
//     for(index++;index < commandSize; index++){
//         int pin = vecCommand[index].toInt();
//         index++;
//         value = vecCommand[index].toInt();
//         input = new InputPin(pin, value);
//         testvector.push_back(input);
//         // testIntvector.push_back(pin);
//     }
//     return index;
// }

CommandManager* cm;
int k = 0;

void setup(){/*nothing to setup*/
    Serial.begin(9600);
    cm = new CommandManager();
}

void loop(){

    Serial.println(freeRam());

    // Serial.print(F("k = "));
    // Serial.println(k);
    if(k == 0){
        test = cm->executeCommand("id 1 a 2 300 i 9 200 10 100 11 150");
        Serial.println(test);

            // vecCommand.push_back("i");
            // vecCommand.push_back("9");
            // vecCommand.push_back("200");
            // vecCommand.push_back("10");
            // vecCommand.push_back("0");
            // vecCommand.push_back("11");
            // vecCommand.push_back("0");

        // for(int i = 0; i < 5; i++){
        //     testvector.push_back(new InputPin(5,5));
        // }
        // Serial.println(test);

        // LED STANDARD
        cm->executeCommand("id 2 a 1 350 o 5");
        cm->executeCommand("id 3 a 1 250 o 4");
        cm->executeCommand("id 4 a 1 250 o 2");
    }


    std::vector<SensorStrategy*> sensorList = cm->getSensorList();

    // Serial.print(F("Size = "));
    // Serial.println(sensorList.size());
    for(unsigned char i = 0; i < sensorList.size(); i++){
        sensorList[i]->write();
        // Serial.println(sensorList[i]->toString());
    }
    // delay(9000);


    if(k %3 ==0){
        Serial.println("TEST DELETE ");
        // cm->executeCommand("id 1 d");
        test = cm->executeCommand("id 3 d 1");
        // Serial.println(test);
        // cm->executeCommand("id 3 d");
        // Serial.println(test);
    }
    else if(k % 3 == 1){
        Serial.println("TEST AJOUT");
        String infoString = "734";
        short info = (short)infoString.toInt();
        unsigned char pin = (info & 0xff00)>> 8;
        unsigned char white = (info & 0xff);
        Serial.println(pin);
        Serial.println(white);

        // test = cm->executeCommand("id 1 a 2 300 i 9 200 10 100 11 150");
        // cm->executeCommand("id 2 a 1 500 i 5");
        // test = cm->executeCommand("id 3 a 1 500 i 3");
        // Serial.println(test);
    }
    else{

        cm->executeCommand("id 2 c 1 100 o 5");
        // cm->executeCommand("id 3 c 1 300 o 4");
        cm->executeCommand("id 4 c 1 500 o 2");
        // Serial.println("TEST Config");
        // int red = random(55,156);
        // int blue = random(127,256);
        // int green = random(0,256);
        // cm->executeCommand("id 1 c 2 200 i 9 " +String(green) + " 10 " +String(blue) +" 11 " + String(red));
        // cm->executeCommand("id 1 c 2 200 i 9 200 10 45 11 55");
        // test = cm->executeCommand("id 1 c 2 1000 i 9 " +String(green) + " 10 " +String(blue) +" 11 " + String(red));
        // Serial.println(test);
    }

    k++;

}
