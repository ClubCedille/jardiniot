#include "webConf.hpp"
#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include <array>
#include <string.h>
#include <stdio.h>


#define module_debug 0

webConf::webConf(): 
    portNumber(0),
    address(),
    listeArguments(),
    newConnectionSSID(),
    newConnectionPW(),
    rawGetRequest(),
    mqttIp(),
    mqttCredentials()
{
    
}

bool webConf::configure(int portNum)
{
    bool ret = false;


    //Préparation des parametres du socket
    address.sin_family = AF_INET;   //ipv4
    address.sin_addr.s_addr = INADDR_ANY; //0.0.0.0
    address.sin_port = htons( portNum ); //passé en paramètres de la fonction
    int addrlen = sizeof(address);
    int socketFileDesc, incomingConnection;

    //Création du socket
    socketFileDesc = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFileDesc < 0)
    {
        //Si le socket ne peut pas etre créer 
        return ret;
    }

    //Permettre à un autre programme d'utiliser ce port (réduit le temps d'attente avant de relancer 
    //le programme de configuration avec succes)
    int opt = 1;
    int err = setsockopt(socketFileDesc, SOL_SOCKET, SO_REUSEADDR, (void *) &opt, sizeof(int));
    if(err < 0)
    {
        return ret;
    }

    //Attacher le socket à l'Adresse innitialisé plus haut
    bind(socketFileDesc, (struct sockaddr *)&address, sizeof(address));
    if (listen(socketFileDesc, 3) < 0) 
    { 
        //Si l'attachement échoue retourner faux
        return ret;
    } 
    //Attendre une connection entrante
    if ((incomingConnection = accept(socketFileDesc, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        return ret;
    }     

    
    char buffer [4096];
    recv(incomingConnection, buffer, 4096, 0);
    
    //S'assurer que le buffer est terminé par un 0
    buffer[4095] = 0;
    this->rawGetRequest = new std::string(buffer);

    #if module_debug
    std::cout<< *(this->rawGetRequest) << std::endl;
    #endif

    //Obtenir les parametres de la premiere demande.
    //Aucune action n'est prise avec ceux ci car 
    //à ce moment, le formulaire web n'est pas encore envoyé.
    parseGetRequest(this->rawGetRequest);

    //Page web dans une string
    const std::string staticPage = std::string("HTTP/1.1 200 OK\n\r\n\r") + 
    "<html>\n    <head>\n        <title>JardinIOT wifi configuration</title>\n        <style>\n            .EntryField\n            {\n                width: 60%;\n                height: 45px;\n                top: 45px;\n                color: white;\n                \n                display: inline-block;\n                position: relative;\n                text-align: center;\n                vertical-align: middle;\n                \n                margin-top: 30px;\n                padding-top: 20px;\n                \n                background-color: blue;\n                border-color: blue;\n                border: 2px solid blue;\n                border-radius: 25px;\n                \n                font-family: \"Lucida\", Courier, monospace;\n            }\n            \n            \n            .TitleBar\n            {\n                font-family: \"Lucida Console\", , sans-serif;\n                \n                padding: 20px;\n                \n                width: 100%;\n                background-color: blue;\n                color: white; \n                font-size: 40px;\n                \n                text-align: center;\n                display: inline-block;\n                vertical-align: middle;\n            }\n            \n            .border\n            {\n                border-width: 2px; \n                border-style: solid; \n                border-color: black;\n            }\n        </style>\n    </head>\n    <body>\n        <center>\n            <div class=\"TitleBar\">Configuration wifi JardinIOT </div>\n            <form action=\"/\" method=\"get\">\n                <div class=\"EntryField\">\n                    <label for=\"SSID\">Wifi SSID :</label>\n                    <input type=\"text\" id=\"wifi\" name=\"SSID\"><br><br>\n                </div>\n                <div class=\"EntryField\">\n                    <label for=\"PW\">Wifi passwd :</label>\n                    <input type=\"password\" id=\"wifipasswd\" name=\"PW\"><br><br>\n                </div>\n                <div class=\"EntryField\">\n                    <label for=\"MQTTIP\">MQTT URL :</label>\n                    <input type=\"text\" id=\"wifi passwd\" name=\"MQTTIP\"><br><br>\n                </div>\n                <div class=\"EntryField\">\n                    <label for=\"MqttID\">ClientID :</label>\n                    <input type=\"text\" id=\"wifi passwd\" name=\"MqttID\"><br><br>\n                </div>\n                <input class=\"EntryField\" type=\"submit\" value=\"Valider\">\n            </form>\n        </center>\n    </body>\n</html>"
    + "\n\r\n\r";
    
    #if module_debug
    std::cout <<staticPage;
    #endif
    
    //Envoyer le formulaire
    send(incomingConnection, staticPage.c_str(), staticPage.length(), MSG_EOR);

    //Si une deuxieme connection arrive
    if ((incomingConnection = accept(socketFileDesc, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        return ret;
    }

    //Réinitialisation du buffer pour une nouvelle utilisation
    memset(buffer, 0, 4096);
    //Réinitialisation du buffer de la requete pour une nouvelle utilisation
    delete this->rawGetRequest;
    this->rawGetRequest = NULL;
    //Recv the second request, this one is sent from the web browser after the client clicks submit on the form
    recv(incomingConnection, buffer, 4096, 0);

    //S'assurer que la requeute est terminé avec un 0
    buffer[4095] = 0;
    this->rawGetRequest = new std::string(buffer);

    #if module_debug
    std::cout<< *(this->rawGetRequest) << std::endl;
    #endif

    this->listeArguments = parseGetRequest(this->rawGetRequest);
    
    std::string basicResponse = "HTTP/1.1 200 OK\n\r\n\r<h1>InfoReceived</h1>\n\r\n\r";
    //Envoyer la réponse de base au client et terminer la connection.
    send(incomingConnection, basicResponse.c_str(), basicResponse.length(), MSG_EOR);
    shutdown(incomingConnection, SHUT_RDWR);
    close(incomingConnection);

    #if module_debug
    for (auto i = list.begin(); i != list.end(); ++i)
    {
        std::cout<< *i <<std::endl;
    }
    #endif

    if(listeArguments.size() != 4)
    {
        return false;
    }

    this->newConnectionSSID = this->listeArguments[0];
    this->newConnectionPW = this->listeArguments[1];
    this->mqttIp = this->listeArguments[2];
    this->mqttCredentials = this->listeArguments[3];
    return true;
}

std::vector<std::string> webConf::parseGetRequest(std::string * getRequest)
{
    std::vector<std::string> ret;

    auto splitter = getRequest->find("?");
    auto nextSplitter = getRequest->find("HTTP/1.1");

    std::string params = getRequest->substr(splitter + 1, nextSplitter - 6);
    if(params.empty())
    {
        return ret;
    }
    #if module_debug
    std::cout<< params <<std::endl;        
    #endif

    //Séparer les arguments passés dans la requete GET
    std::stringstream toSplit(params);
    std::string piece;
    char delim = '&';
    while(std::getline(toSplit, piece, delim))
    {
        //Ajouter les arguments dans le vecteur de retours
        ret.push_back(piece);
    }
    //retourner le vecteur
    return(ret);
}

webConf::~webConf()
{
    delete rawGetRequest;
}

std::string webConf::getSSID()
{
    std::string ret = this->newConnectionSSID.substr(this->newConnectionSSID.find('=') + 1);
    return ret;
}
std::string webConf::getWifiPw()
{
    std::string ret = this->newConnectionPW.substr(this->newConnectionPW.find('=') + 1);
    return ret;
}

std::string webConf::getMQTTUrl()
{
    std::string ret = this->mqttIp.substr(this->mqttIp.find('=') + 1);
    return ret;
}

std::string webConf::getMQTT()
{
    std::string ret = this->mqttCredentials.substr(this->mqttCredentials.find('=') + 1);
    return ret;
}
