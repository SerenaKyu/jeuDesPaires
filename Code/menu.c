#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>

#include "game.h"

#define NOMBRE_LIGNE_TITRE 7
#define NOMBRE_OPTION 5
#define TAILLE_T 50

/*
Fonction : affiche_titre
Param : myWindow récupère la fenêtre sur laquelle la fonction va s'afficher
Traitement : Affiche ligne par ligne le titre "Jeu des paires" en gros
*/
void affiche_titre(WINDOW * myWindow) { // Permet d'afficher le titre

    const char *ligne_texte[NOMBRE_LIGNE_TITRE]  = {"------------------------------------------------------------------------------------------",
                                                    " ******  ***** **  **   ****     *****   ****   *****    ***   ****** *****   *****  **** ",
                                                    "   **   **     **  **   ** **   **      ***     **  **  ** **    **   **  ** **     ***   ",
                                                    "   **   ****   **  **   **  *   ****    ****    *****   *****    **   *****  ****    **** ",
                                                    "   **   **     **  **   ** **   **        ***   **     **   **   **   **  ** **        ***",
                                                    " ***     *****  ****    ****     *****  ****    **     **   ** ****** **  **  *****  **** ", 
                                                    "------------------------------------------------------------------------------------------",};
    
    for(int i = 0 ; i < NOMBRE_LIGNE_TITRE ;i++){
        mvwprintw(myWindow,i+1,4,"%s",ligne_texte[i]) ; // Affiche chaque ligne du tableau 1 à 1
        wrefresh(myWindow); 

    }
}

/*
Fonction : affiche_option
Param : myWindow récupère la fenêtre sur laquelle la fonction va s'afficher
Traitement : Affiche tous les modes de jeu qu'il est possible de séléctionner dans le menu
*/
void affiche_option(WINDOW * myWindow) { // Permet d'afficher les options disponibles

    int ligne = NOMBRE_LIGNE_TITRE + 2 ; // Permet d'initialiser la ligne de départ du tableau de l'affichage de chaque paramètre du tableau
    const char *option[NOMBRE_OPTION] = {"Menu","1. 1 Joueur","2. Autoplayer","3. Mode debug","Entrer l'option de votre de choix :"} ;

    for(int i = 0 ; i < NOMBRE_OPTION ; i++) {
        mvwprintw(myWindow,ligne + i,4,"%s",option[i]) ;
        wrefresh(myWindow) ;
        ligne++ ; // Permet de sauter une ligne entre chaque option
    }
}

/*
Fonction : reset_score
Traitement : Permet de réinitialiser le fichier des scores jeuhighscore.txt avec les valeurs par défaut
*/
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
    fprintf(stderr,"Fichier des scores réinitialisé par défaut\n") ;
}

/*
Fonction : erreur10
Param : rows récupère la longueur actuelle de la console et cols récupère la largeur actuelle de la colonne
Traitement : Cette fonction renvoie une erreur si la taille de la console est trop petite pour que le programme puisse être lancé, elle va renvoyer la taille actuelle de la console ainsi que la taille minimum pour que le programme puisse être lancé
*/
void erreur10(int rows, int cols) { // Affichage de l'erreur et arrêt de la fenêtre
                                    // Erreur 10 = Fenêtre trop petite

    endwin() ;               
    fprintf(stderr, "Erreur 10 : Le terminal est trop petit\n\n"); 
    fprintf(stderr, "Ce dernier doit au minimum respecter la taille suivante :\n");
    fprintf(stderr,"Longueur : 100\nLargeur : 30\n\n") ;
    fprintf(stderr,"Le terminal est actuellement de taille :\n") ;
    fprintf(stderr,"Longueur : %d\nLargeur :%d\n",rows,cols) ;
}

/*
Fonction : erreur11
Traitement : Renvoie une erreur si le mode de jeu séléctionné est incorrect
*/
void erreur11() { // Affichage de l'erreur et arrêt de la fenêtre
                  // Erreur 11 = Mauvais choix d'input dans le menu
    endwin() ;
    fprintf(stderr,"Erreur 11 : Choix du mode de jeu incorrect\n") ;
}

/*
Fonction : menuDebug
Traitement : Affiche la fenêtre avec les choix possibles du mode debug et permet au joueur de choisir
*/
void menuDebug() {
    WINDOW * debugBox = newwin(30,100,0,0);
    box(debugBox,0,0) ;

    wrefresh(debugBox) ;

    char debugChoice[TAILLE_T];

    mvwprintw(debugBox,1,1,"Bienvenue sur la fenêtre de debug, merci de choisir une option") ;
    mvwprintw(debugBox,3,1,"1 - Lancer le jeu en mode debug") ;
    mvwprintw(debugBox,4,1,"2 - Réinitialiser les scores") ; 

    mvwgetnstr(debugBox, 6, 1 , debugChoice,1) ;

    switch (debugChoice[0]){
        case '1' :
            wclear(debugBox) ; // Enlève l'affichage de l'écran titre
            wrefresh(debugBox) ; // Refresh après l'avoir enlevé pour pouvoir mettre la fenêtre à jour
        
            game_1player(true) ;
            break;
        case '2' :
            reset_score() ;
            break ;
        default :
            break;
    }
}