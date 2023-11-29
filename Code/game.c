#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h> //librarie pour utiliser le chrono

void affiche_tipTool(WINDOW *chronoBox) { //affiche le toolTip du jeu(resume de ce qui faut faire)
    const char *texte[2] = {"Jeu des paires","Trouver les paires en un minimun de temps"} ;
    
    for(int i = 0;i < 2 ;i++) {
        mvwprintw(chronoBox,1+i,1,"%s",texte[i]) ; //print dans la fenetre le tooltip
    }
}

void game_1player() { //fonction du jeu à 1 joueur

    struct timeval start_time, current_time; //structure de temps en time.h

    int elapsed_time ; //peremts de calculer le temps qui c'est passer depuis le debut du timer
    int seconds, milliseconds ; //vas transformer ce temps en seconds et milliseconds

    WINDOW *tipToolBox = newwin(4,70,0,0) ; //Fenetre du toolTip du jeu
    WINDOW *chronoBox = newwin(4,29,0,71) ; //Fenetre du chrono du jeu
    box(tipToolBox,0,0) ; //affichage des 2 fenetre
    box(chronoBox,0,0) ;

    affiche_tipTool(tipToolBox) ; //affiche la description 
    wrefresh(tipToolBox) ;
    wrefresh(chronoBox) ;

    timeout(100) ;

    gettimeofday(&start_time, NULL) ; //recuperer la valeur de debut du chrono et du jeu

     do { //Lancement du jeu et du chrono
        gettimeofday(&current_time, NULL) ; // recupere la valeur a ce moment dans le timer

        elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 + 
    (current_time.tv_usec - start_time.tv_usec) / 1000; //calculer le temps depuis le debut du timer et la fin

        seconds = elapsed_time / 1000; //calcule la valeur en secondes
        milliseconds = (elapsed_time % 1000) / 100; //calcule la valeurs a coter en millisecondes

        mvwprintw(chronoBox,1,1,"Chrono  : %d.%ds", seconds,milliseconds); //affichage dans la fenetre du chrono
        wrefresh(chronoBox) ; //refresh la fenetre pour afficher le temps du chrono actuel

    } while (seconds < 5); //temps du chrono (dans la version final, on sera a 120s)
}