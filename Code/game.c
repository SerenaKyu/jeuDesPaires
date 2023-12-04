#include <ncurses.h>
#include <stdlib.h>
#include <sys/time.h> //librarie pour utiliser le chrono
#include <stdbool.h>

struct timeFormat { //structure du format du temps
    int seconds ;
    int milliseconds ;
};

struct timeFormat SecondsAndMilliseconds(int time) { //mise a format du temps via la structures précédentes 
   struct timeFormat format;

   format.seconds = time / 1000; //mise au format seconds
   format.milliseconds = (time % 1000) / 100; //mise au format milliseconds

   return format; // retourne le format bien comme il faut
}



void affiche_tipTool(WINDOW *myWindow) { //affiche le toolTip du jeu(resume de ce qui faut faire)
    const char *texte[2] = {"Jeu des paires","Trouver les paires en un minimun de temps"} ;
    
    for(int i = 0;i < 2 ;i++) {
        mvwprintw(myWindow,1+i,1,"%s",texte[i]) ; //print dans la fenetre le tooltip
    }
}



int affichage_temps(struct timeval start_time ,struct timeval current_time, WINDOW * myWindow) {
    int elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1000 + 
    (current_time.tv_usec - start_time.tv_usec) / 1000; //calculer le temps depuis le debut du timer et la fin

    struct timeFormat format = SecondsAndMilliseconds(elapsed_time) ; //appel de la structure de format du temps

    mvwprintw(myWindow,1,1,"Chrono  : %d.%ds", format.seconds,format.milliseconds); //affichage dans la fenetre du chrono
    wrefresh(myWindow) ; //refresh la fenetre pour afficher le temps du chrono actuel

    return elapsed_time ;
}



int debug_input(int input, int lastInput,WINDOW *myWindow) {  //affiche l'input entree par l'utilisateur
    if (input !=  -1 || input != lastInput) { //affiche la derniere input entrer par l'utilisateur (features debug)
        lastInput = input ;
        return lastInput ;
    }
    return -1 ;
}

void ecriture_score(int time, WINDOW *myWindow) {
    char username[50] ; //variable qui vas stocker le nom

    curs_set(1) ; //reaffiche le curser
    echo() ;

    mvwgetstr(myWindow, 4, 62 , username) ; //recupere le choix de l'utilisateur
    mvwprintw(myWindow,6,1,"%.4s",username) ;
} 



void after_game(bool victory, int time){
    int userInput ; //input utilisateur pour fermer le jeu

    struct timeFormat format = SecondsAndMilliseconds(time) ; //appel de la structure de format du temps

    WINDOW *afterGameBox = newwin(8,100,22,0); //Fenetre de victoire

    box(afterGameBox,0,0) ; //affiche les bordure dans 
    
    if (victory == true) { //si le joueur a gagner

        mvwprintw(afterGameBox,1,1,"VICTOIRE") ; //affiche la victoire et le temps du joueur
        mvwprintw(afterGameBox,2,1,"Votre Temps : %d.%ds",format.seconds,format.milliseconds) ;
        mvwprintw(afterGameBox,4,1,"Veilliez choisir un nom à 4 lettre pour conserver le score :") ;
        
        ecriture_score(time,afterGameBox) ;
    }

    else { //si joueur perds
        mvwprintw(afterGameBox,1,1,"DEFAITE") ;
    }
        wrefresh(afterGameBox) ;
    while (1)
    { //attends un echap avant de quitter le jeu

        userInput = getch() ;
        if(userInput == 27) { //Quand echap press, termine le jeu (features debug)
            break;
        }
    }
}



void game_1player(bool debugMode) { //fonction du jeu à 1 joueur

    struct timeval start_time, current_time; //structure de temps en time.h

    int userInput,lastInput  = 0; //variable pour les inputs joueur
    int inGameTime ; //temps passé dans le jeu, il recupérer dans la fonction de calcul de temps.
    bool victory = true ; //condition de victoire, ici mis en true par defaut pour debug le programme 

    WINDOW *tipToolBox = newwin(4,70,0,0) ; //Fenetre du toolTip du jeu
    WINDOW *chronoBox = newwin(4,29,0,71) ; //Fenetre du chrono du jeu
    
    box(tipToolBox,0,0) ; //affichage des 2 fenetre
    box(chronoBox,0,0) ;

    noecho() ; //enleve l'affiche des inputs rentrer par l'utilisateur
    curs_set(0); //enleve le curseur de la fenetre du terminal
    timeout(100) ; // mets le temps 

    affiche_tipTool(tipToolBox) ; //affiche la description 
    wrefresh(tipToolBox) ;
    wrefresh(chronoBox) ;

    gettimeofday(&start_time, NULL) ; //recuperer la valeur de debut du chrono et du jeu

     do { //Lancement du jeu et du chrono
        gettimeofday(&current_time, NULL) ; // recupere la valeur a ce moment dans le timer

        inGameTime = affichage_temps(start_time,current_time,chronoBox);

        userInput = getch(); //récupere l'input utilisateur pour commander le jeu

        if(debugMode == true) {
            lastInput = debug_input(userInput,lastInput,chronoBox) ;
            mvwprintw(chronoBox,2,1,"Input : %c   ",lastInput) ; //affiche le dernier input
        }
        
        if(userInput == 27) { //Quand echap press, termine le jeu (features debug)
            break;
        }

    } while ((inGameTime / 1000) < 120 ); //temps du chrono (dans la version final, on sera a 120s)
    after_game(victory,inGameTime) ; // lance la fenetre d'aprés jeu
}