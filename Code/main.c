// gcc -o a.out main.c menu.c -lncurses

#include <ncurses.h> // stdio.h est inclue dans ncurses.h
#include <stdlib.h>
#include "menu.h" //permets de gerer l'affichage de l'ecran titre et des différentes
                 // erreures

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

    getmaxyx(stdscr, rows, cols);

    refresh() ;

    if(rows < 30 || cols < 100) { //code permetant de stopper le programme 
                                 // si le terminal n'as pas les bonne dimension

        erreur10(rows,cols); //affichage du retours erreur avec des information 
        return 0 ;          //supplémentaire comme la taille du terminal
    }

    box(menuBox, 0 ,0) ; //affiche la boite
    wrefresh(menuBox) ; 

    affiche_titre(menuBox) ; //affiche le titre + option de l'écran d'acceuille
    affiche_option(menuBox) ;
    wrefresh(menuBox) ; //il faut refresh a chaque changement de valeur btw

    mvwgetstr(menuBox, 15, 40 , userGamemodeChoice) ; //recupere le choix de l'utilisateur
    wrefresh(menuBox) ;

    switch (userGamemodeChoice[0]) //permet de decider le mode choisie par l'utilisateur
    {
    case '1': //Mode 1 joueur
        mvwprintw(menuBox,17,4,"tu as presse 1") ;
        break;
    case '2' : //Autoplay
        mvwprintw(menuBox,17,4,"tu as presse 2") ;
        break ; 
    default: //Affichage de l'erreur d'entrée utilisateur (erreur 11)
        erreur11() ;
        return 0 ;
    }
    wrefresh(menuBox) ; 

    getch(); //recuperer l'input pour finir le programme main
    endwin() ; //fin de du processus ncruses 

    return 0 ; 

}