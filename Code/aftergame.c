#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h> // Librarie pour utiliser le chrono
#include <stdbool.h>

#include "game.h"

struct score{ // Structure de score 
    char name[5];
    float score;
};

/*
Fonction : stringUpper
Param : *string correspond à un pointeur sur une chaîne de caractère sur laquelle on va appliquer la fonction
Traitement : Cette fonction va parcourir la chaîne de caractères prise en paramètre et va mettre chaque caractère en majuscule
*/
void stringUpper ( char *string ) { // Permet de convertire un string en majuscule
    while( *string ){ 
        *string=toupper( *string ); 
        string++; 
    }
}

/*
Fonction : affichage_scores
Param : *classement correspond à un pointeur sur une liste de structures de type score et myWindow correspond à la fenêtre sur laquelle on va afficher cette fonction
Traitement : Affiche le message "Meilleurs temps :" ainsi que les 3 meilleurs temps
*/
void affichage_scores(struct score *classement,WINDOW* myWindow) {
    werase(myWindow) ;
    box(myWindow,0,0) ;
    mvwprintw(myWindow,2,1,"Meilleurs temps :") ;
    for(int i = 0 ; i < 3 ; i++) {
        mvwprintw(myWindow,3+i,1,"%d %s %.1f",i+1,classement[i].name,classement[i].score) ;
    }
    noecho() ;
} 

/*
Fonction : ecriture_scores
Param : *classement correspond à un pointeur sur une liste de structures de type score et *fichier_score correspond à un pointeur sur le fichier contenant les scores
Traitement : écrit les 3 meilleurs scores dans le fichier jeuhighscore.txt
*/
void ecriture_scores(struct score *classement,FILE *fichier_score) {
    if(fichier_score == NULL){ // Vérifie si le fichier jeuhighscore.txt a bien été ouvert
        endwin() ;
        fprintf(stderr,"Erreur 13 : Impossible d'écrire dans le fichier\n") ;
    } 
    else {
        for(int i=0;i<3;i++){ // Met à jour le fichier
        fprintf(fichier_score, "%d %4s %.1f\n", (i+1), classement[i].name, classement[i].score);
    }
    }    

}

/*
Fonction : gestion_classement
Param : time correspond au score de l'utilisateur, myWindow correspond à la fenêtre dans laquelle la fonction va s'éxécuter, victory permet de récupérer si le joueur a gagné ou non
Traitement : Cette fonction va lire le fichier jeuhighscore.txt et va enregistrer les scores dans une liste de structures de type score. Si le joueur a gagné, elle va lui demander un pseudo et va comparer son score avec les autres. Elle va ensuite réécrire le fichier jeuhighscore.txt avec les nouveaux meilleurs scores.
*/
void gestion_classement(int time, WINDOW *myWindow,bool victory) {
    FILE *highscore;
    char username[5] ; // Variable stockant le nom

    struct timeFormat format = SecondsAndMilliseconds(time) ;
    float userscore = format.seconds + (format.milliseconds)*0.1 ;

    struct score scorelist[4];
    struct score temp;

    curs_set(1) ; // Réaffiche le curseur
    echo() ; // Réactive l'affichage des input entrés par l'utilisateur

    highscore = fopen("../../Data/jeuhighscore.txt", "r"); // Ouverture du fichier en mode lecture

    if(highscore == NULL){ // Vérifie si le fichier jeuhighscore.txt a bien été ouvert
        endwin() ;
        fprintf(stderr,"Erreur 12 : fichier non ouvert\n") ;
    }

    else{
        for(int i = 0; i < 3; i++){ // Copie les scores dans la liste des variables score
            fscanf(highscore, "%d %4s %f\n", (&i) + 1,scorelist[i].name, &scorelist[i].score);
        }

        if(victory == true) { // Demande le pseudo du joueur s'il a gagné 
            while (strlen(username) < 4) // Demande au joueur d'entrer son nom. Si le nom est trop petit, le programme va lui redemander.
            {
                mvwprintw(myWindow,4,1,"Veuillez choisir un nom à 4 lettre pour enregistrer le score :      ") ;
                mvwgetnstr(myWindow, 4, 62 , username,4) ; //recupere le choix de l'utilisateur
                if(strlen(username) < 4) { // Affiche un message si le pseudo est incorrect
                    mvwprintw(myWindow,2,1,"NOM INCORRECT, VEUILLEZ ENTRER UN NOM À 4 LETTRES") ;
                }
            }
    
        stringUpper(username) ; // Met le pseudo en majuscule  

        scorelist[3].score=userscore; // Enregistre le score du joueur à l'indice 4 de scorelist.score
        strcpy(scorelist[3].name, username); // Enregistre le pseudo du joueur à l'indice 4 de scorelist.name

        for(int i=3;i>0;i--){ // Programme de comparaison et de déplacement des scores
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
        fclose(highscore) ; // Ferme le fichier en mode lecture

        affichage_scores(scorelist,myWindow) ; // Affiche les scores
    

        if(victory == true) { // Réécrit le fichier si le joueur a gagné 
            highscore = fopen("../../Data/jeuhighscore.txt", "w"); // Ouvre le fichier en mode écriture
            ecriture_scores(scorelist,highscore);
            fclose(highscore);
        }

    }

}

/*
Fonction : after_game
Param : victory correspond à un booléen permettant de récupérer si le joueur a gagné ou non, time permet de récupéré le temps effectué par le joueur
Traitement : Si le joueur a gagné, va afficher un message de victoire avec le temps effectué par le joueur, puis va ensuite enregistrer le score du joueur. Sinon, affiche simplement les meilleurs scores.
*/
void after_game(bool victory, int time){
    int userInput ; // Récupère un input qui permettra de fermer le jeu

    struct timeFormat format = SecondsAndMilliseconds(time) ; // Appel de la structure de format du temps

    WINDOW *afterGameBox = newwin(8,100,22,0); // Fenêtre de victoire

    box(afterGameBox,0,0) ; // Affiche les bordure dans la fenêtre d'après jeu
    
    if (victory == true) { // Si le joueur a gagné 

        mvwprintw(afterGameBox,1,1,"VICTOIRE") ; // 
        mvwprintw(afterGameBox,2,1,"Votre Temps : %d.%ds",format.seconds,format.milliseconds) ;
        
        gestion_classement(time,afterGameBox,victory) ;
    }

    else { // Si le joueur perd
        gestion_classement(time,afterGameBox,victory) ;
    }
        wrefresh(afterGameBox) ;
    while (1)
    { // Attend un input avant de fermer le jeu

        userInput = getch() ;
        if(userInput != -1 ) { // Quand échap est pressé, termine le jeu (features debug)
            break;
        }
    }
}