#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h> //librarie pour utiliser le chrono
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "aftergame.h"

static bool inputDisable = false;
static int numberOfPairs = 0;

struct timeFormat { //structure du format du temps
    int seconds ;
    int milliseconds ;
};

typedef struct card { //structure qui gere le format des cartes (leur position, le statuts )
    WINDOW* windowCard; //fenetre de la carte
    char status ; //status de la carte
    int value ; // valeur de la carte
    bool selected ;
    bool paired ;
}playcard;

struct timeFormat SecondsAndMilliseconds(int time) { //fonction de mise a format du temps via la structures précédentes 
   struct timeFormat format;

   format.seconds = time / 1000; //mise au format seconds
   format.milliseconds = (time % 1000) / 100; //mise au format milliseconds

   return format; // retourne le format bien comme il faut
}

void affiche_tipTool(WINDOW *myWindow) { //affiche le toolTip du jeu(resume de ce qui faut faire)
    const char *texte[2] = {"Jeu des paires","Trouver les paires en un minimun de temps"} ;
    
    for(int i = 0;i < 2 ;i++) {
        mvwprintw(myWindow,1+i,1,"%s",texte[i]) ; //print dans la fenetre le tooltip
    }
}

int affichage_temps(struct timeval start_time ,struct timeval current_time, WINDOW * myWindow) {
    int elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 + 
    (current_time.tv_usec - start_time.tv_usec) / 1000; //calculer le temps depuis le debut du timer et la fin

    struct timeFormat format = SecondsAndMilliseconds(elapsed_time) ; //appel de la structure de format du temps

    mvwprintw(myWindow,1,1,"chrono : %d.%ds", format.seconds,format.milliseconds); //affichage dans la fenetre du chrono
    wrefresh(myWindow) ; //refresh la fenetre pour afficher le temps du chrono actuel

    return elapsed_time ;
}

int debug_input(int input, int lastInput,WINDOW *myWindow) {  //affiche l'input entree par l'utilisateur
    if (input !=  -1 && input != lastInput) { //affiche la derniere input entrer par l'utilisateur (features debug)
        lastInput = input ;
    }
    return lastInput ;
}

void hiddenCard(playcard chosenCard , bool debugMode) {
    wattron(chosenCard.windowCard,COLOR_PAIR(1)) ;
    wborder(chosenCard.windowCard,'|','|','-','-',' ',' ',' ',' ') ;
    if(debugMode == true) {
        mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    }
    else{
        mvwprintw(chosenCard.windowCard,3,4," ") ; 
    }
    wrefresh(chosenCard.windowCard) ;
}

void definitionCard(playcard *carte) {
    int position_x[6] = {1,11,21,31,41,51} ;
    int position_y = 5;
    int cardValue[12] = {'A','A','B','B','C','C','D','D','E','E','F','F'} ;

    srand(time(NULL));

    for(int i = 0 ; i < 12 ;i++) {
            if(i == 6) {
                position_y = 13;
            }
            carte[i].windowCard = newwin(7,9,position_y,position_x[i%6]) ;
            carte[i].status = 'h' ;
            carte[i].value = cardValue[i] ;
            carte[i].selected = false ;
            carte[i].paired = false ;
    }
}

void printCard(playcard *carte, bool debugMode) {
    definitionCard(carte);
    for(int i = 0;i < 12;i++){
        hiddenCard(carte[i],debugMode) ;
    }
}

void onCard(playcard chosenCard) {
    wattron(chosenCard.windowCard,COLOR_PAIR(2)) ;
    wborder(chosenCard.windowCard,'|','|','-','-',' ',' ',' ',' ') ;
    wrefresh(chosenCard.windowCard) ;
}

void pairedCard(playcard chosenCard) {
    wattron(chosenCard.windowCard,COLOR_PAIR(1)) ;
    wborder(chosenCard.windowCard,'|','|','-','-','0','0','0','0') ;
    mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    wrefresh(chosenCard.windowCard) ;
}

void selectedCard(playcard chosenCard){
    wattron(chosenCard.windowCard,COLOR_PAIR(3)) ;
    wborder(chosenCard.windowCard,'|','|','-','-',' ',' ',' ',' ') ;    
    mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    wrefresh(chosenCard.windowCard) ;
}   

void cardStatusUpdate(playcard *chosenCard,int userPosition, bool debugMode){
    for(int i=0;i < 12;i++){
        if(chosenCard[i].status != 'p'){
            chosenCard[i].status = 'h';
        }

        if(i == userPosition){
            chosenCard[userPosition].status = 'o' ;
        }

        switch (chosenCard[i].status) 
        {
        case 'o':
            onCard(chosenCard[i]);
            break;
        case 'h':
            hiddenCard(chosenCard[i],debugMode);
            break;
        }

        if(chosenCard[i].selected == true) {
            selectedCard(chosenCard[i]) ;
        }

        if(chosenCard[i].paired == true) {
            pairedCard(chosenCard[i]) ;
        }

    }
}

int checkPaires(playcard *chosenCard,struct timeval start_time ,struct timeval current_time, WINDOW * myWindow) {
    

    int paires[2] = {-1,-1};
    int elapsed_time,start_break ;

    for(int i = 0; i < 12;i++){
        if(chosenCard[i].selected == true) {
            if(paires[0] == -1) {
                paires[0] = i ;
                selectedCard(chosenCard[i]) ;
            }
            else{
                paires[1] = i ;
                selectedCard(chosenCard[i]) ;
            }
        }
    }

    if(paires[0] != -1 && paires[1] != -1){
        inputDisable = true ;
        start_break = affichage_temps(start_time,current_time,myWindow);

        while ((elapsed_time / 1000) < (start_break / 1000) + 2){
            gettimeofday(&current_time, NULL) ; // recupere la valeur a ce moment dans le timer
            elapsed_time = affichage_temps(start_time,current_time,myWindow);
        }
        inputDisable = false;

        for(int i = 0 ; i < 2; i++){
            chosenCard[paires[i]].selected = false;
        }

        if(chosenCard[paires[0]].value == chosenCard[paires[1]].value) {
            for(int i = 0; i < 2; i++){
                pairedCard(chosenCard[paires[i]]);
                chosenCard[paires[i]].paired = true;
                numberOfPairs++;
            }
            return 1;
        }
        
        else{
            for(int i = 0;i < 2;i++){
                hiddenCard(chosenCard[paires[i]],false) ;
            }
        }
    }
    return 0;
}

int checkPose(int pose,playcard *chosenCard){
    if(pose > 11) {
        pose = 0 ;
        while(chosenCard[pose].paired == true) {
               pose ++;
            }   
        } 
    else if(pose < 0) {
        pose = 11 ;
        while(chosenCard[pose].paired == true) {
           pose --;
        } 
    }
    return pose;
}

void game_1player(bool debugMode) { //fonction du jeu à 1 joueur

    struct timeval start_time, current_time; //structure de temps en time.h
    playcard testCarte[12] ;

    int userInput,lastInput  = 0; //variable pour les inputs joueur
    int inGameTime ; //temps passé dans le jeu, il recupérer dans la fonction de calcul de temps.
    int userPosition = 0;//définie la postion de l'utilisateur dans les cartes
    bool victory = false ; //condition de victoire, ici mis en true par defaut pour debug le programme 
    bool forfait = false ;

    WINDOW *tipToolBox = newwin(4,70,0,0) ; //Fenetre du toolTip du jeu
    WINDOW *chronoBox = newwin(4,29,0,71) ; //Fenetre du chrono du jeu
    
    box(tipToolBox,0,0) ; //affichage des 2 fenetre
    box(chronoBox,0,0) ;

    start_color(); //initialise la couleur
    noecho() ; //enleve l'affiche des inputs rentrer par l'utilisateur
    curs_set(0); //enleve le curseur de la fenetre du terminal
    timeout(100) ; // mets le temps 

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Initialise les paires de couleur
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Initialise la paire de couleur verte
    init_pair(3, COLOR_CYAN, COLOR_BLACK); // Initialise la paire de couleur cyan

    affiche_tipTool(tipToolBox) ; //affiche la description 
    wrefresh(tipToolBox) ;
    wrefresh(chronoBox) ;

    printCard(testCarte,debugMode) ;

    gettimeofday(&start_time, NULL) ; //recuperer la valeur de debut du chrono et du jeu

     do { //Lancement du jeu et du chrono
        if(numberOfPairs == 12) {
            victory = true;
        }

        gettimeofday(&current_time, NULL) ; // recupere la valeur a ce moment dans le timer

        inGameTime = affichage_temps(start_time,current_time,chronoBox);

        userInput = getch(); //récupere l'input utilisateur pour commander le jeu

        if(debugMode == true) {
            lastInput = debug_input(userInput,lastInput,chronoBox) ;
            mvwprintw(chronoBox,2,1,"Input : %c  ",lastInput) ; //affiche le dernier input
        }
        if(inputDisable == false) {
            switch(userInput) {
            case 'q'  : //Quand q press, termine le jeu et applique une défaite
                forfait = true ; //termine le do while grace a la variable de forfait du joueur.
                break;
            case 'a' : //deplacement gauche
                userPosition --;
                while(testCarte[userPosition].paired == true) {
                    userPosition --;
                }
                break;
            case 'z' : //deplacement droit
                userPosition ++;
                while(testCarte[userPosition].paired == true) {
                    userPosition ++;
                }
                break;
            case 'e' : //sélection carte
                if(testCarte[userPosition].paired == false) {
                    testCarte[userPosition].selected = true ;
                }
                break;
            }
        }
        userPosition = checkPose(userPosition,testCarte);
        cardStatusUpdate(testCarte,userPosition,debugMode);
        checkPaires(testCarte,start_time,current_time,chronoBox) ;
    } while ((inGameTime / 1000) < 120 && forfait != true && victory != true); //temps du chrono (dans la version final, on sera a 120s)
    after_game(victory,inGameTime,debugMode) ; // lance la fenetre d'aprés jeu
}