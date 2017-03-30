/* Code pour le Huzzah ESP8266 */

// pour le flasher, tenir les deux boutons 'GPIO' et 'Reset' en même temps
// pendant une couple de secondes puis lâcher 'Reset' et attendre
// une autre couple de secondes avec de lâcher 'GPIO' et ça devrait être bon.
// Une lumière rouge va alumer si c'est correcte. Durant l'upload ça flash.
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "CedilleNetwork";
const char* password = "J'aimange2pommes";

const char* topic = "esp8266_test";  // À remplacer par "Temperature" ou "Humidite"
const char* serverip = "192.168.1.187";   // Rentrer l'IP du serveur MQTT ici
int port = 1883;                  // Renter le port du serveyr MQTT ici

// Fait ce qu'il a à faire avec le message reçu
void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  Serial.println(topic);
}

WiFiClient wifiClient;
PubSubClient client(serverip, port, callback, wifiClient);

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

// Connexion au serveur MQTT après s'avoir connecté au WiFi
// Il y aura plusieurs topics
void setup() {
  Serial.begin(9600);

  delay(10);

  // Connexion au WiFi
  Serial.print("Connexion au réseau ayant le SSID: ");  // Sera pas vu si la Serial Console n'est pas ouvert assez vite
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

  // Generate client name based on MAC address and last 8 bits of microsecond counter
  String clientName;
  clientName += "esp8266_";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);
  clientName += "_";
  clientName += String(micros() & 0xff, 16);

  // La topic c'est aussi le nom du bucket
  //topic = clientName.c_str();   // FIXME: Peut pas changer le nom

  // Connexion au serveur MQTT
  Serial.print("Connecting to ");
  Serial.print(serverip);
  Serial.print(" as ");
  Serial.println(clientName);

  if (client.connect((char*) clientName.c_str())) {
    Serial.println("Connected to MQTT broker");
    Serial.print("Topic is: ");
    Serial.println(topic);

    // On publie une topic (on pourrait en créer plusieurs)
    if (client.publish(topic, "hello from ESP8266")) {
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
  static int iteration = 0;

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
