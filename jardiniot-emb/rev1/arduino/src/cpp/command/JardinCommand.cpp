#include "include/command/JardinCommand.h"

/**
    Les commandes, qui peuvent être reçues, doivent être du format suivant :

    AJOUT :  id (byte) a (CONTROLLER_TYPE) delay i (input1-value1 input2-value2) o (output1 output2)
    CONFIG: id (byte) c (CONTROLLER_TYPE) delay i (input1-value1 input2-value2) o (output1 output2)
    DELETE: CONFIG: id (byte) d (CONTROLLER_TYPE)

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
    byte typeId = (byte)vecCommand[3].toInt();
    short delayValue = (short)vecCommand[4].toInt();

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
        byte typeId = (byte)vecCommand[3].toInt();
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
    short pinValue = 0;
    for(index++;index < commandSize && vecCommand[index] != exitCondition; index++){
        pinValue = (short)vecCommand[index].toInt();
        if(JardinCommand::validConversionStrToInt(vecCommand[index], pinValue)){
            if(isInput){
                this->inputPin.push_back(pinValue);
            }
            else{
                this->outputPin.push_back(pinValue);
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
int JardinCommand::split(const String &command, std::vector<String> &tokens, char ch)
{
	size_t pos = 0;

	tokens.clear();
	String token;
	while ((pos = command.indexOf(ch)) != -1) {
		token = command.substring(0, pos);
		tokens.push_back(token);	// add to vector
		command.remove(0, pos + 1);
	}

	// There may not be any delimiter remaining, but let's not forget the last token.
	tokens.push_back(command);

	return tokens.size();
}

byte JardinCommand::getIdController(){
    return this->idController;
}

short JardinCommand::getDelay(){
    return this->delay;
}

ControllerType JardinCommand::getControllerType(){
    return this->type;
}

std::vector<short> JardinCommand::getOutputPin(){
    return this->outputPin;
}

std::vector<short> JardinCommand::getInputPin(){
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
    for(byte i=0; i < this->outputPin.size(); i++){
        str.concat(this->outputPin[i]);

    }

    str.concat(" InputPin = ");
    for(byte i=0; i < this->inputPin.size(); i++){
        str.concat(this->inputPin[i]);
    }
    return str;
}

String JardinCommand::getError(){
    return this->errorMsg;
}
