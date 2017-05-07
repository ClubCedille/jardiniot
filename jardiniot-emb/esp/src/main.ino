/* Code pour le Huzzah ESP8266 */

// pour le flasher, tenir les deux boutons 'GPIO' et 'Reset' en même temps
// pendant une couple de secondes puis lâcher 'Reset' et attendre
// une autre couple de secondes avec de lâcher 'GPIO' et ça devrait être bon.
// Une lumière rouge va alumer si c'est correcte. Durant l'upload ça flash.
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <string.h>   // strdup

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"  // ip pour se connecter: 192.168.4.1

const char* ssid = "CedilleNetwork";
const char* password = "Quiamanger2pommes!";

// le préfix pour recevoir du API c'est control_
const char* topic = "status_test";  // À remplacer par "Temperature" ou "Humidite"
const char* topicControl = "control_test";
const char* serverip = "192.168.1.187";   // Rentrer l'IP du serveur MQTT ici
int port = 1883;                  // Renter le port du serveyr MQTT ici

// Fait ce qu'il a à faire avec le message reçu
void callback(char* topic, byte* payload, unsigned int length) {
  char message_buff[100];
  // handle message arrived
  Serial.println(topic);
  int i = 0;

  Serial.println("Message arrived:  topic: " + String(topic));
  Serial.println("Length: " + String(length,DEC));

  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';

  String msgString = String(message_buff);

  Serial.println("Payload: " + msgString);

  sendCommandToArduino(msgString);
}

WiFiClient wifiClient;
PubSubClient client;

// Convertit un adresse MAC en string
String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    //if (i < 5)
      //result += ':';
  }
  return result;
}

const char* getTopic(String type, String &clientName){
  clientName = "";
  // Generate client name based on MAC address and last 8 bits of microsecond counter
  clientName += type;
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);
  //clientName += "_";
  //clientName += String(micros() & 0xff, 16);
  return clientName.c_str();   // note: strdup fait un malloc à l'interne
}

// Wifi callback
/*void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Mode configuration. Configurez le WiFi par vous même.");
  Serial.print("Le SSID du AP est: ");
  Serial.println(myWiFiManager->getConfigPortalSSID());
  Serial.print("Utiliser le IP suivant pour la configuration: ");
  Serial.println(WiFi.softAPIP());
}*/

// Connexion au serveur MQTT après s'avoir connecté au WiFi
// Il y aura plusieurs topics
void setup() {
  Serial.begin(9600);

  delay(10);

  // WIFI MANAGER
  WiFiManager wifiManager;
  wifiManager.resetSettings();    // Reset les settings pour les renter à chaque fois.
  wifiManager.setTimeout(1);   //180-->60  // on peut le mettre à 1 pour se connecter par défaut au Wifi hardcodé
  //wifiManager.setConfigPortalTimeout(60); //warn: utiliser cette méthode fuck le esp
  //wifiManager.setConnectTimeout(60);  //warn: utiliser cette méthode fuck le esp

  // MQTT
  String mqtt_server = "";  // Enter MQTT server IP here
  WiFiManagerParameter custom_mqtt_server("mqttserver", "MQTT server IP", mqtt_server.c_str(), 25);
  wifiManager.addParameter(&custom_mqtt_server);

  if (!wifiManager.autoConnect("AP-config-ESP8266-wifi")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    // CONNEXION AU WIFI PAR DEFAULT
    Serial.print("Connexion au réseau par défaut ayant le SSID: ");  // Sera pas vu si la Serial Console n'est pas ouvert assez vite
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connecté!");
    Serial.println("adresse IP: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    mqtt_server = custom_mqtt_server.getValue();
    serverip = strdup(mqtt_server.c_str());
  }

  //if you get here you have connected to the WiFi
  //Serial.print("On se connect au WIFI ayant le SSID: ");
  //Serial.println(ssid);

  String type = "status_";
  String clientName;
  // La topic c'est aussi le nom du bucket
  topic = strdup(getTopic(type, clientName));
  type = "control_";
  topicControl = strdup(getTopic(type, clientName));

  client = PubSubClient(serverip, port, callback, wifiClient);

  // Connexion au serveur MQTT
  Serial.print("On se connecte au serveur MQTT à l'IP: ");
  Serial.print(serverip);
  Serial.print(", en tant que: ");
  Serial.println(topic);   // TOPIC

  if (client.connect((char*) clientName.c_str())) {
    Serial.println("Connected to MQTT broker");
    Serial.print("Topic is: ");
    Serial.println(topic);
    Serial.print("Topic control is: ");
    Serial.println(topicControl);

    // on subscribe sur un topic
    if(client.subscribe(topicControl)){
      Serial.println("Subscribe OK");
    }
    else{
      Serial.println("Subscribe failed");
    }

    // On publie une topic (on pourrait en créer plusieurs)
    if (client.publish(topic, "hello world!")) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }
  }
  else {
    Serial.println("MQTT connect failed");
    Serial.println("Will reset and try again...");
    abort();
  }
}

void loop() {
  // Il faut faire un client loop pour obtenir les messages qui viennent du API
  client.loop();

  sendStatus();
}

void sendCommandToArduino(String command){
  int value = atoi(command.c_str());
  Serial.println(value);

  // Extraire les infos contenu dans le int reçu
  int bleu = (value & 0xff000000) >> 24;
	int blanc = (value & 0xff0000) >> 16;
	int rouge = (value & 0xff00) >> 8;
  int fans = (value & 0xff);

  Serial.print("Bleu :");
  Serial.println(bleu);
  Serial.print("Blanc :");
  Serial.println(blanc);
  Serial.print("Rouge :");
  Serial.println(rouge);
  Serial.print("Fans :");
  Serial.println(fans);

  delay(2020);
}

void sendStatus(){
  static int iteration = 0;

  if(iteration == 0){
    Serial.println(topic);
  }

  String arduino_sensors;
  while (Serial.available()) {
    arduino_sensors = Serial.readString();
  }

  // Ce payload constitue une topic
  String payload = "{\"micros\":";
  payload += micros();
  payload += ",\"iteration\":";
  payload += iteration;
  if (arduino_sensors.length() > 0)
  {
    payload += ",";
    payload += arduino_sensors;
  }
  payload += "}";

  // Envoie du payload
  if (client.connected()){
    Serial.print("Sending payload: ");
    Serial.println(payload);

    if (client.publish(topic, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    }
    else {
      Serial.println("Publish failed");
    }
  }
  // FIXME: Quand le ESP est seul, cela fonctionne normalement,
  // mais sinon il attend 2 secondes après le Arduino et faire 2 itératons.
  iteration++;
  delay(2020);

  if (Serial.available())
  {
    Serial.println(payload);
  }
}
