# jardiniot-emb

Ce dossier contient le code du système embarqué, qui est actuellement principalement composé d'un Arduino Uno et d'un ESP8266.

Pour voir le montage, consultez [la page wiki](https://github.com/ClubCedille/jardiniot/wiki/Composantes-%C3%A9lectroniques). Elles montrent des photos de la partie physique (et électronique) du jardin.

Il y a aussi de la [documentation sur le code source](http://geocities.ws/axdoomer/jardin/) (qui inclut des graphiques sur les relations entre les classes).

# IMPORTANT: OPTIMISATION POUR ÉVITER LE GÈLE/PLANTAGE

La taille d'allocation par défaut des vecteurs C++ doit être modifiée. Par défaut, elle est dans `jardiniot-emb/arduino/.piolibdeps/StandardCplusplus_ID572/system_configuration.h`. La donnée devant être changée est `__UCLIBCXX_STL_BUFFER_SIZE__`. Elle est normalement à `8`, mais elle doit être changée pour `1`.

## Formatage de code

Pour formater le code C++ dans un style commun, utilisez la commande suivante:

```
clang-format -i -style='{BasedOnStyle: Microsoft, PointerAlignment: Left, ColumnLimit: 150}' *.cpp *.h */*.cpp */*.h */*/*.cpp */*/*.h */*/*/*.cpp */*/*/*.h */*/*/*/*.cpp */*/*/*/*.h */*/*/*/*/*.cpp */*/*/*/*/*.h */*/*/*/*.h */*/*/*/*/*/*.cpp */*/*/*/*/*/*.h
```

#### Photo d'une ancienne version du montage

Voir [ici](https://github.com/ClubCedille/jardiniot/wiki/Composantes-%C3%A9lectroniques) pour les photos récentes.
![2017-03-02-214503 2](https://cloud.githubusercontent.com/assets/6194072/23536579/d562b726-ff93-11e6-8868-f21fe216f864.jpg)
