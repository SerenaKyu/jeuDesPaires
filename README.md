# Jeu des paires :black_joker:

- ### Le but du jeu :black_flag: 

 Le jeu des paires est un jeu de carte ou le but est de trouver le plus rapidement des ensembles de cartes identiques, soyer le plus rapide à trouver toute les paires afin de pouvoir marquer le meilleur score possible ! 

---

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

gcc -o a.out ../Code/main.c ../Code/menu.c ../Code/game.c -lncurses

./a.out
```
> *il est quand meme préférable de passer par le makefile présent dans le dossier Output*

---

- ### Commandes de l'interface du jeu :video_game:

- ##### Liste des commandes utilisateur possible dans le programme :

    - **q** = Mettre fin au jeu.
    - ****

---

- ### ToDo list :memo::white_check_mark:

Voici notre avancement actuelle sur le projet, ce qui reste à faire et à implémenter

*Version actuelle du jeu : v0.4.4*

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
|Motif déco cartes         |:x:                       |        |
|Défini Aléatoire cartes   |:eight_pointed_black_star:|        |
|Gestion des inputs jeu    |:white_check_mark:        |**v0.3**|
|Choix de la carte jeu     |:eight_pointed_black_star:|        |
|Chronomètre               |:white_check_mark:        |**v0.2**|
|Comparaison des cartes    |:eight_pointed_black_star:|        |
|Couleur des cartes status |:eight_pointed_black_star:|        |
|Ecriture highscore        |:white_check_mark:        |**v0.4**|
|Highscores stockage       |:white_check_mark:        |**v0.4**|
|Temps écoulée             |:white_check_mark:        |**v0.2**|
|Décision auto play        |:x:                       |        |
|SiteWeb                   |:x:                       |        |

---

- ### PatchNotes :bookmark_tabs:

*Version actuelle du jeu : v0.4.4*

- ###### v0.4.4 :
> - déplacement des features d'aprés jeu dans `aftergame.c`

- ###### v0.4.3 :
> - Modification de la touche de fin de tâche du jeu basé sur les besoin du cahier des charges

- ###### v0.4.2 :
> - Optimisation de la fonction de la gestion du score
> - Mise en place de la fenetre de défaite différentes de la fenetre de victoire
> - Ajout de commentaire à la fonction d'écriture/lecture du fichier et gestion du scores
> - réecriture des .h

- ###### v0.4.1 :
> - Implémentation des features suivantes :
>   - Outil de debug suivant :
>       - Menu debug pour choisir ces option
>       - Possibilité de rénitialiser le fichier ``jeuhighscore.txt``
>   - Une sécurité pour l'utilisateur d'entrer des noms en dessous et au dessus de 4 charactére
> - Résolution d'un probléme qui faisait que les noms soit mal lu
> - Correction d'un bug qui faisait que les sortie erreur ne s'affichait pas 

- ##### v0.4 :
> - Implémentation des features suivantes :
>   - Ecrans de victoire aprés la fin du jeu.
>   - Ecriture et lecture des highscores
>   - Jeu en Mode débug (accéssible avec *3* dans le menu)
> - Réecriture du code de la features timer avec les paramétres suivants
>   - Calcul des secondes et millisecondes via une structure annexe 

- ###### v0.3.1 :
> - Optimisation général dans le code du jeu :
>   - Calcul du timer du jeu déplacé dans une fonction
>   - Debug input déplacé dans une fonction

- ##### v0.3 :
> - Implémentation des features suivantes :
>   - Détection des inputs utilisateur
>   - Rendre le curser invisible pendant le jeu
>   - Outil de debug suivants :
>       -   Savoir la dernière input user
>       -   Quitter rapidement le programme avec la touche *Echap*

- ###### v0.2.1 :
> - Correction de la commande a rentrée dans le terminal pour compiler.
> - Réecriture du code de la features timer avec les paramétres suivants :
>   - Utilisation de la librairie "time.h" au lieu de ncurses pour une meilleur gestion du temps
>   - Implementation direct dans la fonction de jeu pour l'utiliser en même temps que le jeu 
>   - mise en place du nodelay et timeout pour la gestion des inupts du jeu

- ##### v0.2 :
> - Implémentation des features suivantes :
>   - Lancement du jeu à 1 joueur
>   - Chronometre
>   - Stop programme quand temps écoulée 

- ###### v0.1.1 :
> - Résolution d'un probléme de compilation avec le makefile

- ##### v0.1 :
> - Mise en place arborescence fichier
> - Ecriture du ```README.md```
> - Implémentation des features suivantes : 
>   - Ecran titre
>   - Erreur terminal si il est trop petit
>   - Selection du mode de jeu
>   - Erreur de sélection du mode de jeu si valeur incorrect
> - Mise en ligne sur GitHub du code sources










