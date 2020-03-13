# Matériel JardinIOT révision 2.0

## Contexte :

L'arrivé de nouveaux modules plus performants sur le marché des systèmes
embarqués a rendue le matériel utilisé dans la dernière révision obsolète. 
Utiliser ce nouveau matériel permettraient de réduire les irritants et les
problèmes qu'avait la dernière version de JardinIOT.

## Objectifs :

Voici les objectifs pour la révision matériel 2.0 du projet JardinIOT.

* Réduire le nombre de contrôleurs différents dans le projet.
* Réimplémenter le code des itération précédentes pour qu'il fonctionne avec un
  contrôleur possédant plus de RAM (e.g ESP32, Arduino Due/MEGA, Rasperry Pi, etc...).
* Produire un circuit imprimé pour éviter les couettes et les mottes de fils.
  Bref, donner une allure plus professionnelle et moins "prototype" au projet.
* Uniformiser la source de tension. L'itération précédente devait être branché à
  2 places différentes pour leur alimentation.
  
## Choix: 

* Logiciel de dessin pour les circuits: Autodesk EAGLE. Rationnel: Je me suis
  familiarisé avec ce logiciel en technique et m'y sens à l'aise. De plus, le
  logiciel est gratuit pour les étudiants à la création d'un compte Autodesk.
  
* Nouveau contrôleur, plusieurs choix disponibles avec plusieurs implications:

| Possibilité  | pour                                         | contre                                                     |
|--------------|----------------------------------------------|------------------------------------------------------------|
| Rasperry pi  | Beaucoup de mémoire                          | * Tension d'opération incompatible avec les anciens capteurs |
| ESP32        | Mémoire suffisante                           | * Tension d'opération incompatible avec les anciens capteurs * Peu de GPIO|
| Arduino Mega | Moins de mémoire que les options précédentes | * Tension d'opération compatible avec les anciens capteurs   |

Il est important de mentionner qu'il est possible d'acquérir des nouveaux
capteurs pour accomoder les différents choix. De plus, il existe aussi des
multiplexeurs de GPIO dans le cas ou on désire continuer avec l'option ESP32.
