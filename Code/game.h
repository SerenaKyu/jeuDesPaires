#ifndef GAME_H
#define GAME_H

struct timeFormat {
    int seconds;
    int milliseconds;
};


struct timeFormat SecondsAndMilliseconds(int time) ;
void affiche_tipTool(WINDOW *myWindow);
int affichage_temps(struct timeval start_time, struct timeval current_time, WINDOW *myWindow);
int debug_input(int input, int lastInput, WINDOW *myWindow);
void game_1player(bool debugMode);

#endif // GAME_FUNCTIONS_H
