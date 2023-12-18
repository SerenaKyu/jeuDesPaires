# Jeu des paires :black_joker:

- ### Le but du jeu :black_flag: 

 Le jeu des paires est un jeu de cartes où le but est de former le plus rapidement possible des ensembles de cartes identiques, soyez le plus rapide pour trouver tous les pairs afin de pouvoir inscrire le meilleur score ! 

---

 - ### Installation, Compilation & OS disponible :arrow_down:

Le programme est disponible sur n'importe quelle distribution **Linux.:penguin:**. Pour compiler le code, vous aurez besoin de :

##### 1. Installer la librairie ncurses sur votre machine :blue_book: 

- Ce programme fonctionne grâce à la librairie ncurses, il faut donc la télécharger au préalable (:page_facing_up:[Fiche d'aide sur l'installation de la librairie ncurses pour les distributions les plus populaires](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/?__cf_chl_tk=rluPuC6Rq0fQWuxExTTKQpOTJpms0k3zLRHfU842vQY-1700225221-0-gaNycGzNDqU))

##### 2. Télécharger les fichiers sources du programme sur votre ordinateur :floppy_disk: 

- Cloner le repository (:page_facing_up:[Fiche d'aide pour cloner un repository](https://docs.github.com/fr/repositories/creating-and-managing-repositories/cloning-a-repository))
- Ou téléchargez-le manuellement en haut de la page avec le boutton vert "Code"

##### 3. Compiler le code et le lancer dans le terminal :minidisc:

- Pour compiler le code, verifiez que vous possédez GCC GNU sur votre machine (:arrow_down:[Lien pour installer GCC GNU](https://doc.ubuntu-fr.org/gcc))

- Pour compiler le code de manière simple et lancer le jeu il faut :

    1. Se rendre dans le fichier "télécharger" grâce au terminal Linux et aller dans le dossier : ```jeuDesPaires/Compil/Linux``` 
    2. Lancer le makefile grâce à la commande : ```make```
    3. le fichier de lancement sera alors disponible et prêt à être lancé via la commande ```./game.exe``` pour y jouer
- Vous pouvez aussi le compiler directement sans passer par un makefile déjà présent : 
```
gcc -c game.exe ../../Code/ObjectFile/main.c ../../Code/ObjectFile/menu.c ../../Code/ObjectFile/game.c ../../Code/ObjectFile/aftergame.c -lncurses

./game.exe
```
> *il est quand-même préférable de passer par le makefile présent dans le dossier Compil/Linux*

---

- ### Commandes de l'interface du jeu :video_game:

- ##### Liste des commandes utilisateur possibles dans le programme :

    - **q** : Mettre fin au jeu
    - **z** : Se déplacer vers la droite
    - **a** : Se déplacer vers la gauche
    - **e** : Séléctionner la cartes

---

- ### ToDo list :memo::white_check_mark:

Voici notre avancement actuel sur le projet, ce qui reste à faire et à implémenter

*Version actuelle du jeu : v1.0.1*

> **Légende :**
>
> - :white_check_mark: = Fait et implémenté dans code principal
> - :eight_pointed_black_star: = Codé mais non implémenté dans cette version
> - :x: = Pas encore fait

|Fonctionnalité            |Status                    |Version |
|--------------------------|--------------------------|--------|
|Écran Titre               |:white_check_mark:        |**v0.1**|
|Sélection du mode de jeu  |:white_check_mark:        |**v0.1**|
|Test résolution Terminal  |:white_check_mark:        |**v0.1**|
|Lancement jeu 1 joueur    |:white_check_mark:        |**v0.2**|
|Lancement jeu AutoPlay    |:x:                       |        |
|Motifs décoratifs cartes  |:eight_pointed_black_star:|        |
|Cartes aléatoires         |:white_check_mark:        |**v1.0**|
|Gestion des inputs jeu    |:white_check_mark:        |**v0.3**|
|Choix de la carte jeu     |:white_check_mark:        |**v0.5**|
|Chronomètre               |:white_check_mark:        |**v0.2**|
|Comparaison des cartes    |:white_check_mark:        |**v0.5**|
|Couleur des cartes status |:white_check_mark:        |**v0.5**|
|Écriture highscore        |:white_check_mark:        |**v0.4**|
|Highscores stockage       |:white_check_mark:        |**v0.4**|
|Temps écoulé              |:white_check_mark:        |**v0.2**|
|Décision AutoPlay         |:x:                       |        |
|Site Web                  |:x:                       |        |
|Portage Windows           |:x:                       |        |

---

- ### PatchNotes :bookmark_tabs:

Accédez à tous les patchnotes :page_facing_up:[Liste complète](./PATCH.md)

**Dernier Patch :**

- ###### v1.0.1 :
> - Correction d'un bug qui rendais la lecture et ecriture du classement impossible