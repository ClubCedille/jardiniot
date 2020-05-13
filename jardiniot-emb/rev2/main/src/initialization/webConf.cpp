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

#include "webConf.hpp"
#include <array>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/socket.h>

#define module_debug 1

webConf::webConf( )
    : portNumber( 0 ), address( ), listeArguments( ), newConnectionSSID( ),
      newConnectionPW( ), rawGetRequest( ), mqttIp( ), mqttCredentials( ) {}

bool webConf::configure( int portNum ) {
    bool ret = false;

    // Préparation des parametres du socket
    address.sin_family = AF_INET;         // ipv4
    address.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    address.sin_port = htons( portNum ); // passé en paramètres de la fonction
    int addrlen = sizeof( address );
    int socketFileDesc, incomingConnection;

    // Création du socket
    socketFileDesc = socket( AF_INET, SOCK_STREAM, 0 );
    if ( socketFileDesc < 0 ) {
        // Si le socket ne peut pas etre créer
        return ret;
    }

    // Permettre à un autre programme d'utiliser ce port (réduit le temps
    // d'attente avant de relancer le programme de configuration avec succes)
    int opt = 1;
    int err = setsockopt( socketFileDesc, SOL_SOCKET, SO_REUSEADDR,
                          (void *) &opt, sizeof( int ) );
    if ( err < 0 ) {
        return ret;
    }

    // Attacher le socket à l'Adresse innitialisé plus haut
    bind( socketFileDesc, (struct sockaddr *) &address, sizeof( address ) );
    if ( listen( socketFileDesc, 3 ) < 0 ) {
        // Si l'attachement échoue retourner faux
        return ret;
    }

    // Attendre une connection entrante
    if ( ( incomingConnection =
               accept( socketFileDesc, (struct sockaddr *) &address,
                       (socklen_t *) &addrlen ) ) < 0 ) {
        return ret;
    }

    char buffer[512];
    recv( incomingConnection, buffer, 512, 0 );

    // S'assurer que le buffer est terminé par un 0
    buffer[511] = 0;
    this->rawGetRequest = new std::string( buffer );

#if module_debug
    std::cout << *( this->rawGetRequest ) << std::endl;
#endif

    // Obtenir les parametres de la premiere demande.
    // Aucune action n'est prise avec ceux ci car
    //à ce moment, le formulaire web n'est pas encore envoyé.
    parseGetRequest( this->rawGetRequest );

    // Page web dans une string
    const std::string staticPage =
        std::string( "HTTP/1.1 200 OK\n\r\n\r" ) +
        "<html>\n<head>\n<title>JardinIOT wifi "
        "configuration</title>\n<style>\n.EntryField\n{\nwidth: 60%;\nheight: "
        "45px;\ntop: 45px;\ncolor: white;\n\ndisplay: inline-block;\nposition: "
        "relative;\ntext-align: center;\nvertical-align: "
        "middle;\n\nmargin-top: "
        "30px;\npadding-top: 20px;\n                \n                "
        "background-color: blue;\n                border-color: blue;\n        "
        "  "
        "      border: 2px solid blue;\n                border-radius: 25px;\n "
        "  "
        "             \n                font-family: \"Lucida\", Courier, "
        "monospace;\n            }\n            \n            \n            "
        ".TitleBar\n            {\n                font-family: \"Lucida "
        "Console\", , sans-serif;\n                \n                padding: "
        "20px;\n                \n                width: 100%;\n               "
        " "
        "background-color: blue;\n                color: white; \n             "
        "  "
        " font-size: 40px;\n                \n                text-align: "
        "center;\n                display: inline-block;\n                "
        "vertical-align: middle;\n            }\n            \n            "
        ".border\n            {\n                border-width: 2px; \n         "
        "  "
        "     border-style: solid; \n                border-color: black;\n    "
        "  "
        "      }\n        </style>\n    </head>\n    <body>\n        "
        "<center>\n  "
        "          <div class=\"TitleBar\">Configuration wifi JardinIOT "
        "</div>\n<form action=\"/\" method=\"get\">\n<div "
        "class=\"EntryField\">\n<label for=\"SSID\">Wifi SSID "
        ":</label>\n<input "
        "type=\"text\" id=\"wifi\" name=\"SSID\"><br><br>\n</div>\n<div "
        "class=\"EntryField\">\n<label for=\"PW\">Wifi passwd "
        ":</label>\n<input "
        "type=\"password\" id=\"wifipasswd\" "
        "name=\"PW\"><br><br>\n</div>\n<div "
        "class=\"EntryField\">\n<label for=\"MQTTIP\">MQTT URL "
        ":</label>\n<input "
        "type=\"text\" id=\"wifi passwd\" "
        "name=\"MQTTIP\"><br><br>\n</div>\n<div "
        "class=\"EntryField\">\n<label for=\"MqttID\">ClientID "
        ":</label>\n<input "
        "type=\"text\" id=\"wifi passwd\" "
        "name=\"MqttID\"><br><br>\n</div>\n<input class=\"EntryField\" "
        "type=\"submit\" "
        "value=\"Valider\">\n</form>\n</center>\n</body>\n</html>" +
        "\n\r\n\r";

#if module_debug
    std::cout << staticPage;
#endif

    // Envoyer le formulaire
    send( incomingConnection, staticPage.c_str( ), staticPage.length( ), 0 );

    // Si une deuxieme connection arrive
    if ( ( incomingConnection =
               accept( socketFileDesc, (struct sockaddr *) &address,
                       (socklen_t *) &addrlen ) ) < 0 ) {
        return ret;
    }

    // Réinitialisation du buffer pour une nouvelle utilisation
    memset( buffer, 0, 512 );
    // Réinitialisation du buffer de la requete pour une nouvelle utilisation
    delete this->rawGetRequest;
    this->rawGetRequest = NULL;
    // Recv the second request, this one is sent from the web browser after the
    // client clicks submit on the form
    recv( incomingConnection, buffer, 512, 0 );

    // S'assurer que la requeute est terminé avec un 0
    buffer[511] = 0;
    this->rawGetRequest = new std::string( buffer );

#if module_debug
    std::cout << *( this->rawGetRequest ) << std::endl;
#endif

    this->listeArguments = parseGetRequest( this->rawGetRequest );

    std::string basicResponse =
        "HTTP/1.1 200 OK\n\r\n\r<h1>InfoReceived</h1>\n\r\n\r";
    // Envoyer la réponse de base au client et terminer la connection.
    send( incomingConnection, basicResponse.c_str( ), basicResponse.length( ),
          0 );
    shutdown( incomingConnection, SHUT_RDWR );
    close( incomingConnection );

#if module_debug
    for ( auto i = listeArguments.begin( ); i != listeArguments.end( ); ++i ) {
        std::cout << *i << std::endl;
    }
#endif

    if ( listeArguments.size( ) != 4 ) {
        return false;
    }

    this->newConnectionSSID = this->listeArguments[0];
    this->newConnectionPW = this->listeArguments[1];
    this->mqttIp = this->listeArguments[2];
    this->mqttCredentials = this->listeArguments[3];
    return true;
}

std::vector<std::string> webConf::parseGetRequest( std::string *getRequest ) {
    std::vector<std::string> ret;

    auto splitter = getRequest->find( "?" );
    auto nextSplitter = getRequest->find( "HTTP/1.1" );

    std::string params = getRequest->substr( splitter + 1, nextSplitter - 6 );
    if ( params.empty( ) ) {
        return ret;
    }
#if module_debug
    std::cout << params << std::endl;
#endif

    // Séparer les arguments passés dans la requete GET
    std::stringstream toSplit( params );
    std::string piece;
    char delim = '&';
    while ( std::getline( toSplit, piece, delim ) ) {
        // Ajouter les arguments dans le vecteur de retours
        ret.push_back( piece );
    }
    // retourner le vecteur
    return ( ret );
}

webConf::~webConf( ) { delete rawGetRequest; }

std::string webConf::getSSID( ) {
    std::string ret = this->newConnectionSSID.substr(
        this->newConnectionSSID.find( '=' ) + 1 );
    return ret;
}
std::string webConf::getWifiPw( ) {
    std::string ret =
        this->newConnectionPW.substr( this->newConnectionPW.find( '=' ) + 1 );
    return ret;
}

std::string webConf::getMQTTUrl( ) {
    std::string ret = this->mqttIp.substr( this->mqttIp.find( '=' ) + 1 );
    return ret;
}

std::string webConf::getMQTT( ) {
    std::string ret =
        this->mqttCredentials.substr( this->mqttCredentials.find( '=' ) + 1 );
    return ret;
}
