  
// Copyright (C) 2020   Vincent Perrier
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

#ifndef WEBCONF_HPP
#define WEBCONF_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h> 

// Cette classe obtient les informations pour la connection wifi
// par le biais d'un serveur web simple threadé qui héberge un simple formulaire

class webConf
{
    public:
        bool configure(int portNum);

        std::string getSSID();
        std::string getWifiPw();

        std::string getMQTTUrl();
        std::string getMQTT();

        webConf();
        ~webConf();
        
    private:
        std::vector<std::string> parseGetRequest(std::string * getRequest);


        int portNumber;
        struct sockaddr_in address;


        std::vector<std::string> listeArguments;
        std::string  newConnectionSSID;
        std::string  newConnectionPW;

        std::string * rawGetRequest;

        //Todo later
        std::string  mqttIp;
        std::string  mqttCredentials;

};

#endif