# Jeu des paires :black_joker:

- ### Le but du jeu :black_flag: 

 Le jeu des paires est un jeu de carte ou le but est de trouver le plus rapidement des ensembles de cartes identiques, soyer le plus rapide à trouver toute les paires afin de pouvoir marquer le meilleur score possible ! 

---

 - ### Installation, Compilation & OS disponible :arrow_down:

Le programme est seulement disponible sur n'importe quel distribution **Linux.:penguin:** Pour compiler le code, vous aurez besoin au de :

##### 1. Installer la librairie ncurses sur votre machine:blue_book: 

- Ce programme fonctionne grace à la librairie ncurses, il faut donc la telecharger à l'avance(:page_facing_up:[Fiche d'aide sur l'installation de ncurses pour les distribution les plus populaires.](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/?__cf_chl_tk=rluPuC6Rq0fQWuxExTTKQpOTJpms0k3zLRHfU842vQY-1700225221-0-gaNycGzNDqU))

##### 2. Téléchager les fichier sources du programme sur votre ordinateur :floppy_disk: 

- Cloner le repository (:page_facing_up:[Fiche d'aide pour cloner un repository](https://docs.github.com/fr/repositories/creating-and-managing-repositories/cloning-a-repository))
- Ou télécharger le manuellement en haut de la page avec le boutton vert "Code"

##### 3. Compiler le code et lancer le dans le terminal :minidisc:

- Pour compiler le code, verifier que vous possedée GCC GNU sur votre machine (:arrow_down:[Lien pour installer GCC GNU](https://doc.ubuntu-fr.org/gcc))

- Pour compiler le code de maniere simple et lancer le jeu il faut :

    1. Ce rendre dans le fichier télécharger grace au terminal linux et aller dans le dossier : ```jeuDesPaires/Compil/Linux``` 
    2. Lancer le makefile grace a la commande : ```make```
    3. le fichier de lancement sera alors disponible et pret a lancer via la commande```./game.exe``` pour y jouer
- Vous pouvez aussi le compiler directement sans passer par un makefile déja présent : 
```
gcc -c game.exe ../../Code/ObjectFile/main.c ../../Code/ObjectFile/menu.c ../../Code/ObjectFile/game.c ../../Code/ObjectFile/aftergame.c -lncurses

./game.exe
```
> *il est quand meme préférable de passer par le makefile présent dans le dossier Compil/Linux*

---

- ### Commandes de l'interface du jeu :video_game:

- ##### Liste des commandes utilisateur possible dans le programme :

    - **q** : Mettre fin au jeu.
    - **z** : Se déplacer vers la droite
    - **a** : Se déplacer vers la gauche
    - **e** : Séléctionner la cartes

---

- ### ToDo list :memo::white_check_mark:

Voici notre avancement actuelle sur le projet, ce qui reste à faire et à implémenter

*Version actuelle du jeu : v1.0*

> **Légende :**
>
> - :white_check_mark: = Fait et implémenté dans code principale
> - :eight_pointed_black_star: = Codé mais non implémenté dans cette version
> - :x: = Pas encore fait

|Fonctionnalité            |Status                    |Version |
|--------------------------|--------------------------|--------|
|Ecran Titre               |:white_check_mark:        |**v0.1**|
|Séléction du mode de jeu  |:white_check_mark:        |**v0.1**|
|Test résolution Terminal  |:white_check_mark:        |**v0.1**|
|Lancement jeu 1 joueur    |:white_check_mark:        |**v0.2**|
|Lancement jeu Autoplay    |:x:                       |        |
|Motif décoratif cartes    |:eight_pointed_black_star:|        |
|Cartes aléatoires         |:white_check_mark:        |**v1.0**|
|Gestion des inputs jeu    |:white_check_mark:        |**v0.3**|
|Choix de la carte jeu     |:white_check_mark:        |**v0.5**|
|Chronomètre               |:white_check_mark:        |**v0.2**|
|Comparaison des cartes    |:white_check_mark:        |**v0.5**|
|Couleur des cartes status |:white_check_mark:        |**v0.5**|
|Ecriture highscore        |:white_check_mark:        |**v0.4**|
|Highscores stockage       |:white_check_mark:        |**v0.4**|
|Temps écoulée             |:white_check_mark:        |**v0.2**|
|Décision auto play        |:x:                       |        |
|SiteWeb                   |:x:                       |        |
|Portage Windows           |:x:                       |        |

---

- ### PatchNotes :bookmark_tabs:

Acceder à tous les patchnotes :page_facing_up:[Liste complètes](./PATCH.md)

**Dernier Patch :**

- ###### v1.0.1 :
> - Correction d'un bug qui rendais la lecture et ecriture du classement impossible