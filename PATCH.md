- ### PatchNotes :bookmark_tabs:

*Version actuelle du jeu : v1.0*

- #### v1.0 :
> - Jeu à 1 joueur totalement fonctionnel et implémenté.
> - Changement de la structures de la stucture du projet :
>   - Les patch sont desormais déplacé dans un autres fichier

- ##### v0.5 : 
> - Implémentation des features suivantes :
>   - Affichages des 12 cartes intétegré
>   - Controle de déplacement et de séléction des cartes
>   - Gestion des différents status des cartes
>   - Algorythme de comparaison des cartes
>   - Condition de victoire
> - Correction d'un Bug de compilation qui faisait que les fichiers .o ne trouvais pas leur dossier.
> - Correction d'un Bug qui faisait que le programme ne conservais pas réellement la derniere input pour le mode Debug.

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










