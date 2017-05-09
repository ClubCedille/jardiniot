/**
* Connecteur MQTT-PostgreSQL pour le projet JardinIoT
* Club CÉDILLE
* ----
* Écrit par Aubert Guillemette
*
* version 0.3, 9 mai 2017
* Modification du fichier pour qu'il soit utilisé en tant que module.
*/


//----------------------------SECTION CONFIGURATION----------------------------
module.exports = function(sq){
	//Constantes d'application
	const DEBUG = true;

	//Éventuellement, cette section devrait être incluse dans un fichier de config.
	const MQTT_USERNAME = 'jardiniot';
	const MQTT_PASSWORD = 'jardiniot'; //Storing passwords in source code isn't good
	const MQTT_IP       = '127.0.0.1';
	const MQTT_PORT     = '1883';

	//-----------------------------------------------------------------------------



	//Construction des chaînes de connexion
	const MQTT_CREDS    = { username: MQTT_USERNAME, password: MQTT_PASSWORD };
	const MQTT_CONN_STR = 'mqtt://' + MQTT_IP + ':' + MQTT_PORT;

	//Requirements
	//var sq = require('./sqlite_connector.js');
	var mqtt = require('mqtt');



	//Démarrage du client MQTT
	//debug("Ouverture de la base de données...");
	//sq.dbInit();
	//debug("Connecté.");

	debug("Connexion au serveur MQTT...");
	var mqtt_client = mqtt.connect(MQTT_CONN_STR, MQTT_CREDS);

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

	//Fonction qui affiche des messages à l'écran si la constante DEBUG est true
	function debug(msg)
	{
		if (DEBUG) { console.log(msg); }
	}
}
