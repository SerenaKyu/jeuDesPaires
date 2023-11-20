#include <ncurses.h>
#include <stdlib.h>

void affiche_tipTool(WINDOW *myWindow) { //affiche le toolTip du jeu(resume de ce qui faut faire)
    const char *texte[2] = {"Jeu des paires","Trouver les paires en un minimun de temps"} ;
    
    for(int i = 0;i < 2 ;i++) {
        mvwprintw(myWindow,1+i,1,"%s",texte[i]) ; //print dans la fenetre le tooltip
    }
}

void timer(WINDOW *myWindow) { //timer du jeu, permet de chronomettrer le jeu

    float secondes = 0; 

        do { //reaffiche le chrono updater tout les 0.1 secondes
        mvwprintw(myWindow,1,1,"Chrono  : %.1fs", secondes); //affichage dans la fenetre du chrono
        wrefresh(myWindow); //update la fenetre
        secondes = secondes+0.1; //ajoute 0.1 
        napms(100);             //tout les 100ms
    } while (secondes < 3); //temps du chrono (dans la version final, on sera a 120s)
}

void game_1player() { //fonction du jeu à 1 joueur

    WINDOW *tipToolBox = newwin(4,70,0,0) ; //Fenetre du toolTip du jeu
    WINDOW *chronoBox = newwin(4,29,0,71) ; //Fenetre du chrono du jeu

    refresh() ; 

    box(tipToolBox,0,0) ; //affichage des 2 fenetre
    box(chronoBox,0,0) ;

    affiche_tipTool(tipToolBox) ; //affiche la description

    wrefresh(tipToolBox) ;
    wrefresh(chronoBox) ;

    timer(chronoBox) ; //chronometrage du jeu
}