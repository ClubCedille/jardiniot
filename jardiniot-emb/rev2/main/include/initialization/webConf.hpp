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