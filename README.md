# Jeu des paires :black_joker:

- ### Le but du jeu :video_game: 

 Le jeu des paires est un jeu de carte ou le but est de trouver le plus rapidement des ensembles de cartes identiques, soyer le plus rapide à trouver toute les paires afin de pouvoir marquer le meilleur score possible ! 

 - ### Installation, Compilation & OS disponible :arrow_down:

Le programme est seulement disponible sur n'importe quel distribution **Linux.:penguin:** Pour compiler le code, vous aurez besoin au de :

##### 1. Installer la librairie ncurses sur votre machine:blue_book: 

- Ce programme fonctionne grace à la librairie ncurses, il faut donc la telecharger à l'avance(:link:[Fiche d'aide sur l'installation de ncurses pour les distribution les plus populaires.](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/?__cf_chl_tk=rluPuC6Rq0fQWuxExTTKQpOTJpms0k3zLRHfU842vQY-1700225221-0-gaNycGzNDqU))

##### 2. Téléchager les fichier sources du programme sur votre ordinateur :floppy_disk: 

- Cloner le repository (:link:[Fiche d'aide pour cloner un repository](https://docs.github.com/fr/repositories/creating-and-managing-repositories/cloning-a-repository))
- Ou télécharger le manuellement en haut de la page avec le boutton vert "Code"

##### 3. Compiler le code et lancer le dans le terminal :minidisc:

- Pour compiler le code, verifier que vous possedée GCC GNU sur votre machine (:link:[Lien pour installer GCC GNU](https://doc.ubuntu-fr.org/gcc))

- Pour compiler le code de maniere simple et lancer le jeu il faut :

    1. Ce rendre dans le fichier télécharger grace au terminal linux et aller dans le dossier : ```jeuDesPaires/Ouput``` 
    2. Lancer le makefile grace a la commande : ```make```
    3. le fichier de lancement sera alors disponible et pret a lancer via la commande```./a.out``` pour y jouer
- Vous pouvez aussi le compiler directement sans passer par un makefile déja présent : 
```
cd jeuDesPaires/Output

gcc -o a.out ../Code/ObjectFile/main.o ../Code/ObjectFile/menu.o -lncurses

./a.out
```
> *il est quand meme préférable de passer par le makefile présent dans le dossier Output* 

- ### ToDo list :memo::white_check_mark:

Voici notre avancement actuelle sur le projet, ce qui reste à faire et à implémenter

*Version actuelle du jeu : v0.1.1*

> **Légende :**
>
> - :white_check_mark: = Fait et implémenter dans code principale
> - :eight_pointed_black_star: = Codé mais non implémenter dans cette version
> - :x: = Pas encore fait

|Fonctionnalité            |Status                    |Version |
|--------------------------|--------------------------|--------|
|Ecran Titre               |:white_check_mark:        |**v0.1**|
|Séléction du mode de jeu  |:white_check_mark:        |**v0.1**|
|Test résolution Terminal  |:white_check_mark:        |**v0.1**|
|Lancement jeu 1 joueur    |:x:                       |        |
|Lancement jeu Autoplay    |:x:                       |        |
|Motif déco cartes         |:x:                       |        |
|Défini Aléatoire cartes   |:x:                       |        |
|Gestion des inputs jeu    |:eight_pointed_black_star:|        |
|Choix de la carte jeu     |:eight_pointed_black_star:|        |
|Chronomètre               |:eight_pointed_black_star:|        |
|Comparaison des cartes    |:x:                       |        |
|Couleur des cartes status |:x:                       |        |
|Ecriture highscore        |:x:                       |        |
|Highscores stockage       |:x:                       |        |
|Temps écoulée             |:x:                       |        |
|Decision auto play        |:x:                       |        |
|SiteWeb                   |:x:                       |        |

- ### PatchNotes :bookmark_tabs:

*Version actuelle du jeu : v0.1.1*

- ##### v0.1.1 :
> - Résolution d'un probléme de compilation avec le makefile

- ###### v0.1 :
> - Mise en place arborescence fichier
> - Ecriture du ```README.md```
> - Implémentation des features suivantes : 
>   - Ecran titre
>   - Erreur terminal si il est trop petit
>   - Selection du mode de jeu
>   - Erreur de sélection du mode de jeu si valeur incorrect
> - Mise en ligne sur GitHub du code sources










