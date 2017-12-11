#include "include/command/JardinCommand.h"

/**
    Les commandes, qui peuvent être reçues, doivent être du format suivant :

    AJOUT :  id (int) a (CONTROLLER_TYPE) delay i (input1 value1 input2 value2) o (output1 output2)
    CONFIG: id (int) c (CONTROLLER_TYPE) delay i (input1 value1 input2 value2) o (output1 output2)
    DELETE: CONFIG: id (int) d (CONTROLLER_TYPE)

*/

JardinCommand::JardinCommand(){
}

JardinCommand::JardinCommand(String command){
    std::vector<String> commandSplitted;

    // Init prop ERREUR
    this->errorInCommand = false;
    this->errorMsg = "";

    this->split(command, commandSplitted, ' ');

    this->validCommand(commandSplitted);
    commandSplitted.clear();
}

JardinCommand::~JardinCommand(){
    this->inputPin.clear();
    this->outputPin.clear();
}

bool JardinCommand::validIdController(std::vector<String> &vecCommand){
    if(vecCommand[0] == "id"){
        this->idController = vecCommand[1].toInt();

        // Si le idController est 0 mais que la chaine de caractères n'était pas 0 alors erreur de conversion
        if(!JardinCommand::validConversionStrToInt(vecCommand[1], this->idController)){
            this->errorInCommand = true;
            this->errorMsg = "Invalid idController";
            return false;
        }
        return true;
    }
    //ERREUR
    this->errorInCommand = true;
    this->errorMsg = "ID controller not provided";

    return false;
}

bool JardinCommand::validConversionStrToInt(String &str, int i){
    bool isValid = true;
    // Si la conversion donne 0 et que la chaine de caractère n'égale pas 0 alors la conversion a échoué
    if((i == 0 && str.compareTo("0") != 0)){
        return false;
    }
    return isValid;
}

int JardinCommand::extractControllerTypeDelay(std::vector<String> &vecCommand){
    int typeId = vecCommand[3].toInt();
    int delayValue = vecCommand[4].toInt();

    if(ControllerTypeValidator::validateCtrlType(typeId)){
        this->type = static_cast<ControllerType>(typeId);
    }
    if(delayValue > 0){
        this->delay = delayValue;
    }
    else{
        this->delay = 0;
    }

    return 5;
}

int JardinCommand::validCommandType(std::vector<String> &vecCommand){

    if(vecCommand[2] == "a"){
        this->commandType = ADD;
        return this->extractControllerTypeDelay(vecCommand);
    }
    else if(vecCommand[2] == "c"){
        this->commandType = CONFIG;
        return this->extractControllerTypeDelay(vecCommand);
    }
    else if(vecCommand[2] == "d"){
        this->commandType = DELETE;
        int typeId = vecCommand[3].toInt();    
        if(ControllerTypeValidator::validateCtrlType(typeId)){
            this->type = static_cast<ControllerType>(typeId);
        }
        return 0;
    }
    else{
        this->errorInCommand = true;
        this->errorMsg = "Invalid command size";
        return -1;
    }
    return -1;
}

int JardinCommand::extractPin(int index, std::vector<String> &vecCommand, String exitCondition, bool isInput){
    int commandSize = vecCommand.size();
    int value = 0;
    int pin = 0;
    InputPin* input;
    for(index++;index < commandSize && vecCommand[index] != exitCondition; index++){
        pin = vecCommand[index].toInt();
        if(JardinCommand::validConversionStrToInt(vecCommand[index], pin)){
            if(isInput){
                index++;
                value = vecCommand[index].toInt();
                input = new InputPin(pin, value);
                this->inputPin.push_back(input);
            }
            else{
                this->outputPin.push_back(pin);
            }
        }
    }
    // delete input;
    return index;
}

bool JardinCommand::validCommand(std::vector<String> &vecCommand){
    int commandSize = vecCommand.size();
    if(commandSize >= 3 && commandSize <= 20){
        // Une commande doit commencer avec ID
        if(validIdController(vecCommand)){
            // Valide commandType et retourne la position où se trouve les pin info
            int i = this->validCommandType(vecCommand);
            if(i<0){
                return !this->errorInCommand;
            }
            else{
                // Extraction des informations de la commande
                for(; i < commandSize; i++){
                    if(vecCommand[i] == "i"){
                        this->extractPin(i, vecCommand, "o", true);
                    }
                    if(vecCommand[i] == "o"){
                        this->extractPin(i, vecCommand, "i", false);
                    }
                }
                return true;
            }
        }
    }
    else{
        this->errorInCommand = true;
        this->errorMsg = "Invalid command size";
    }
    return !this->errorInCommand;
}

// Split les commandes pour permettre de savoir quelle type de commande on doit exécuter
int JardinCommand::split(const String &command, std::vector<String> &strs, char ch)
{
    int pos = command.indexOf(ch);
    // return pos;
    int initialPos = 0;
    strs.clear();

    int commandLength = command.length();

    // Decompose statement
    while( pos < commandLength && pos != -1 ) {
        strs.push_back( command.substring( initialPos, pos) );

        initialPos = pos+1;

        pos = command.indexOf( ch, initialPos+1);
    }
    // Add the last one
    strs.push_back( command.substring( initialPos) );
    return strs.size();
}

int JardinCommand::getIdController(){
    return this->idController;
}

int JardinCommand::getDelay(){
    return this->delay;
}

ControllerType JardinCommand::getControllerType(){
    return this->type;
}

std::vector<int> JardinCommand::getOutputPin(){
    return this->outputPin;
}

std::vector<InputPin*> JardinCommand::getInputPin(){
    return this->inputPin;
}

CommandType JardinCommand::getCommandType(){
    return this->commandType;
}

String JardinCommand::toString(){
    String str = "";
    str.concat(" idController = ");
    str.concat(this->idController);
    str.concat(" CommandType =");
    str.concat(this->commandType);
    str.concat(" ControllerType = ");
    str.concat(this->type);
    str.concat(" Delay =");
    str.concat(this->delay);

    str.concat(" OutputPin = ");
    for(unsigned int i=0; i < this->outputPin.size(); i++){
        str.concat(this->outputPin[i]);

    }

    str.concat(" InputPin = ");
    for(unsigned int i=0; i < this->inputPin.size(); i++){
        str.concat(this->inputPin[i]->toString());
    }
    return str;
}

String JardinCommand::getError(){
    return this->errorMsg;
}
