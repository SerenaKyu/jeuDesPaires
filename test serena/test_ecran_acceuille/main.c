#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "tools.h"
#include <string.h>

int main(int argc , char ** argv) {

    //initialisation de la fenetre
    initscr() ; 

    //initialisation des variables de configuration de la boite du menu
    int height, width, start_x, start_y ;
    height = 10 ;
    width = 20 ; 
    start_x = start_y = 0 ;
    WINDOW *menuBox = newwin(height,width,start_y,start_x) ;

    refresh() ;

    box(menuBox, 0 ,0) ; 
    wrefresh(menuBox) ; 


    getch(); //recuperer les input

    endwin() ;
    //fin de ncruses + clear ram

    return 0 ; 

}


/*
int main(void) {
    WINDOW *boite; //creation de ma fenetre 
    char *msg= "Test";
    initscr();
    int taille= strlen(msg);    
    boite= subwin(stdscr, 20, 20, LINES / 2,   (COLS / 2) - (taille / 2)); //definir taille de la boite , dans l'ordre : ? tailles longeur, tailles largeur , position x dans fenetre, position y 
    wborder(boite, '|', '|', '-', '-', '+', '+', '+', '+'); // definir caractere de la fenetre  

    mvwprintw(boite, LINES / 2, (COLS / 2) - (taille / 2), msg);
    wrefresh(boite);
   
    getch();
    endwin();

    free(boite);
    
    return 0;
} */

/*

    WINDOW *boite;
    char *msg= "Texte au centre";
    int taille= strlen(msg);
    
    initscr();
    while(1) {
        clear();    // Efface la fenêtre (donc l'ancien message)
        mvprintw(LINES/2, (COLS / 2) - (taille / 2), msg);
        refresh();
        if(getch() != 410)
            break;
    }
    
    endwin()

*/

