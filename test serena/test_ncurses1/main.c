#include <stdio.h>
#include <ncurses.h>
#include "tools.h"

int main() {

    initscr() ; //activation mode cursive
    barre(10) ; // print hello world en mode cursif
    refresh() ; 
    getch() ; // attents input user
    endwin(); // finit programme

}