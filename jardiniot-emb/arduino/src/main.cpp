#include <include/CommandManager.h>
#include <include/ServoMotor.h>

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
        cm->executeCommand("id 1 a 1 350 i 13");
        cm->executeCommand("id 2 a 1 250 i 10");
        cm->executeCommand("id 3 a 1 250 i 3");
    }


    std::vector<SensorStrategy*> sensorList = cm->getSensorList();

    Serial.print("Size = ");
    Serial.println(sensorList.size());
    for(unsigned int i = 0; i < sensorList.size(); i++){
        sensorList[i]->write();
    }

    if(k %3 ==0){
        Serial.println("TEST DELETE ");
        String test = cm->executeCommand("id 2 d");
        test = cm->executeCommand("id 3 d");
        test = cm->executeCommand("id 3 d");
        // Serial.println(test);
    }
    else if(k % 3 == 1){
        Serial.println("TEST AJOUT");
        String test = cm->executeCommand("id 2 a 1 500 i 10");
        test = cm->executeCommand("id 3 a 1 500 i 3");
        // Serial.println(test);
    }
    else{
        Serial.println("TEST Config");
        test = cm->executeCommand("id 2 c 1 1000 i 10");
        // Serial.println(test);
    }

    k++;

}
