# Comment jouer à Oriieflamme ?

Avec le LOT C, vous pouvez désormais jouer à Oriieflamme avec une interface graphique web avec deux joueurs sur le même 
pc puisqu'actuellement
nous n'avons pas de serveur en ligne pour héberger le jeu et qu'il n'est pas encore prêt pour cela de toute façon.

## Préparer le lancement

Afin de pouvoir utiliser des websocket nous avons ajouté à notre code la librairie wsServer trouvable à l'adresse Github 
suivante: https://github.com/Theldus/wsServer
Nous avons mis la librairie dans le répertoire lib. Il va d'abord falloir compiler les fichiers de cette librairie,
pour cela, il faut aller dans le répertoire wsServer et exécuter la commande make clean all
```
cd code/lib/wsServer
make clean all
```
Ensuite retourner à la racine du répertoire code et exécuter make clean all egalement
```
cd ../../
make clean all
```
Si tout se passe bien la compilation a fonctionnée, et vous pouvez désormais lancer le serveur

## Lancer une partie

Executer la commande suivante depuis le répertoire code afin de lancer le main en mode serveur, s'il n'y a pas l'option
--online cela lance le jeu comme avant.
```
./bin/main --online
```

Une fois, le serveur lancé, il faut ouvrir le fichier game.html dans un navigateur web comme Google Chrome par exemple,
et l'ouvrir une seconde fois dans un autre onglet pour avoir deux joueurs. 
Attention, si vous rafraichissez une des deux pages, cela aura pour
conséquence une fermeture de la connexion avec le serveur qui se coupe automatiquement quand un des joueurs n'est plus
connecté, il faudra donc relancer le serveur.

En cas de problèmes, contactez JUSSEAUME Jonathan par mail et s'il y a besoin d'une démonstration en présentiel
avec tous les membres de l'équipe, nous sommes disponibles.