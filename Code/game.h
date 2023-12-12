#ifndef GAME_H
#define GAME_H

struct timeFormat { //format de temps
    int seconds;
    int milliseconds;
};

struct card { //structure qui gere le format des cartes (leur position, le statuts )
    WINDOW* windowCard; //fenetre de la carte
    char status ; //status de la carte
    char value ; // valeur de la carte
};

struct timeFormat SecondsAndMilliseconds(int time) ;
void affiche_tipTool(WINDOW *myWindow);
int affichage_temps(struct timeval start_time, struct timeval current_time, WINDOW *myWindow);
int debug_input(int input, int lastInput, WINDOW *myWindow);
void selectedCard(struct card chosenCard);
void visualCard(struct card chosenCard , bool debugMode) ;
void printCard(struct card carte) ;
void game_1player(bool debugMode);

#endif // GAME_FUNCTIONS_H
