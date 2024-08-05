# log-analyzer

## Principe

Le programme log-analyzer est conçu pour analyser des fichiers journaux (logs) Apache et extraire des informations concernant le nombre de hits d'une page à l'autre.

## Mode d'Emploi

### Prérequis

Assurez-vous d'avoir les éléments suivants installés sur votre machine locale :

- Compilateur C++ (g++ recommandé) avec prise en charge de C++17
- Make

### Construction

Le projet utilise un Makefile pour construire l'exécutable. Pour construire le projet, naviguez vers le répertoire du projet dans votre terminal et exécutez :

```sh
make
```

Vous pouvez alors exécuter le programme comme ceci :
```sh
cd ./bin/
analog [options] [fichiers_logs]
```
## Options disponibles

Voici la liste des options disponibles :

- **```-h``` ou ```--help``` :** Affiche l'aide avec les options disponibles.

- **```-g <FILE>``` ou ```--graph <FILE>``` :** Spécifie le chemin vers le fichier de sortie du graphe. Le programme générera un graphe au format GraphViz.

- **```-e``` ou ```--exclude-special-extensions``` :** Exclut les logs avec des extensions spéciales définies dans le fichier de configuration.

- **```-t <HOUR>``` ou ```--time <HOUR>``` :** Limite l'analyse aux logs dans l'intervalle horaire [HOUR, HOUR+1[.

- **```-l <NUMBER>``` ou ```--limit <NUMBER>``` :** Spécifie le nombre de résultats à afficher pour les URLs les plus consultées. Par défaut, affiche les 10 URLs les plus consultées.

- **```-p``` ou ```--progress``` :** Affiche une barre de progression pendant la lecture des fichiers.
Ces paramètres permettent de personnaliser l'analyse des logs effectuée par le programme 

## Fichier de configuration

Un fichier de configuration peut être placé dans le même répertoire que l'exécutable.
**Celui-ci doit nécessairement se nommer ```analog.conf```.**

Deux lignes peuvent être modifiées :

- **```local-domain``` :** Spécifie le ou les domaines locaux utilisés. Il est important de noter que le préfixe "http://" ou "https://" ne doit pas être inclus. Les différents domaines sont séparés par des espaces.

- **```extensions-excluded```** : Spécifie une liste d'extensions de fichiers à exclure lors de l'analyse lorsque l'option ```--exclude-special-extensions``` est active. Cette liste est insensible à la casse, ce qui signifie que les extensions de fichiers peuvent être écrites en majuscules ou en minuscules. Elles doivent être séparées par des espaces.

## Framework de Tests

Un ensemble de tests sont réalisés dans par un framework dédié. Pour plus d'informations, se référer au fichier ```readme``` dans :

```sh
./Test/
```