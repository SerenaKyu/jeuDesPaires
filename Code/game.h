#ifndef HEADER_FILE
#define HEADER_FILE

void affiche_tipTool(WINDOW *myWindow) ;
int affichage_temps(struct timeval start_time ,struct timeval current_time, WINDOW * myWindow) ;
int debug_input(int input, int lastInput,WINDOW *myWindow)  ;
void game_1player() ;

#endif