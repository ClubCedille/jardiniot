# Composante MQTT

Il faut démarrer Mosquitto sur son ordi. Puis:

1. Démarrer l'emulateur de jardin: `python3 fakejardin.py`
2. Démarrer la composante MQTT: `python3 mqttmain.py`

### Voir les données écrites dans la base de données

1. Exécuter `sqlite3 jardin.db`
2. Pour lister toutes les données: `select * from valeurs;`


