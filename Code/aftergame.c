#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h> //librarie pour utiliser le chrono
#include <stdbool.h>

#include "game.h"

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

void affichage_scores(struct score *classement,WINDOW* myWindow) {
    werase(myWindow) ;
    box(myWindow,0,0) ;
    mvwprintw(myWindow,2,1,"Meilleurs temps :") ;
    for(int i = 0 ; i < 3 ; i++) {
        mvwprintw(myWindow,3+i,1,"%d %s %.1f",i+1,classement[i].name,classement[i].score) ;
    }
    noecho() ;
} 

void ecriture_scores(struct score *classement,FILE *fichier_score) {
    if(fichier_score == NULL){ // Vérifie si le fichier jeuhighscore.txt a bien été ouvert
        endwin() ;
        fprintf(stderr,"Erreur 13 : Impossible d'écrire dans le fichier\n") ;
    } 
    else {
        for(int i=0;i<3;i++){ //mets à jours le fichier 
        fprintf(fichier_score, "%d %4s %.1f\n", (i+1), classement[i].name, classement[i].score);
    }
    }    

}

void gestion_classement(int time, WINDOW *myWindow,bool victory) {
    FILE *highscore;
    char username[5] ; //variable qui vas stocker le nom

    struct timeFormat format = SecondsAndMilliseconds(time) ;
    float userscore = format.seconds + (format.milliseconds)*0.1 ;

    struct score scorelist[4];
    struct score temp;

    curs_set(1) ; //reaffiche le curser
    echo() ; //réactive l'affichage des inputs entrée par l'utilisateur

    highscore = fopen("../../Data/jeuhighscore.txt", "r"); //ouverture du fichier en mode lecture

    if(highscore == NULL){ // Vérifie si le fichier jeuhighscore.txt a bien été ouvert
        endwin() ;
        fprintf(stderr,"Erreur 12 : fichier non ouvert\n") ;
    }

    else{
        for(int i = 0; i < 3; i++){ //copie des score dans la liste des variables scores
            fscanf(highscore, "%d %4s %f\n", (&i) + 1,scorelist[i].name, &scorelist[i].score);
        }

        if(victory == true) { //demande le pseudo si le joueur a gagner 
            while (strlen(username) < 4) //Demande au joueur de rentrer son nom, si il est trop petit, il redemande
            {
                mvwprintw(myWindow,4,1,"Velliez choisir un nom à 4 lettres pour conserver le score :      ") ;
                mvwgetnstr(myWindow, 4, 62 , username,4) ; //recupere le choix de l'utilisateur
                if(strlen(username) < 4) { //affiche ce messages si le pseudo est incorrecte
                    mvwprintw(myWindow,2,1,"NOM INCORRECT, VELLIEZ ENTRER UN NOM A 4 LETTRES") ;
                }
            }
    
        stringUpper(username) ; //mettre en majuscule le username   

        scorelist[3].score=userscore; //mets le score du joeur dedans
        strcpy(scorelist[3].name, username); //copie le nom du joueur

        for(int i=3;i>0;i--){ //programme de comparaison et de déplacement des scores.
            if(scorelist[i].score<scorelist[i-1].score){
                temp.score=scorelist[i-1].score;
                strcpy(temp.name, scorelist[i-1].name);

                scorelist[i-1].score=scorelist[i].score;
                strcpy(scorelist[i-1].name,scorelist[i].name);

                scorelist[i].score=temp.score;
                strcpy(scorelist[i].name, temp.name);
                }
            }

        }
        fclose(highscore) ; //ferme le fichier en mode lecture

        affichage_scores(scorelist,myWindow) ; //affiche les scores 
    
        if(victory == true) { //reecrit le fichier si le joueur à gagner 
            highscore = fopen("../../Data/jeuhighscore.txt", "w"); //ouvre le fichier en mode écriture
            ecriture_scores(scorelist,highscore);
            fclose(highscore);
        }

    }

}

void after_game(bool victory, int time){
    int userInput ; //input utilisateur pour fermer le jeu

    struct timeFormat format = SecondsAndMilliseconds(time) ; //appel de la structure de format du temps

    WINDOW *afterGameBox = newwin(8,100,22,0); //Fenetre de victoire

    box(afterGameBox,0,0) ; //affiche les bordure dans 
    
    if (victory == true) { //si le joueur a gagner

        mvwprintw(afterGameBox,1,1,"VICTOIRE") ; //affiche la victoire et le temps du joueur
        mvwprintw(afterGameBox,2,1,"Votre Temps : %d.%ds",format.seconds,format.milliseconds) ;
        
        gestion_classement(time,afterGameBox,victory) ;
    }

    else { //si joueur perds
        gestion_classement(time,afterGameBox,victory) ;
    }
        wrefresh(afterGameBox) ;
    while (1)
    { //attends un echap avant de quitter le jeu

        userInput = getch() ;
        if(userInput != -1 ) { //Quand echap press, termine le jeu (features debug)
            break;
        }
    }
}