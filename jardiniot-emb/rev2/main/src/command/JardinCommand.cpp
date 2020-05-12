// Copyright (C) 2020      Vincent Perrier
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

#include "JardinCommand.h"

/**
    Les commandes, qui peuvent être reçues, doivent être du format suivant :

    AJOUT :  id (byte) a (CONTROLLER_TYPE) delay i (input1-value1 input2-value2) o (output1 output2)
    CONFIG: id (byte) c (CONTROLLER_TYPE) delay i (input1-value1 input2-value2) o (output1 output2)
    DELETE: CONFIG: id (byte) d (CONTROLLER_TYPE)

*/

JardinCommand::JardinCommand(){
}

JardinCommand::JardinCommand(std::string command){
    std::vector<std::string> commandSplitted;

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

bool JardinCommand::validIdController(std::vector<std::string> &vecCommand){
    if(vecCommand[0] == "id"){
        this->idController = std::stoi(vecCommand[1]);

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

bool JardinCommand::validConversionStrToInt(std::string &str, int i){
    bool isValid = true;
    // Si la conversion donne 0 et que la chaine de caractère n'égale pas 0 alors la conversion a échoué
    if((i == 0 && str.compare("0") != 0)){
        return false;
    }
    return isValid;
}

int JardinCommand::extractControllerTypeDelay(std::vector<std::string> &vecCommand){
    unsigned char typeId = (unsigned char) std::stoi(vecCommand[3]);
    short delayValue = (short) std::stoi(vecCommand[4]);

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

int JardinCommand::validCommandType(std::vector<std::string> &vecCommand){

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
        unsigned char typeId = (unsigned char) std::stoi(vecCommand[3]);
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

int JardinCommand::extractPin(int index, std::vector<std::string> &vecCommand, std::string exitCondition, bool isInput){
    int commandSize = vecCommand.size();
    short pinValue = 0;
    for(index++;index < commandSize && vecCommand[index] != exitCondition; index++){
        pinValue = (short) std::stoi(vecCommand[index]);
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

bool JardinCommand::validCommand(std::vector<std::string> &vecCommand){
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
int JardinCommand::split(std::string &command, std::vector<std::string> &tokens, char ch)
{
	size_t pos = 0;

	tokens.clear();
	std::string token;
	while ((pos = command.find(ch)) != -1) {
		token = command.substr(0, pos);
		tokens.push_back(token);	// add to vector
		command.erase(0, pos + 1);
	}

	// There may not be any delimiter remaining, but let's not forget the last token.
	tokens.push_back(command);

	return tokens.size();
}

unsigned char JardinCommand::getIdController(){
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

std::string JardinCommand::toString(){
    std::string str = "";
    str + " idController = ";
    str + std::to_string(this->idController);
    str + " CommandType =";
    str + std::to_string(this->commandType);
    str + " ControllerType = ";
    str + std::to_string(this->type);
    str + " Delay =";
    str + std::to_string(this->delay);

    str + " OutputPin = ";

    for(unsigned char i=0; i < this->outputPin.size(); i++){
        str + std::to_string(this->outputPin[i]);

    }

    str + " InputPin = ";
    for(unsigned char i=0; i < this->inputPin.size(); i++){
        str + std::to_string(this->inputPin[i]);
    }
    return str;
}

std::string JardinCommand::getError(){
    return this->errorMsg;
}
