# Tache B2 - tests unitaires par JUSSEAUME Jonathan

Ce document présente les tests effectués que j'ai réalisé dans le cadre de la
tâche B2 du lot B. Il est découpé en trois parties: les tests unitaires automatisés,
les tests qui ont été réalisés sur le programme et enfin la partie dédiée à la recherche des
fuites mémoires.

## Tests automatisés

Afin de faire des tests, j'ai tout d'abord créer deux fichiers test.c et test.h 
qui vont utiliser la libraire CUNIT. Il faut l'avoir d'installer pour pouvoir lancer
le main. 
Voici la commande pour installer CUNIT sur Debian:
```
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```
Ensuite j'ai rajouté l'option -lcunit à la compilation afin de pouvoir utiliser
les fonctions de la librairie.
Afin de lancer les tests unitaires, j'ai rajouté une option dans le main qui permet de les lancer.
Par conséquent une fois dans le répertoire bin, il suffit de taper la commande suivante pour lancer les tests
unitaires:
```
./main --test
```
Tous les tests unitaires sont dans le fichier test.c, et le main lance l'intégralité des tests.

### Structures de données

La première priorité a été de tester les structures de données qui sont vitales au bon fonctionnement du programme. \
J'ai donc d'abord testé la liste chainée, que ce soit son initialisation, l'ajout d'éléments, la suppression d'éléments ou encore
l'obtention d'un élément à un indice particulier. L'ensemble de ces tests ont été validés. \
J'ai ensuite testé la structure correspondant à un ensemble d'entier afin de m'assurer que l'ajout et l'obtention d'éléments se passait
bien mais que surtout quand on ajoute un élément déjà présent dans l'ensemble alors cela ne le rajoute pas en plus. \
Enfin, je me suis attardé sur la structure grille dédiée au plateau afin de m'assurer que les bornes min_x, max_x
min_y et max_y sont correctement mise à jour quand on retire des cartes ou quand on en ajoute puisque si les bornes sont
correctement mise à jour alors on peut garantir des boucles courtes permettant d'accéder à toutes les cartes. \
En résumé voici les tests effectués sur les structures de données: 
- [x] Initialisation liste chainée
- [x] Ajout en tête liste chaînée
- [x] Suppression élément liste chaînée lorsque l'élément est en tête, au milieu et en queue
- [x] Obtention du i-eme élément de la liste chainée
- [x] initialisation grille 
- [x] ajout d'une carte sur la grille et modification correcte des extremum
- [x] suppression d'une carte sur la grille et modification correcte des extremum
- [x] obtention d'une carte sur la grille
- [x] réinitialisation de la grille
- [x] obtention de la carte non retournée la plus en haut à gauche
- [x] initialisation de l'ensemble d'entier
- [x] ajout d'un élément 
- [x] vérification que si on ajoute un élément dans l'ensemble alors il est déjà présent alors il n'est pas ajouté

### plateau.c

J'ai ensuite fait des fonctions afin de tester unitairement plateau.c afin de vérifier que son comportement
était correct
- [x] Initialisation du plateau avec une grille à la bonne taille, avec des factions et un nombre de cartes posees, retournees mis à 0
- [x] Quand on pose une carte sur la grille alors la position de la carte est modifiée et la carte est correctement placée sur notre grille
- [x] Vérifier que si une faction a plus de points DDRS que l'autre alors son nombre de manches gagnées augmente de 1
- [x] Vérifier que si la dernière carte retournée est Laurent Prével alors peu importe le nombre de points DDRS des deux factions, c'est sa faction qui gagne
- [x] Vérifier que si il y a égalité en termes de points alors c'est la faction qui a la carte la plus en haut à gauche qui gagne
- [x] Vérifier qu'il faut bien 2 manches gagnées afin de remporter la victoire
- [x] Vérifier que réinitialiser manche efface bien ce qu'il y a sur la grille

### carte.c

J'ai testé l'initialisation d'une carte afin de vérifier que ces champs sont bien instanciés.

### faction.c

J'ai testé les différentes fonctions de faction.c
- [x] Initialisation correct avec des champs avec les bonnes valeurs (ex: nombre de manches gagnées mis à 0)
- [x] Vérifier que la génération des cartes à piocher est bien aléatoire et génère toujours des indices entre 0 et 46
- [x] Vérifer que vider la main dans la pioche permet d'éviter des fuites mémoire
- [x] Vérifier que les cartes tirées sont bien les bonnes cartes désignées par les chiffres de la pioche

### aleatoire

J'ai vérifié que la génération de l'ordre dans lequel les joueurs jouaient étaient
bien aléatoire en vérifiant qu'il était bien possible de commencer avec la faction 0 comme 
avec la faction 1. Ensuite j'ai vérifié que la deuxième manche commençait toujours avec la faction
qui n'avait pas commencé à la première manche.

### interface

J'ai également tenté d'automatiser certains tests de l'interface. Pour cela j'ai utilisé des fichiers mis dans
le répertoire test et j'ai utilisé dup2 afin de faire des saisies utilisateurs via ces fichiers et vérifier que les résultats
retournées sont bons.
- [x] La fonction demandant à remelanger renvoie VRAI quand on écrit "O" ou "o"
- [x] La fonction demandant à remelanger renvoie FAUX quand on écrit "N" ou "n"
- [x] La fonction demandant à remelanger continue à nous demander d'écrire quand on écrit autre chose que "O", "o", "N" ou "n"

### effets

Voici la liste des effets que j'ai automatisé avec via la création d'une manche factice:
- [x] la carte FISE rapporte 1 point à la faction qui a posé la carte
- [x] la carte FISA rapporte 2 points à la faction qui a posé la carte s'il y a un nombre pair de cartes retournées
- [x] la carte FISA ne rapporte pas de points à la faction qui a posé la carte s'il y a un nombre impair de cartes retournées
- [x] la carte FC ne rapporte pas de points s'il n'y pas d'autres cartes FC retournées
- [x] la carte FC rapporte quatre points s'il y a une autre carte FC retournée
- [x] la carte Ecologiie rapporte un point par carte FC/FISE/FISA retournée
- [x] la carte lIIens prend toutes les cartes FISE/FISA/FC retournées et les met bien en haut à gauche face cachée
- [x] la carte alcool détruit les cartes adjacentes mais ne se détruit pas
- [x] la carte Heures supplémentaires enlève 3 points à la faction adverse de celle qui a posé
- [x] la carte Fetia Bannour permet de supprimer toutes les cartes qui sont sur sa ligne et sur sa colonne s'il y a une carte Heures supplémentaires
- [x] l'effet de Laurent Prével fait bien gagner la partie (cf tests unitaires sur la réinitialisation d'une manche)


## Tests non automatisés

Malheureusement je n'ai pas pu automatisé certains tests qui sont très longs à mettre en place ou difficillement automatisables.


### effets

Les tests unitaires des effets sont clairement les plus longs à automatiser, j'ai essayé d'en automatiser au maximum mais j'ai également pu
vérifier les éléments suivants en jouant des parties:
- [x] Kahima Bouchama supprime bien une carte non retournée au hasard
- [x] Kevin Goliard supprime bien une ligne au hasard et rapporte deux points DDRS par carte supprimée à la faction qui l'a posé
- [x] l'effet d'Anne Laure Ligozat ajoute 3 points DDRS par carte EcologIIE, Ecocup, Isolation du bâtiment et parcours sobriété numérique retournées et la dernière carte non retournée du plateau est supprimée
- [ ] Si les conditions pour marquer des points ne sont pas réunies, Katrin Salhab retoure tous les cartes sur sa ligne sans appliquer les effets
- [x] Vitera Y rapporte 3 points à l'équipe qui a le moins de points DDRS
- [x] Fetia Bannour rapporte 1 point DDRS par Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau s'il n'y a pas d'heures supplémentaires


Nous avions également quelques doutes sur certains effets qui sont les suivants:
- Effet d'Aurélien..., faut-il strictement plus de 3 cartes sur la même ligne ou un nombre supérieur ou égal à 3, pour l'instant nous avons mis strictement supérieur à 3

### Interfaces

Pour les interfaces, j'ai testé différentes fonctionnalités en lançant des parties.
Tout d'abord j'ai vérifié que les informations affichées étaient correctes.
J'ai testé la demande pour prendre une carte dans la main
- [x] La fonction demandant une carte dans la main n'autorise pas un chiffre trop grand
- [x] La fonction demandant une carte dans la main n'autorise pas une chaîne de caractères
- [x] La fonction demandant une carte dans la main supprime bien la carte de la main si on saisit un indice correct
J'ai ensuite testé la saisie pour poser une carte:
- [x] J'ai vérifié qu'il faut bien saisir le chiffre associé à une carte déjà posée afin de l'ajouter et qu'on nous demande une nouvelle saisie si l'utilisateur ne saisit pas quelque chose de correct.
- [x] J'ai vérifié qu'on ne peut pas poser une carte à un endroit déjà pris
- [x] J'ai vérifié que la direction saisie est bien suivie en vérifiant que si je saisis "B" alors la carte que je pose est en-dessous de la carte que l'on avait séléctionné préalablement.
J'ai ensuite vérifié que l'on devait saisir l'intégralité des cartes à poser afin de lancer la phase 2 de la manche

### Aléatoire

J'ai pu vérifier que l'ordre de début de partie était aléatoire en vérifiant qu'en lançant
plusieurs parties alors ce n'était pas toujours la même faction qui commence.
J'ai vérifié également que la main n'était pas toujours la même à chaque début de partie.

### Autres tests

- [x] Vérifier qu'on ne peut pas remelanger plusieurs fois par partie
- [x] Vérifier que mettre toutes les cartes sur la gauche de la précédente ne cause pas une erreur de segmentation (jouer sur la limite de la grille de taille 32)
- 

## Valgrind

Afin de vérifier qu'il n'y a pas de fuite mémoire, j'ai utilisé valgrind que ce soit au lancement du programme avec:
```
valgrind ./main
```
ou au lancement des tests unitaires
```
valgrind ./main --test
```
Lorsque j'ai lancé mes tests unitaires, le nombre de blocs perdus étaient de 0 ce qui fait
qu'il n'y a aucune fuite mémoire puisque j'ai fait des free à toutes les fonctions de tests.

Concernant le programme quand je l'ai lancé avec
```
valgrind --leak-check=full ./main
```
je n'ai globalement pas eu de fuites mémoires associés au jeu en lui même mais certains effets de carte en provoquaient comme
Soirees Sans Alcool ou encore Eric Lejeune.
Il m'est arrivé aussi de perdre quelques blocs mais en général cela ne dépasse pas les 5 blocs.