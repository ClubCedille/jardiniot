JardinIoT - Serveur Web
==========

Ce dossier contient le code qui concerne le site web, l'API et le connecteur. Éventuellement, le code de ces trois objets pourra être mergé (à voir avec XavSavage).

Langage de programmation: Javascript (NodeJS)
Base de données: PostgreSQL


## connecteur
Le connecteur se connecte au serveur MQTT et s'inscrit (subscribe) aux topics correspondant aux buckets gérés par le serveur.  Ensuite, le connecteur inscrit les données recueillies dans la base de données.

La liste des buckets gérés par le serveur web se trouve dans la base de données, chaque contrôleur publie (publish) ses données sur un seul topic.

```
bucketA --publish topic "bucketA"--> Mosquitto --> DB
bucketB --publish topic "bucketB"--> Mosquitto --> DB
```

Le serveur MQTT empêche les buckets de publier sur des topics qui ne leur correspondent pas à l'aide d'une ACL.

```
bucketB --publish topic "bucketA"--> Mosquitto --> DENIED
```

####Todo
- Implémenter l'ACL (on est sensé pouvoir mettre les accès directement dans la BD)
- Ré-implémenter l'inscription des topics dans la DB (un topic par bucket)

####Instructions d'installation:
- Installer NodeJS
- S'assurer qu'un serveur MQTT et qu'un serveur PostgreSQL sont en ligne.
- Installer la base de données (fichier database_gen.sql)
- Configurer les IPs et les credentials dans la section configuration du fichier connector.js

##API
Structure de l'API:

- Liste des buckets: 
	- ```/buckets```
- Infos de base sur le bucket: 
	- `/bucket/{id}`
- Dernières données d'un sensor donné: 
	- `/bucket/{id}/sensor/{id}/`
- Obtenir les données sur un intervalle donné:
	- `/bucket/{id}/sensor/{id}/{frequency}`
- Limiter le nombre de données à renvoyer par le serveur
	- `/bucket/{id}/sensor/{id}/{frequency}/{limit}`
					
##Site web
Documentation plus détaillée à venir.
