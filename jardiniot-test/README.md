# jardiniot-test

Objectif: faire communiquer le Arduino Uno et le ESP8266. 

On devra envoyer le température captée par le DHT22 connecté au Arduino Uno au ESP8266 pour qu'il l'envoie par le WiFi. 

IDE à utiliser: http://platformio.org/platformio-ide#other-platforms

Pour chercher des bibliothèques manquantes:
	1. Aller dans le menu PlatformIO puis dans Library Manager
	2. Web Library Search est le moteur de recherche de choix

Sinon manuellement: `platformio lib install "DHT sensor library"`

À éviter car on veut que le projet s'installe bien sur un autre ordinateur sa avoir à trop gosser. 


NodeMCU: http://www.nodemcu.com/index_en.html
Description: https://en.wikipedia.org/wiki/NodeMCU
Documentation: https://nodemcu.readthedocs.io/en/master/

![2017-02-20-210530](https://cloud.githubusercontent.com/assets/6194072/23149047/4ef4d63a-f7b7-11e6-8098-dd2ed969226d.jpg)


