
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

#ifndef JardinCommand_H
#define JardinCommand_H

#include "ControllerType.h"
#include <iostream>
#include <string>
#include <vector>

/**
    Les commandes, qui peuvent être reçues, doivent être du format suivant :

    AJOUT :  id (byte) a (CONTROLLER_TYPE) delay i (input1-value1 input2-value2)
   o (output1 output2) CONFIG: id (byte) c (CONTROLLER_TYPE) delay i
   (input1-value1 input2-value2) o (output1 output2) DELETE: CONFIG: id (byte) d
   (CONTROLLER_TYPE)

*/
enum CommandType { ADD, CONFIG, DELETE };

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

  int split( std::string &command, std::vector<std::string> &strs, char ch );

  bool validCommand( std::vector<std::string> &vecCommand );
  bool validIdController( std::vector<std::string> &vecCommand );
  bool validConversionStrToInt( std::string &str, int i );
  int validCommandType( std::vector<std::string> &vecCommand );
  int extractPin( int index, std::vector<std::string> &vecCommand,
                  std::string condition, bool isInput );
  int extractControllerTypeDelay( std::vector<std::string> &vecCommand );

public:
  JardinCommand( );
  JardinCommand( std::string command );
  ~JardinCommand( );

  CommandType getCommandType( );
  unsigned char getIdController( );
  short getDelay( );
  ControllerType getControllerType( );
  std::vector<short> getOutputPin( );
  std::vector<short> getInputPin( );
  std::string getError( );

  std::string toString( );
};

#endif
