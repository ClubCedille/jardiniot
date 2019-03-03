JardinIoT - Serveur Web
==========

Ce dossier contient le code qui concerne le site web, l'API et le connecteur. L'API et le connecteur sont en processus d'être mergé (ils sont dorénavant dans le même dossier).

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

** Une documentation plus complète sur le connecteur peut-être retrouvée dans le Wiki: [Connectivité entre ESP et API (MQTT)](https://github.com/ClubCedille/jardiniot/wiki/Connectivit%C3%A9-entre-ESP-et-API-(MQTT)) **

#### Todo
- Implémenter l'ACL dans Mosquitto (on est sensé pouvoir mettre les accès directement dans la BD)

## Docker
Pour un environement de dévelopement rapide:

* Installer docker et docker-compose
* Lancer l'api avec la commande `docker-compose up` à partir de la racine du dépot.

## API
Structure de l'API:

- Liste des buckets:
	- ```/buckets```
- Infos de base sur le bucket:
	- `/bucket/{id}`
- Dernières données d'un sensor donné:
	- `/bucket/{id}/sensor/{id}/`
- Donné la plus récente d'un sensor donné:
	- `/bucket/{id}/sensor/{id}/latest`

#### À faire
- Obtenir les données sur un intervalle donné:
	- `/bucket/{id}/sensor/{id}/{frequency}`
- Limiter le nombre de données à renvoyer par l'API
	- `/bucket/{id}/sensor/{id}/{frequency}/{limit}`

