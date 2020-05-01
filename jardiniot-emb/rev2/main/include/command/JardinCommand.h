#ifndef JardinCommand_H
#define JardinCommand_H

#include <iostream>
#include <string>
#include "ControllerType.h"
#include <vector>

/**
    Les commandes, qui peuvent être reçues, doivent être du format suivant :

    AJOUT :  id (byte) a (CONTROLLER_TYPE) delay i (input1-value1 input2-value2) o (output1 output2)
    CONFIG: id (byte) c (CONTROLLER_TYPE) delay i (input1-value1 input2-value2) o (output1 output2)
    DELETE: CONFIG: id (byte) d (CONTROLLER_TYPE)

*/
enum CommandType { ADD, CONFIG, DELETE};

class JardinCommand {
private:
    CommandType commandType;
    unsigned char idController;
    short delay;
    ControllerType type;
    std::vector<short> outputPin;
    std::vector<short> inputPin;

    // Erreur flag
    bool errorInCommand;
    std::string errorMsg;

    int split(std::string &command, std::vector<std::string> &strs, char ch);

    bool validCommand(std::vector<std::string> &vecCommand);
    bool validIdController(std::vector<std::string> &vecCommand);
    bool validConversionStrToInt(std::string &str, int i);
    int validCommandType(std::vector<std::string> &vecCommand);
    int extractPin(int index, std::vector<std::string> &vecCommand, std::string condition, bool isInput);
    int extractControllerTypeDelay(std::vector<std::string> &vecCommand);
public:
    JardinCommand();
    JardinCommand(std::string command);
    ~JardinCommand();

    CommandType getCommandType();
    unsigned char getIdController();
    short getDelay();
    ControllerType getControllerType();
    std::vector<short> getOutputPin();
    std::vector<short> getInputPin();
    std::string getError();

    std::string toString();
};

#endif
