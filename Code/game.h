#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdbool.h>
#include <sys/time.h>

static bool inputDisable ; // Valeur static qui va permettre de désactiver les input du joueur
static int numberOfPairs ; // Valeur du nombre de paires totales trouvées

struct timeFormat {
    int seconds;
    int milliseconds;
};

struct timeFormat SecondsAndMilliseconds(int time);
void affiche_tipTool(WINDOW *myWindow);
int affichage_temps(struct timeval start_time, struct timeval current_time, WINDOW *myWindow);
int debug_input(int input, int lastInput, WINDOW *myWindow);
void game_1player(bool debugMode);

#endif  //GAME_H
