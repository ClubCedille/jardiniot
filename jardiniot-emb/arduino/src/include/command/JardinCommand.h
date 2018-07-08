#ifndef JardinCommand_H
#define JardinCommand_H

#include <Arduino.h>
#include <string.h>
#include "include/ControllerType.h"
#include <StandardCplusplus.h>
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
    byte idController;
    short delay;
    ControllerType type;
    std::vector<short> outputPin;
    std::vector<short> inputPin;

    // Erreur flag
    bool errorInCommand;
    String errorMsg;

    int split(String &command, std::vector<String> &strs, char ch);

    bool validCommand(std::vector<String> &vecCommand);
    bool validIdController(std::vector<String> &vecCommand);
    bool validConversionStrToInt(String &str, int i);
    int validCommandType(std::vector<String> &vecCommand);
    int extractPin(int index, std::vector<String> &vecCommand, String condition, bool isInput);
    int extractControllerTypeDelay(std::vector<String> &vecCommand);
public:
    JardinCommand();
    JardinCommand(String command);
    ~JardinCommand();

    CommandType getCommandType();
    byte getIdController();
    short getDelay();
    ControllerType getControllerType();
    std::vector<short> getOutputPin();
    std::vector<short> getInputPin();
    String getError();

    String toString();
};

#endif
