#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h> //librarie pour utiliser le chrono
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "aftergame.h"

static bool inputDisable = false; // valeur static qui vas permettre de desactiver les inputs du joueur
static int numberOfPairs = 0; //valeur du nombre de paire total trouve

struct timeFormat { //structure du format du temps
    int seconds ;
    int milliseconds ;
};

typedef struct card { //structure qui gere le format des cartes (leur position, le statuts )
    WINDOW* windowCard; //fenetre de la carte
    char status ; //status de la carte
    int value ; // valeur de la carte
    bool selected ; // etat selectionner pour l'algo de pairage
    bool paired ; //etat pairé (sont afficher et pas selectionnable ou passable dessus)
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

void hiddenCard(playcard chosenCard , bool debugMode) { //affiche une carte face cache. si le debug mode est on, on affiche la lettre aussi
    wattron(chosenCard.windowCard,COLOR_PAIR(1)) ; //definie la couleur de la carte
    wborder(chosenCard.windowCard,'|','|','-','-',' ',' ',' ',' ') ; //creer les bordure de la carte
    if(debugMode == true) { //si le debug mode est on, affiche la valeur
        mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    }
    else{
        mvwprintw(chosenCard.windowCard,3,4," ") ; //sinon affiche rien
    }
    wrefresh(chosenCard.windowCard) ; //refesh la carte
}

void definitionCard(playcard *carte) { //vas definir les valeur de la liste des cartes (leur position,valeur,status)

    int position_x[6] = {1,11,21,31,41,51} ; //position x de la carte, il y a une liste pour les cartes d'une rangee
    int position_y = 5; //position y de la carte, la premiere rangee commence en 5
    int valeurRand, temp ; //definition des valeur utiliser pour l'algo de trie aleatoire
    int cardValue[12] = {'A','A','B','B','C','C','D','D','E','E','F','F'} ; //definition de toutes les valeur utiliser pour les cartes 

    srand(time(NULL)); //seed du random 

    for(int i = 0 ; i < 12;i++) { //algorithme de trie aleatoire
        valeurRand = rand() % 12 ;

        temp = cardValue[i] ;
        cardValue[i] = cardValue[valeurRand] ;
        cardValue[valeurRand] = temp ;
    }

    for(int i = 0 ; i < 12 ;i++) { //boucle qui vas definir toute les cartes par defaut
            if(i == 6) { //position en hauteur qui vas changer si on change de range
                position_y = 13; // 13 etant la valeur de la deuxime rangee
            }
            carte[i].windowCard = newwin(7,9,position_y,position_x[i%6]) ; //creation de la fenetre de la carte, 
                                                                         //elle vas definir la hauteur et largeur de l'espace de la carte
            carte[i].status = 'h' ; //status qui vas gerer si le jouer est au dessus de la carte ou pas, par defaut, le joueur est pas dessus
            carte[i].value = cardValue[i] ; //valeur de la carte
            carte[i].selected = false ; //si elle est selectionner par le joueur
            carte[i].paired = false ; // si elle est deja pairee
    }
}

void printCard(playcard *carte, bool debugMode) { //definie et affiche toute les cartes du jeu
    definitionCard(carte);
    for(int i = 0;i < 12;i++){
        hiddenCard(carte[i],debugMode) ;
    }
}

void onCard(playcard chosenCard) { //si le joueur est dessus la carte, elle est verte
    wattron(chosenCard.windowCard,COLOR_PAIR(2)) ;
    wborder(chosenCard.windowCard,'|','|','-','-',' ',' ',' ',' ') ;
    wrefresh(chosenCard.windowCard) ;
}

void pairedCard(playcard chosenCard) { // si elle est paired, les corneur sont des 0
    wattron(chosenCard.windowCard,COLOR_PAIR(1)) ;
    wborder(chosenCard.windowCard,'|','|','-','-','0','0','0','0') ;
    mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    wrefresh(chosenCard.windowCard) ;
}

void selectedCard(playcard chosenCard){ //si la carte est selectionner, elle est bleu et on affiche sa valeur
    wattron(chosenCard.windowCard,COLOR_PAIR(3)) ;
    wborder(chosenCard.windowCard,'|','|','-','-',' ',' ',' ',' ') ;    
    mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    wrefresh(chosenCard.windowCard) ;
}   

void cardStatusUpdate(playcard *chosenCard,int userPosition, bool debugMode){ // vas update le status de la carte selon la position du jeu
                                                                             // et son etat dans le jeu
    for(int i=0;i < 12;i++){ //vas parcourrire toute les cartes
        if(chosenCard[i].status != 'p'){// si la carte est autres que hidden, on la remets en hidden 
            chosenCard[i].status = 'h'; 
        }

        if(i == userPosition){ // si la carte paroucus = la carte ou est le joueur, alors son status = o
            chosenCard[userPosition].status = 'o' ;
        }

        switch (chosenCard[i].status) // switch qui vas update le status de la cartes selon son status 
        {
        case 'o':
            onCard(chosenCard[i]); //affiche la carte en vert 
            break;
        case 'h':
            hiddenCard(chosenCard[i],debugMode); //affiche la carte en mode cachee et selon le debug mode on ou pas
            break;
        }

        if(chosenCard[i].selected == true) { // l'update en bleu est valeur afficher si elle est bleu
            selectedCard(chosenCard[i]) ;
        }

        if(chosenCard[i].paired == true) { //si la carte est pairee, alors on l'affiche en mode pairee
            pairedCard(chosenCard[i]) ;
        }

    }
}

void checkPaires(playcard *chosenCard,struct timeval start_time ,struct timeval current_time, WINDOW * myWindow) { //algo qui vas check si la cartes est pairee ou pas
    
    int paires[2] = {-1,-1}; //liste qui va enregistrer les 2 indicices des carte selectionee
    int elapsed_time,start_break ;

    for(int i = 0; i < 12;i++){ //vas parcourrir toute les cartes pour lire leur status
        if(chosenCard[i].selected == true) { //si la cartes est selectionner alors on vas chercher a l'ajouter dans la liste des paires
            if(paires[0] == -1) { // si pas de valeur, alors paires[0] = l'indice de la premiere selection
                paires[0] = i ;
                selectedCard(chosenCard[i]) ; // affiche la cartes en mode selectionner
            }
            else{ //si une carte deja selectionner alors on enregistre le deuxieme indice afin de l'utiliser 
                paires[1] = i ;
                selectedCard(chosenCard[i]) ;
            }
        }
    }

    if(paires[0] != -1 && paires[1] != -1){ // si deux cartes sont selectionner, alors on vas check si elle sont good
        inputDisable = true ; //vas desactiver les input
        start_break = affichage_temps(start_time,current_time,myWindow);

        while ((elapsed_time / 1000) < (start_break / 1000) + 2){ //tourne le chrono pendant 2 seconds
                                                                 // le temps de test si les deux sont bien des paires
            gettimeofday(&current_time, NULL) ;
            elapsed_time = affichage_temps(start_time,current_time,myWindow); }//refesh le chrono du temps
        inputDisable = false; //redonne les inputs a la fin du timer

        for(int i = 0 ; i < 2; i++){ //enleve l'etat de selection des deux cartes
            chosenCard[paires[i]].selected = false;
        } 

        if(chosenCard[paires[0]].value == chosenCard[paires[1]].value) { //si la valeur des deux cartes sont identique
            for(int i = 0; i < 2; i++){
                pairedCard(chosenCard[paires[i]]); //on affiche les cartes en mode paired
                chosenCard[paires[i]].paired = true; //on donne le status paires
                numberOfPairs++; // on augmente le nombre de pairs qui on ete trouver 
            }
            return ;
        }
        
        else{ //sinon, on retourne toute les cartes en mode cachée
            for(int i = 0;i < 2;i++){
                hiddenCard(chosenCard[paires[i]],false) ; //note : il y a un bug avec le mode debug
            }
        }
    }
    return ;
}


int checkPose(int pose,playcard *chosenCard){ //reajuste la position du joueur si il sort de la liste
    if(pose > 11) { // si il vas en dehors du paquet de 12 cartes, on vas le mettre au 0
        pose = 0 ;
        while(chosenCard[pose].paired == true) { //si la carte et paire a cette iteration, alors on la decale encores de 1
               pose ++;
            }   
        } 
    else if(pose < 0) { //la meme mais dans l'autre sens de circulation
        pose = 11 ;
        while(chosenCard[pose].paired == true) {
           pose --;
        } 
    }
    return pose; //retourne la position ajuster du joueur
}

void game_1player(bool debugMode) { //fonction du jeu à 1 joueur

    struct timeval start_time, current_time; //structure de temps en time.h
    playcard cardDeck[12] ; //definition du paquet de carte

    int userInput,lastInput  = 0; //variable pour les inputs joueur
    int inGameTime ; //temps passé dans le jeu, il recupérer dans la fonction de calcul de temps.
    int userPosition = 0;//définie la postion de l'utilisateur dans les cartes
    bool victory = false ; //condition de victoire, ici mis en true par defaut pour debug le programme 
    bool forfait = false ;

    WINDOW *tipToolBox = newwin(4,70,0,0) ; //Fenetre du toolTip du jeu
    WINDOW *chronoBox = newwin(4,29,0,71) ; //Fenetre du chrono du jeu
    
    box(tipToolBox,0,0) ; //affichage des 2 fenetre en mode box
    box(chronoBox,0,0) ; 

    start_color(); //initialise la couleur
    noecho() ; //enleve l'affiche des inputs rentrer par l'utilisateur
    curs_set(0); //enleve le curseur de la fenetre du terminal
    timeout(100) ; // mets le temps 

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Initialise les paires de couleur
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Initialise la paire de couleur verte
    init_pair(3, COLOR_CYAN, COLOR_BLACK); // Initialise la paire de couleur cyan

    affiche_tipTool(tipToolBox) ; //affiche la description 
    wrefresh(tipToolBox) ; //refesh les 2 fenetre
    wrefresh(chronoBox) ;

    printCard(cardDeck,debugMode) ; //affiche toute les cartes en mode face cachee

    gettimeofday(&start_time, NULL) ; //recuperer la valeur de debut du chrono et du jeu

     do { //Lancement du jeu et du chrono
        if(numberOfPairs == 12) {
            victory = true;
        }

        gettimeofday(&current_time, NULL) ; // recupere la valeur a ce moment dans le timer

        inGameTime = affichage_temps(start_time,current_time,chronoBox); //refresh le temps actuelle du jeu, 
                                                                        //tout en la conservant pour pouvoir l'utiliser pour savoir si on est hors temps ou pas

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
            case 'a' : //deplacement vers la gauche
                userPosition --;
                while(cardDeck[userPosition].paired == true) { //decale la position si la carte est paire
                    userPosition --;
                }
                break;
            case 'z' : //deplacement vers la droit
                userPosition ++;
                while(cardDeck[userPosition].paired == true) { //decale la position si la carte est paire
                    userPosition ++;
                }
                break;
            case 'e' : //sélectionne la carte, et change le status de cette derniere
                if(cardDeck[userPosition].paired == false) { //on peut pas selectionner une carte deja paire
                    cardDeck[userPosition].selected = true ;
                }
                break;
            }
        }
        userPosition = checkPose(userPosition,cardDeck); //recalcule la position pour eviter que le joueur sorte de l'ecran
        cardStatusUpdate(cardDeck,userPosition,debugMode); //vas update le status des cartes (couleur)
        checkPaires(cardDeck,start_time,current_time,chronoBox) ; //vas check si deux cartes sont selectionner et paire
    } while ((inGameTime / 1000) < 120 && forfait != true && victory != true); //temps du chrono (dans la version final, on sera a 120s)
    after_game(victory,inGameTime) ; // lance la fenetre d'aprés jeu
    }