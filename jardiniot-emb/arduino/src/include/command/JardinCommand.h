#ifndef JardinCommand_H
#define JardinCommand_H

#include <Arduino.h>
#include <string.h>
#include "include/ControllerType.h"
#include <StandardCplusplus.h>
#include <vector>

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
    byte getIdController();
    short getDelay();
    ControllerType getControllerType();
    std::vector<short> getOutputPin();
    std::vector<short> getInputPin();
    String getError();

    String toString();
};

#endif
