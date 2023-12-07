#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

struct score{ //structure de score 
    char name[5];
    float score;
};




void stringUpper ( char *string ) { //permet de convertire un string en majuscule
    while( *string ){ 
        *string=toupper( *string ); 
        string++; 
    }
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
    FILE *highscore;
    char username[5] ; //variable qui vas stocker le nom

    struct timeFormat format = SecondsAndMilliseconds(time) ;
    float userscore = format.seconds + (format.milliseconds)*0.1 ;

    struct score scorelist[4];
    struct score temp;

    curs_set(1) ; //reaffiche le curser
    echo() ; //réactive l'affichage des inputs entrée par l'utilisateur

    while (strlen(username) < 4)
    {
        mvwprintw(myWindow,4,1,"Veilliez choisir un nom à 4 lettre pour conserver le score :      ") ;
        mvwgetnstr(myWindow, 4, 62 , username,4) ; //recupere le choix de l'utilisateur
        if(strlen(username) < 4) {
            mvwprintw(myWindow,2,1,"NOM INCORRECTE, VEILLIEZ ENTRER UN NOMBRE A 4 LETTRE ") ;
        }
    }
    
    stringUpper(username) ; //mettre en majuscule le username   

    highscore = fopen("../Data/jeuhighscore.txt", "r");

    if(highscore == NULL){ // Vérifie si le fichier jeuhighscore.txt a bien été ouvert
        endwin() ;
        fprintf(stderr,"Erreur 12 : fichier non ouvert\n") ;
    }

    scorelist[3].score=userscore; //mets le score du joeur dedans
    strcpy(scorelist[3].name, username); //copie le nom du joueur

    fscanf(highscore, "1 %4s %f\n", scorelist[0].name, &scorelist[0].score);
    fscanf(highscore, "2 %4s %f\n", scorelist[1].name, &scorelist[1].score);
    fscanf(highscore, "3 %4s %f\n", scorelist[2].name, &scorelist[2].score);

    for(int i=3;i>0;i--){
        if(scorelist[i].score<scorelist[i-1].score){
            temp.score=scorelist[i-1].score;
            strcpy(temp.name, scorelist[i-1].name);

            scorelist[i-1].score=scorelist[i].score;
            strcpy(scorelist[i-1].name,scorelist[i].name);

            scorelist[i].score=temp.score;
            strcpy(scorelist[i].name, temp.name);
        }
    }

    fclose(highscore) ;
    
    highscore = fopen("../Data/jeuhighscore.txt", "w");

    
    if(highscore == NULL){ // Vérifie si le fichier jeuhighscore.txt a bien été ouvert
        endwin() ;
        fprintf(stderr,"Erreur 13 : Impossible d'écrire dans le fichier\n") ;
    } 
    

    for(int i=0;i<3;i++){
        fprintf(highscore, "%d %4s %.1f\n", (i+1), scorelist[i].name, scorelist[i].score);
    
    }
    werase(myWindow) ;
    box(myWindow,0,0) ;
    mvwprintw(myWindow,2,1,"Meilleurs temps :") ;
    for(int i = 0 ; i < 3 ; i++) {
        mvwprintw(myWindow,3+i,1,"%d %s %.1f",i+1,scorelist[i].name,scorelist[i].score) ;
    }
    noecho() ;


    fclose(highscore);

} 



void after_game(bool victory, int time){
    int userInput ; //input utilisateur pour fermer le jeu

    struct timeFormat format = SecondsAndMilliseconds(time) ; //appel de la structure de format du temps

    WINDOW *afterGameBox = newwin(8,100,22,0); //Fenetre de victoire

    box(afterGameBox,0,0) ; //affiche les bordure dans 
    
    if (victory == true) { //si le joueur a gagner

        mvwprintw(afterGameBox,1,1,"VICTOIRE") ; //affiche la victoire et le temps du joueur
        mvwprintw(afterGameBox,2,1,"Votre Temps : %d.%ds",format.seconds,format.milliseconds) ;
        
        ecriture_score(time,afterGameBox) ;
        mvwprintw(afterGameBox,1,1,"VICTOIRE") ; 
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