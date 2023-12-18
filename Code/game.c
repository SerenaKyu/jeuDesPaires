#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h> // Librarie pour utiliser le chrono
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "aftergame.h"
#include "./card.h"

static bool inputDisable = false; // Valeur static qui va permettre de désactiver les input du joueur
static int numberOfPairs = 0; // Valeur du nombre de paires totales trouvées

struct timeFormat { // Structure du format du temps
    int seconds ;
    int milliseconds ;
};

/*
Fonction : SecondsAndMilliseconds
Param : time correspond au temps actuelle du jeu calculer grace a la fonction du chronometre
Traitement : transforme l'heure sous le format seconds/milliseconds
Retourne : Le temps sous le bon format
*/
struct timeFormat SecondsAndMilliseconds(int time) { // Fonction permettant de mettre au bon format le temps via la structures précédentes  
   struct timeFormat format;

   format.seconds = time / 1000; // Mise au format secondes
   format.milliseconds = (time % 1000) / 100; // Mise au format millisecondes 

   return format; // Retourne le format proprement
}

/*
Fonction : affiche_tipTool
Param : myWindow correspond à la fenêtre sur laquelle la fonction va être appliquée
Traitement : Affiche une fenêtre avec marqué "Jeu des paires" puis "Trouver les paires en un minimum de temps".
*/
void affiche_tipTool(WINDOW *myWindow) { // Affiche le toolTip du jeu résumant ce qu'il faut faire
    const char *texte[2] = {"Jeu des paires","Trouver les paires en un minimum de temps"} ;
    
    for(int i = 0;i < 2 ;i++) {
        mvwprintw(myWindow,1+i,1,"%s",texte[i]) ; // Print le tooltip dans la fenêtre
    }
}

/*
Fonction : affichage_temps
Param : start_time récupère le temps de la machine auquel le programme a commencé, current_time récupère le temps actuel de la machine, myWindow correspond à la fenêtre sur laquelle la fonction va s'effectuer
Traitement : Cette fonction va calculer le temps passé depuis le début du programme à l'aide du start_time et du current_time et va ensuite l'afficher sur la fenêtre
Retour : Cela retourne le temps passé depuis le début du programme
*/
int affichage_temps(struct timeval start_time ,struct timeval current_time, WINDOW * myWindow) {
    int elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 + 
    (current_time.tv_usec - start_time.tv_usec) / 1000; // Calculer le temps passé entre le début du timer et la fin

    struct timeFormat format = SecondsAndMilliseconds(elapsed_time) ; // Appel de la structure de format du temps

    mvwprintw(myWindow,1,1,"chrono : %d.%ds", format.seconds,format.milliseconds); // Affichage dans la fenêtre du chrono
    wrefresh(myWindow) ; // Refresh la fenêtre pour afficher le temps du chrono actuel

    return elapsed_time ;
}

/*
Fonction : debug_input
Param : input correspond à l'input pressé par l'utilisateur, lastInput correspond à l'input précedent pressé par l'utilisateur
Traitement : Compare le nouvel input avec l'ancien, et défini lastInput à input si la valeur de lastInput est différente de celle de input ou de -1. Elle renvoie ensuite la valeur de lastInput. Cette fonction permet d'afficher l'input pressé dans le mode debug.
Retour : Cela correspond à la valeur de l'input pressé
*/
int debug_input(int input, int lastInput,WINDOW *myWindow) {  // Affiche l'input entré par l'utilisateur
    if (input !=  -1 && input != lastInput) { // Affiche le dernier input entré par l'utilisateur (features debug)
        lastInput = input ;
    }
    return lastInput ;
}

/*
Fonction : game_1player
Param : debugMode permet de récupérer si le mode debug est activé ou non
Traitement : Exécute toutes les fonctions permettant de lancer le jeu
*/
void game_1player(bool debugMode) { // Fonction du jeu à 1 joueur

    struct timeval start_time, current_time; // Structure de temps en time.h
    playcard cardDeck[12] ; // Définition du paquet de carte

    int userInput,lastInput  = 0; // Variable pour les inputs joueur
    int inGameTime ; // Temps passé dans le jeu, récupéré dans la fonction de calcul de temps
    int userPosition = 0;// Défini la postion de l'utilisateur dans les cartes
    bool victory = false ; // Condition de victoire, ici mit en true par défaut pour debug le programme 
    bool forfait = false ;

    WINDOW *tipToolBox = newwin(4,70,0,0) ; // Fenêtre du toolTip du jeu
    WINDOW *chronoBox = newwin(4,29,0,71) ; // Fenêtre du chrono du jeu
    
    box(tipToolBox,0,0) ; // Affichage des deux fenêtre en mode box
    box(chronoBox,0,0) ; 

    start_color(); // Initialise la couleur
    noecho() ; // Enlève l'affichage des inputs entrés par l'utilisateur
    curs_set(0); // Enlève le curseur de la fenêtre du terminal
    timeout(100) ; // Intilise l'intervalle de temps entre chaque rafraîchissement du programme (utile pour le timer)

    init_pair(1, COLOR_WHITE, COLOR_BLACK); // Initialise les paires de couleur
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Initialise la paire de couleur verte
    init_pair(3, COLOR_CYAN, COLOR_BLACK); // Initialise la paire de couleur cyan

    affiche_tipTool(tipToolBox) ; // Affiche la description 
    wrefresh(tipToolBox) ; // Refresh les deux fenêtres
    wrefresh(chronoBox) ;

    printCard(cardDeck,debugMode) ; // Affiche toutes les cartes en mode face cachée

    gettimeofday(&start_time, NULL) ; // Récupère la valeur de début du chrono et du jeu

     do { // Lancement du jeu et du chrono
        if(numberOfPairs == 12) {
            victory = true;
        }

        gettimeofday(&current_time, NULL) ; // Récupère la valeur au moment où se trouve le timer

        inGameTime = affichage_temps(start_time,current_time,chronoBox); // Refresh le temps actuel du jeu tout en la conservant pour pouvoir l'utiliser pour savoir si on est hors temps ou non

        userInput = getch(); // Récupère l'input utilisateur pour commander le jeu

        if(debugMode == true) {
            lastInput = debug_input(userInput,lastInput,chronoBox) ;
            mvwprintw(chronoBox,2,1,"Input : %c  ",lastInput) ; // Affiche le dernier input entré
        }
        if(inputDisable == false) {
            switch(userInput) {
            case 'q'  : // Quand q est pressé, termine le jeu et applique une défaite
                forfait = true ; // Termine le do while grâce à la variable de forfait du joueur.
                break;
            case 'a' : // Déplacement vers la gauche
                userPosition --;
                while(cardDeck[userPosition].paired == true) { // Décale la position si la carte est paire
                    userPosition --;
                }
                break;
            case 'z' : // Déplacement vers la droit
                userPosition ++;
                while(cardDeck[userPosition].paired == true) { // Décale la position si la carte est paire
                    userPosition ++;
                }
                break;
            case 'e' : // Sélectionne la carte, et change le status de cette dernière
                if(cardDeck[userPosition].paired == false) { // Permet de ne pas sélectionner une carte déjà pairée
                    cardDeck[userPosition].selected = true ;
                }
                break;
            }
        }
        userPosition = checkPose(userPosition,cardDeck); // Recalcule la position pour éviter que le joueur sorte de l'écran
        cardStatusUpdate(cardDeck,userPosition,debugMode); // Update le status des cartes (couleur)
        checkPaires(cardDeck,start_time,current_time,chronoBox) ; // Vérifie si deux cartes sont sélectionnées et paires
    } while ((inGameTime / 1000) < 120 && forfait != true && victory != true); // Tant que le joueur n'a pas réussi, abandonné, ou atteint la limite de temps de 120 secondes, on continue le sélection de cartes
    after_game(victory,inGameTime) ; // Lance la fenêtre d'après jeu
}