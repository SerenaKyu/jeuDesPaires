#ifndef GAME_H
#define GAME_H

#include <sys/time.h>

struct timeFormat {
    int seconds;
    int milliseconds;
};

struct score {
    char name[5];
    float score;
};

void stringUpper(char *string);
void affiche_tipTool(WINDOW *myWindow);
int affichage_temps(struct timeval start_time, struct timeval current_time, WINDOW *myWindow);
int debug_input(int input, int lastInput, WINDOW *myWindow);
void affichage_scores(struct score *classement, WINDOW *myWindow);
void ecriture_scores(struct score *classement, FILE *fichier_score);
void gestion_classement(int time, WINDOW *myWindow, bool victory);
void after_game(bool victory, int time);
void game_1player(bool debugMode);

#endif // GAME_FUNCTIONS_H
