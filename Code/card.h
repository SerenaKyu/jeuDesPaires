#ifndef CARD_H
#define CARD_H

#include <ncurses.h>
#include <stdbool.h>

typedef struct card {
    WINDOW *windowCard;
    char status;
    int value;
    bool selected;
    bool paired;
} playcard;

void hiddenCard(playcard chosenCard, bool debugMode);
void definitionCard(playcard *carte);
void printCard(playcard *carte, bool debugMode);
void onCard(playcard chosenCard, bool debugMode);
void pairedCard(playcard chosenCard);
void selectedCard(playcard chosenCard);
void cardStatusUpdate(playcard *chosenCard, int userPosition, bool debugMode);
void checkPaires(playcard *chosenCard, struct timeval start_time, struct timeval current_time, WINDOW *myWindow);
int checkPose(int pose, playcard *chosenCard);

#endif  //CARD_H
