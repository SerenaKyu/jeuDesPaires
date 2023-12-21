#include <curses.h> // stdio.h est inclue dans ncurses.h
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "menu.h" // Permet de gérer l'affichage de l'écran titre et des différentes erreurs
#include "game.h"// Permet de gérer le jeu

#define TAILLE_T 50

/*
Fonction : main
Traitement : Affiche le menu de démarrage et demande un choix de mode de jeu à l'utilisateur (1 joueur, autoplay, mode debug...)
Retour : Une fonction main retourne 0 par défaut
*/
int main() {

    initscr() ; // Initialisation de la fenêtre

    int height, width, start_x, start_y ,cols,rows; // Initialisation des variables de configuration de la boîte du menu
    height = 30 ; // Définition de la longueur de la boîte
    width = 100 ; // Définition de la largeur de la boîte
    start_x = start_y = 0 ; // Définition des variables de déplacement 

    char userGamemodeChoice[TAILLE_T]; // Chaîne de caractères qui permet de récupérer le choix de mode de l'utilisateur

    WINDOW *menuBox = newwin(height,width,start_y,start_x) ; // Définition de la taille de la fenêtre 
    if(menuBox == NULL) {
        endwin() ;
        fprintf(stderr,"Erreur 15 : Chargement des ressources ncurses impossible") ;
        return 0;
    }

    nodelay(stdscr,TRUE); // N'attend pas pour effectuer un while
    getmaxyx(stdscr, rows, cols); // Récupere la taille du terminal

    refresh() ;

    if(rows < 30 || cols < 100) { // Code permetant de stopper le programme si le terminal n'a pas les bonnes dimensions
        erreur10(rows,cols); // Affichage du retour erreur avec des informations supplémentaires, comme la taille du terminal
        return 0 ;
    }

    box(menuBox,0,0) ; // Affiche la boîte
    wrefresh(menuBox) ; 

    affiche_titre(menuBox) ; // Affiche le titre et les options de l'écran d'accueil
    affiche_option(menuBox) ;
    wrefresh(menuBox) ; // Rafraîchi à chaque changement de valeurs

    mvwgetnstr(menuBox, 17, 40 , userGamemodeChoice,1) ; // Récupère le choix de l'utilisateur
    wrefresh(menuBox) ;

    switch (userGamemodeChoice[0]) // Permet de décider le mode choisi par l'utilisateur
    {
    case '1': // Mode 1 joueur
        wclear(menuBox) ; // Enlève l'affichage de l'écran titre
        wrefresh(menuBox) ; // Refresh après l'avoir enlevé pour pouvoir la mettre à jour

        game_1player(false) ; // Début du jeu à 1 joueur
        break;
    case '2' : // Autoplay
        wclear(menuBox) ; // Enlève l'affichage de l'écran titre
        wrefresh(menuBox) ; // Refresh après l'avoir enlevé pour pouvoir la mettre à jour

        game_autoplay() ; // Début du en Mode autoplay
        break ; 
    case '3'  :
        wclear(menuBox) ; // Enlève l'affichage de l'écran titre
        wrefresh(menuBox) ; // Refresh après l'avoir enlevé pour pouvoir la mettre à jour

        menuDebug() ; // Début du jeu à 1 joueur
        break;
    default: // Affichage de l'erreur d'entrée utilisateur (erreur 11)
        erreur11() ;
        return 0 ;
    }

    getch(); // Récupère l'input pour finir la fonction main
    endwin() ; // Fin du processus ncurses

    return 0 ; 

}