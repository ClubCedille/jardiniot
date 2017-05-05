JardinIoT - Serveur Web
==========

Ce dossier contient le code qui concerne le site web, l'API et le connecteur. Éventuellement, le code de ces trois objets pourra être mergé (à voir avec XavSavage).

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

#### Todo
- Ré-écrire le connecteur MQTT->BD (la BD a changé de PostgreSQL vers SQLite)
- Implémenter l'ACL (on est sensé pouvoir mettre les accès directement dans la BD)

#### Instructions d'installation
Non fonctionnel pour l'instant

## API
Structure de l'API:

- Liste des buckets: 
	- ```/buckets```
- Infos de base sur le bucket: 
	- `/bucket/{id}`
- Dernières données d'un sensor donné: 
	- `/bucket/{id}/sensor/{id}/`
- Obtenir les données sur un intervalle donné:
	- `/bucket/{id}/sensor/{id}/{frequency}`
- Limiter le nombre de données à renvoyer par l'API
	- `/bucket/{id}/sensor/{id}/{frequency}/{limit}`

#### Todo
- À court terme
	- Faire le code pour obtenir les données sur un intervalle donné (`/bucket/{id}/sensor/{id}/{frequency}`)
	- Faire le code pour limiter le nombre de données à renvoyer par l'API (`/bucket/{id}/sensor/{id}/{frequency}/{limit}`)
- À long terme
	- Faire le code pour envoyer des commandes au bucket
					
## Site web
Le site web se veut le "panneau de contrôle" du jardin. On veut être capable:
- de voir les statistiques
- d'envoyer des commandes au bucket (via l'API)

(voir le prototype d'interface dans le Wiki du projet)

#### Todo
- Tout. Il n'y a rien d'effectué encore au niveau du site web.
