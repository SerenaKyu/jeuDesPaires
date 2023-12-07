#include <ncurses.h> // stdio.h est inclue dans ncurses.h
#include <stdlib.h>
#include <stdbool.h>

#include "menu.h" //Permets de gerer l'affichage de l'ecran titre et des différentes
                 // erreures
#include "game.h"//Permets de gerer le jeu

#define TAILLE_T 50

int main(int argc , char ** argv) {

    //initialisation de la fenetre
    initscr() ; 

    //initialisation des variables de configuration de la boite du menu
    int height, width, start_x, start_y ,cols,rows;
    height = 30 ; //definition de la longeur de la boite
    width = 100 ; //definition de la largeur de la boite
    start_x = start_y = 0 ; //definition des variables de deplacement 

    char userGamemodeChoice[TAILLE_T]; //chaine de charactere qui permet de recup le choix de mode de l'utilisateur

    WINDOW *menuBox = newwin(height,width,start_y,start_x) ; //definition de la taille de la fenetre 

    nodelay(stdscr,TRUE); //enleve le delay de refresh de la window
    getmaxyx(stdscr, rows, cols); //recupere la taille du terminal

    refresh() ;

    if(rows < 30 || cols < 100) { //code permetant de stopper le programme 
                                 // si le terminal n'as pas les bonne dimension

        erreur10(rows,cols); //affichage du retours erreur avec des information 
        return 0 ;          //supplémentaire comme la taille du terminal
    }

    box(menuBox,0,0) ; //affiche la boite
    wrefresh(menuBox) ; 

    affiche_titre(menuBox) ; //affiche le titre + option de l'écran d'acceuille
    affiche_option(menuBox) ;
    wrefresh(menuBox) ; //il faut refresh a chaque changement de valeur btw

    mvwgetnstr(menuBox, 17, 40 , userGamemodeChoice,1) ; //recupere le choix de l'utilisateur
    wrefresh(menuBox) ;

    switch (userGamemodeChoice[0]) //permet de decider le mode choisie par l'utilisateur
    {
    case '1': //Mode 1 joueur
        wclear(menuBox) ; //eneleve l'affichage de l'ecran titre
        wrefresh(menuBox) ; //refresh aprés l'avoir enlever pour pouvoir la mettre a jour

        game_1player(false) ; //Debut du jeu à 1 joueur
        break;
    case '2' : //Autoplay
        mvwprintw(menuBox,17,4,"Mode AutoPlay") ;
        break ; 
    case '3'  :
        wclear(menuBox) ; //eneleve l'affichage de l'ecran titre
        wrefresh(menuBox) ; //refresh aprés l'avoir enlever pour pouvoir la mettre a jour

        menuDebug() ; //Debut du jeu à 1 joueur
        break;
    default: //Affichage de l'erreur d'entrée utilisateur (erreur 11)
        erreur11() ;
        return 0 ;
    }

    getch(); //recuperer l'input pour finir le programme main
    endwin() ; //fin de du processus ncruses 

    return 0 ; 

}