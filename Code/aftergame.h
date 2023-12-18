#ifndef AFTERGAME_H
#define AFTERGAME_H

#include <ncurses.h>
#include <stdbool.h>

struct score {
    char name[5];
    float score;
};

void stringUpper(char *string);
void affichage_scores(struct score *classement, WINDOW *myWindow);
void ecriture_scores(struct score *classement, FILE *fichier_score);
void gestion_classement(int time, WINDOW *myWindow, bool victory);
void after_game(bool victory, int time);

#endif  // AFTERGAME_H
