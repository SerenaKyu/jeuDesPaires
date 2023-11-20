#include <ncurses.h>
#include <stdlib.h>

#define NOMBRE_LIGNE_TITRE 7
#define NOMBRE_OPTION 4

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
    const char *option[NOMBRE_OPTION] = {"Menu","1. 1 Joueur","2. Autoplayer","Entrer l'option de votre de choix :"} ;

    for(int i = 0 ; i < NOMBRE_OPTION ; i++) {
        mvwprintw(myWindow,ligne + i,4,"%s",option[i]) ;
        wrefresh(myWindow) ;
        ligne++ ; //permet de sauter des lignes entre chaque option
    }
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