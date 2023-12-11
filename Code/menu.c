#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#include "game.h"

#define NOMBRE_LIGNE_TITRE 7
#define NOMBRE_OPTION 5
#define TAILLE_T 50

void affiche_titre(WINDOW * myWindow) { //permet d'afficher le titre

    const char *ligne_texte[NOMBRE_LIGNE_TITRE]  = {"------------------------------------------------------------------------------------------",
                                                    " ******  ***** **  **   ****     *****   ****   *****    ***   ****** *****   *****  **** ",
                                                    "   **   **     **  **   ** **   **      ***     **  **  ** **    **   **  ** **     ***   ",
                                                    "   **   ****   **  **   **  *   ****    ****    *****   *****    **   *****  ****    **** ",
                                                    "   **   **     **  **   ** **   **        ***   **     **   **   **   **  ** **        ***",
                                                    " ***     *****  ****    ****     *****  ****    **     **   ** ****** **  **  *****  **** ", 
                                                    "------------------------------------------------------------------------------------------",};
    
    for(int i = 0 ; i < NOMBRE_LIGNE_TITRE ;i++){
        mvwprintw(myWindow,i+1,4,"%s",ligne_texte[i]) ; //affiche chaque ligne du tableau 1 a 1
        wrefresh(myWindow); 

    }
}

void affiche_option(WINDOW * myWindow) { //permet d'afficher les options disponible

    int ligne = NOMBRE_LIGNE_TITRE + 2 ; //permet d'initialiser la ligne de depart de l'affichage 
                                         //de chaque paramettre du tableau
    const char *option[NOMBRE_OPTION] = {"Menu","1. 1 Joueur","2. Autoplayer","3. Mode debug","Entrer l'option de votre de choix :"} ;

    for(int i = 0 ; i < NOMBRE_OPTION ; i++) {
        mvwprintw(myWindow,ligne + i,4,"%s",option[i]) ;
        wrefresh(myWindow) ;
        ligne++ ; //permet de sauter des lignes entre chaque option
    }
}

void reset_score() {
    FILE* highscore ;

    highscore = fopen("../Data/jeuhighscore.txt", "w");

    if(highscore == NULL){ // Vérifie si le fichier jeuhighscore.txt a bien été ouvert
        printf("Erreur lors de l'écriture du fichiers des scores");
        exit(2);
    } 

    fprintf(highscore, "1 JACK 90.0\n") ;
    fprintf(highscore, "2 PAUL 100.0\n") ;
    fprintf(highscore, "3 ZACK 110.0\n") ;

    fclose(highscore);
    
    endwin() ;
    fprintf(stderr,"Fichier scores rénitialisé par défaut\n") ;
}

void erreur10(int rows, int cols) { //affichage de l'erreur et arret de la fenetre
                                    //Erreur 10 = fenetre trop petite

    endwin() ;               
    fprintf(stderr, "Erreur 10 : Le terminal est trop petit\n\n"); 
    fprintf(stderr, "Ce dernier dois minimum respecter la tailles suivantes :\n");
    fprintf(stderr,"Longeur : 100\nLargeur : 30\n\n") ;
    fprintf(stderr,"Le terminal est de taille actuelle :\n") ;
    fprintf(stderr,"Longeur : %d\nLargeur :%d\n",rows,cols) ;
}

void erreur11() { //affichage de l'erreur et arret de la fenetre
                  //Erreur 11 = mauvais choix d'input dans le menu
    endwin() ;
    fprintf(stderr,"Erreur 11 : choix du mode de jeu incorrect\n") ;
}

void menuDebug() {
    WINDOW * debugBox = newwin(30,100,0,0);
    box(debugBox,0,0) ;

    wrefresh(debugBox) ;

    char debugChoice[TAILLE_T];

    mvwprintw(debugBox,1,1,"Bienvenue sur la fenetre de debug, merci de choisir une option") ;
    mvwprintw(debugBox,3,1,"1 - Lancer le jeu en mode debug") ;
    mvwprintw(debugBox,4,1,"2 - Renitialiser les scores") ; 

    mvwgetnstr(debugBox, 6, 1 , debugChoice,1) ;

    switch (debugChoice[0]){
        case '1' :
            wclear(debugBox) ; //eneleve l'affichage de l'ecran titre
            wrefresh(debugBox) ; //refresh aprés l'avoir enlever pour pouvoir la mettre a jour

            game_1player(true) ;
            break;
        case '2' :
            reset_score() ;
            break ;
        default :
            break;
    }
}