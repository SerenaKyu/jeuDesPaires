#ifndef GAME_H
#define GAME_H

#include <curses.h>
#include <stdbool.h>
#include <sys/time.h>

struct timeFormat {
    int seconds;
    int milliseconds;
};

typedef struct card {
    WINDOW *windowCard;
    char status;
    int value;
    bool selected;
    bool paired;
} playcard;

struct timeFormat SecondsAndMilliseconds(int time);
void affiche_tipTool(WINDOW *myWindow);
int affichage_temps(struct timeval start_time, struct timeval current_time, WINDOW *myWindow);
int debug_input(int input, int lastInput, WINDOW *myWindow);
void hiddenCard(playcard chosenCard, bool debugMode);
void definitionCard(playcard *carte);
void printCard(playcard *carte, bool debugMode);
void onCard(playcard chosenCard);
void pairedCard(playcard chosenCard);
void selectedCard(playcard chosenCard);
void cardStatusUpdate(playcard *chosenCard, int userPosition, bool debugMode);
void checkPaires(playcard *chosenCard, struct timeval start_time, struct timeval current_time, WINDOW *myWindow);
int checkPose(int pose, playcard *chosenCard);
void game_1player(bool debugMode);
void game_autoplay() ;

#endif  //GAME_H
