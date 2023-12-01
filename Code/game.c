#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h> //librarie pour utiliser le chrono
#include <stdbool.h>

void affiche_tipTool(WINDOW *myWindow) { //affiche le toolTip du jeu(resume de ce qui faut faire)
    const char *texte[2] = {"Jeu des paires","Trouver les paires en un minimun de temps"} ;
    
    for(int i = 0;i < 2 ;i++) {
        mvwprintw(myWindow,1+i,1,"%s",texte[i]) ; //print dans la fenetre le tooltip
    }
}

int affichage_temps(struct timeval start_time ,struct timeval current_time, WINDOW * myWindow) {
    int seconds, milliseconds ; //vas transformer ce temps en seconds et milliseconds
    int elapsed_time ; //peremts de calculer le temps qui c'est passer depuis le debut du timer

    elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 + 
    (current_time.tv_usec - start_time.tv_usec) / 1000; //calculer le temps depuis le debut du timer et la fin

    seconds = elapsed_time / 1000; //calcule la valeur en secondes
    milliseconds = (elapsed_time % 1000) / 100; //calcule la valeurs a coter en millisecondes

    mvwprintw(myWindow,1,1,"Chrono  : %d.%ds", seconds,milliseconds); //affichage dans la fenetre du chrono
    wrefresh(myWindow) ; //refresh la fenetre pour afficher le temps du chrono actuel

    return seconds ;
}

int debug_input(int input, int lastInput,WINDOW *myWindow) {  //affiche l'input entree par l'utilisateur
    if (input !=  -1 || input != lastInput) { //affiche la derniere input entrer par l'utilisateur (features debug)
        lastInput = input ;
        return lastInput ;
    }
    return -1 ;
}

void game_1player(bool debugMode) { //fonction du jeu à 1 joueur

    struct timeval start_time, current_time; //structure de temps en time.h

    int userInput,lastInput  = 0; //variable pour les inputs joueur
    int inGameTime ; //temps passé dans le jeu, il recupérer dans la fonction de calcul de temps.

    WINDOW *tipToolBox = newwin(4,70,0,0) ; //Fenetre du toolTip du jeu
    WINDOW *chronoBox = newwin(4,29,0,71) ; //Fenetre du chrono du jeu
    
    box(tipToolBox,0,0) ; //affichage des 2 fenetre
    box(chronoBox,0,0) ;

    noecho() ; //enleve l'affiche des inputs rentrer par l'utilisateur
    curs_set(0); //enleve le curseur de la fenetre du terminal
    timeout(100) ; // mets le temps 

    affiche_tipTool(tipToolBox) ; //affiche la description 
    wrefresh(tipToolBox) ;
    wrefresh(chronoBox) ;

    gettimeofday(&start_time, NULL) ; //recuperer la valeur de debut du chrono et du jeu

     do { //Lancement du jeu et du chrono
        gettimeofday(&current_time, NULL) ; // recupere la valeur a ce moment dans le timer

        inGameTime = affichage_temps(start_time,current_time,chronoBox);

        userInput = getch(); //récupere l'input utilisateur pour commander le jeu

        if(debugMode == true) {
            lastInput = debug_input(userInput,lastInput,chronoBox) ;
            mvwprintw(chronoBox,2,1,"Input : %c   ",lastInput) ; //affiche le dernier input
        }
        
        if(userInput == 27) { //Quand echap press, termine le jeu (features debug)
            break;
        }

    } while (inGameTime < 120 ); //temps du chrono (dans la version final, on sera a 120s)
}