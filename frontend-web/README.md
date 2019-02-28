JardinIoT - Interface Web
=========
_Réalisé avec Angular5_

Ce dossier contient tout ce qui se rapporte à l'interface web. Ce site web est le panneau de contrôle qui nous permettra d'interagir facilement avec l'API, et ainsis afficher les données que le bucket lui envoie.

## Installation
Tout comme l'API, cloner le repo et [installer yarn](https://yarnpkg.com/fr/docs/install).

Ensuite, il faut faire ces commandes pour installer les dépendances :
```
cd jardiniot/serveur-web/
yarn install
```
Assurez-vous que l'api soit en marche afin d'en obtenir les données. L'adresse de l'API doit être paramétrée dans le fichier `src/environment/environment.ts` :

``` typescript
export const environment = {
    production: false,
    api_hostname: "http://localhost:8080"
};
```

Une fois que tout est en place, il faut faire
```
yarn start
```
pour lancer le projet

