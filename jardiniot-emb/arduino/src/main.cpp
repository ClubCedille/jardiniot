#include <include/CommandManager.h>
#include <include/motor/ServoMotor.h>
#include <SoftwareSerial.h>

ServoMotor* servoTest;

CommandManager* cm;
int k = 0;

void setup(){/*nothing to setup*/
    Serial.begin(9600);
    cm = new CommandManager();
    // servoTest = new ServoMotor(5,9);
}

void loop(){

    // Serial.print("Test Servo");
    //
    // if(servoTest->isAttached()){
    //     Serial.print("isAttached");
    //     int pin = servoTest->activate();
    //     Serial.println(pin);
    // }
    // else{
    //     Serial.print("NotAttached");
    // }
    // Serial.println("Move ");

    String test = "";
    Serial.print("k = ");
    Serial.println(k);
    if(k == 0){
        test = cm->executeCommand("id 1 a 2 300 i 9 200 10 100 11 150");
        Serial.println(test);

        // LED STANDARD
        // cm->executeCommand("id 1 a 1 350 i 13");
        // cm->executeCommand("id 2 a 1 250 i 10");
        // cm->executeCommand("id 3 a 1 250 i 3");
    }


    std::vector<SensorStrategy*> sensorList = cm->getSensorList();

    Serial.print("Size = ");
    Serial.println(sensorList.size());
    for(unsigned int i = 0; i < sensorList.size(); i++){
        sensorList[i]->write();
        Serial.println(sensorList[i]->toString());
    }
    // delay(9000);

    if(k %3 ==1){
        // Serial.println("TEST DELETE ");
        // String test = cm->executeCommand("id 1 d");
        // test = cm->executeCommand("id 3 d");
        // test = cm->executeCommand("id 3 d");
        // Serial.println(test);
    }
    else if(k % 3 == 0 && k != 0){
        // Serial.println("TEST AJOUT");
        // test = cm->executeCommand("id 1 a 2 300 i 9 200 10 100 11 150");
        // String test = cm->executeCommand("id 2 a 1 500 i 10");
        // test = cm->executeCommand("id 3 a 1 500 i 3");
        // Serial.println(test);
    }
    else{
        Serial.println("TEST Config");
        int red = random(55,156);
        int blue = random(127,256);
        int green = random(0,256);
        test = cm->executeCommand("id 1 c 2 1000 i 9 " +String(green) + " 10 " +String(blue) +" 11 " + String(red));
        Serial.println(test);
    }

    k++;

}
