/**
* Connecteur MQTT-PostgreSQL pour le projet JardinIoT
* Club CÉDILLE
* ----
* Écrit par Aubert Guillemette
*
* version 0.4, 9 mai 2017
* Ajout du code pour envoyer des commandes au ESP
*/

var out = module.exports;
var mqtt = require('mqtt');
var mqtt_client = undefined;

//----------------------------SECTION CONFIGURATION----------------------------
//Éventuellement, cette section devrait être incluse dans un fichier de config.
const DEBUG = true;
const MQTT_USERNAME = 'jardiniot';
const MQTT_PASSWORD = 'jardiniot'; //Storing passwords in source code isn't good
const MQTT_IP       = '127.0.0.1';
const MQTT_PORT     = '1883';
//-----------------------------------------------------------------------------


//Initialisation du connecteur: instancie un client MQTT et s'abonne
//aux buckets définis dans la BD
out.init = function(sq) {

	//Construction des chaînes de connexion
	const MQTT_CREDS    = { username: MQTT_USERNAME, password: MQTT_PASSWORD };
	const MQTT_CONN_STR = 'mqtt://' + MQTT_IP + ':' + MQTT_PORT;
	debug("Connexion au serveur MQTT...");
	mqtt_client = mqtt.connect(MQTT_CONN_STR, MQTT_CREDS);

	//Callbacks!
	mqtt_client.on('connect', function () {
		debug("Connecté. Inscription aux buckets...");
		/* Ici, on subscribe aux buckets.
		*  Dans le code écrit par axdoomer, le nom du bucket est "esp8266_" + sa MAC.
		*  Les valeurs des différents sensors sont encodées en JSON.
		*/
		//On va chercher les buckets dans la base de données
		sq.getBucketList(function(rst){
			rst.forEach(function(elem){
				debug("--> " + elem.name + " à l'adresse " + elem.ip);
				mqtt_client.subscribe("status_" + elem.name);
			});
		});
	});

	mqtt_client.on('message', function (topic, message) {
		debug("-------------------\nMessage recu:\nTopic: " + topic + ", Message: " + message);
		try
		{
			var sensors = JSON.parse(message);
			//Ici, sensors est un objet et toutes ses keys sont le nom des sensors, donc
			//on doit itérer dans l'objet.
			Object.keys(sensors).forEach(function(name){
				sq.createValueWithSensorName(sensors[name], name, topic.replace("status_", "")); //--> function(_value, _sensorName, _bucketName)
			});
		}
		catch (err)
		{
			debug("Message invalide: " + err.message);
		}
	});

	mqtt_client.on('error', function(error) {
		console.log("Error: " + error);
	});
}

//Fonction qui envoie un message au ESP
out.send = function(bucket, params)
{
	//On utilise un entier 32 bit pour envoyer du data. (4 x 8 bits)
	//[LED bleue] + [LED blanche] + [LED rouge] + [FAN]
	var entier = params.fan + (params.red * 256) + (params.white * Math.pow(256, 2)) + (params.blue * Math.pow(256, 3));
	mqtt_client.publish('control_' + bucket, entier.toString());
}

//Fonction qui affiche des messages à l'écran si la constante DEBUG est true
function debug(msg)
{
	if (DEBUG) { console.log(msg); }
}
