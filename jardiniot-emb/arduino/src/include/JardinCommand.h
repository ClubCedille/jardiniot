#ifndef JardinCommand_H
#define JardinCommand_H

#include <Arduino.h>
#include <string.h>
#include "ControllerType.h"
#include <StandardCplusplus.h>
#include <vector>

enum CommandType { ADD, CONFIG, DELETE};

class JardinCommand {
private:
    CommandType commandType;
    int idController;
    int delay;
    ControllerType type;
    std::vector<int> outputPin;
    std::vector<int> inputPin;

    // Erreur flag
    bool errorInCommand;
    String errorMsg;

    int split(const String &command, std::vector<String> &strs, char ch);

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
    int getIdController();
    int getDelay();
    ControllerType getControllerType();
    std::vector<int> getOutputPin();
    std::vector<int> getInputPin();
    String getError();

    String toString();
};

#endif
