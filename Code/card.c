#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h> // Librarie pour utiliser le chrono
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"

static bool inputDisable = false; // Valeur static qui va permettre de désactiver les input du joueur

typedef struct card { // Structure qui gère le format des cartes (leur position et leur status)
    WINDOW* windowCard; // Fenêtre de la carte
    char status ; // Status de la carte
    int value ; // Valeur de la carte
    bool selected ; // Etat sélectionné pour l'algo de pairage
    bool paired ; // Etat pairé (sont affichée mais pas sélectionnable et impossible de passer dessus)
}playcard;

/*
Fonction : hiddenCard
Param : chosenCard correspond à la carte choisie par l'utilisateur, et debugMode permet de dire si oui ou non le mode debug est activé
Traitement : Cette fonction permet de créer les cartes face cachée, et d'afficher la valeur se trouvant sur l'autre coté de la carte si le mode debug est activé
*/
void hiddenCard(playcard chosenCard , bool debugMode) { // Affiche une carte face cachée. Si le mode debug est activé, on affiche également la lettre
    wattron(chosenCard.windowCard,COLOR_PAIR(1)) ; // Défini la couleur de la carte
    wborder(chosenCard.windowCard,'|','|','-','-',' ',' ',' ',' ') ; // Créé les bordure de la carte
    if(debugMode == true) { // Si le mode debug est activé, affiche la valeur
        mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    }
    else{
        mvwprintw(chosenCard.windowCard,3,4," ") ; // Sinon, n'affiche rien
    }
    wrefresh(chosenCard.windowCard) ; // Refesh la carte
}

/*
Fonction : definitionCard
Param : *carte est un pointeur sur un paquet de cartes
Traitement : Permet de créer l'ensemble des cartes du jeu en mettant les symboles dans un ordre aléatoire
*/
void definitionCard(playcard *carte) { // Va définir les valeurs de la liste des cartes (leur position, leur valeur et leur status)

    int position_x[6] = {1,11,21,31,41,51} ; // Position x de la carte, il y a une liste pour les cartes d'une rangée
    int position_y = 5; //position y de la carte, la premiere rangee commence en 5
    int valeurRand, temp ; //definition des valeur utiliser pour l'algo de trie aleatoire
    int cardValue[12] = {'A','A','B','B','C','C','D','D','E','E','F','F'} ; //definition de toutes les valeur utiliser pour les cartes 

    srand(time(NULL)); // Seed du random 

    for(int i = 0 ; i < 12;i++) { // Algorithme de tri aléatoire
        valeurRand = rand() % 12 ;

        temp = cardValue[i] ;
        cardValue[i] = cardValue[valeurRand] ;
        cardValue[valeurRand] = temp ;
    }

    for(int i = 0 ; i < 12 ;i++) { // Boucle qui va définir toutes les cartes par défaut
            if(i == 6) { // Position en hauteur qui va changer si on change de range
                position_y = 13; // 13 correspond à la valeur de la deuxième rangée
            }
            carte[i].windowCard = newwin(7,9,position_y,position_x[i%6]) ; // Création de la fenêtre de la carte, elle va définir la hauteur et largeur de l'espace de la carte
            carte[i].status = 'h' ; // Status qui va gérer si le joueur est au dessus de la carte ou pas. Par défaut, le joueur ne se trouve pas dessus
            carte[i].value = cardValue[i] ; // Valeur de la carte
            carte[i].selected = false ; // Si elle est sélectionnée par le joueur
            carte[i].paired = false ; // Si elle est déjà pairée
    }
}

/*
Fonction : printCard
Param : *carte est un pointeur sur un paquet de carte et debugMode est un booléen permettant de savoir si le debugMode est activé ou non
Traitement : Premet d'affiche toutes les cartes
*/
void printCard(playcard *carte, bool debugMode) { // Défini et affiche toutes les cartes du jeu
    definitionCard(carte);
    for(int i = 0;i < 12;i++){
        hiddenCard(carte[i],debugMode) ;
    }
}

/*
Fonction : onCard
Param : chosenCard correspond à la carte sur laquelle le joueur se trouve, debugMode est un booléen permettant de savoir si le debugMode est activé ou non
Traitement : Permet au joueur de sélectionner une carte et de la mettre en verte lorsque c'est le cas
*/
void onCard(playcard chosenCard,bool debugMode) { // Si le joueur est sur la carte, celle-ci devient verte
    wattron(chosenCard.windowCard,COLOR_PAIR(2)) ;
    wborder(chosenCard.windowCard,'|','|','-','-',' ',' ',' ',' ') ;
    if(debugMode == true) { // Si le mode debug est activé, affiche la valeur de la carte
        mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    }
    else{
        mvwprintw(chosenCard.windowCard,3,4," ") ; // Sinon, cela n'affiche rien
    }
    wrefresh(chosenCard.windowCard) ;
}

/*
Fonction : pairedCard
Param : chosenCard correspond à la carte sur laquelle la fonction va s'appliquer
Traitement : Permet de changer les coins de la carte avec des 0 lorsque celle-ci est pairée.
*/
void pairedCard(playcard chosenCard) { // Si elle est pairée, les coins de la carte sont des 0
    wattron(chosenCard.windowCard,COLOR_PAIR(1)) ;
    wborder(chosenCard.windowCard,'|','|','-','-','0','0','0','0') ;
    mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    wrefresh(chosenCard.windowCard) ;
}

/*
Fonction : selectedCard
Param : chosenCard correspond à la carte sur laquelle la fonction va s'appliquer
Traitement : Permet au joueur de sélectionner une carte et ainsi d'afficher sa valeur
*/
void selectedCard(playcard chosenCard){ // Si la carte est sélectionnée, elle devient bleu et on affiche sa valeur
    wattron(chosenCard.windowCard,COLOR_PAIR(3)) ;
    wborder(chosenCard.windowCard,'|','|','-','-',' ',' ',' ',' ') ;    
    mvwprintw(chosenCard.windowCard,3,4,"%c",chosenCard.value) ;
    wrefresh(chosenCard.windowCard) ;
}   

/*
Fonction : cardStatusUpdate
Param : *chosenCard est un pointeur sur la liste des cartes, userPosition permet de récupérer la position où se trouve l'utilisateur et debugMode permet de savoir si le mode debug est activé ou non
Traitement : résumé succinct de son traitement
*/
void cardStatusUpdate(playcard *chosenCard,int userPosition, bool debugMode){ // Va update le status de la carte selon la position du jeu et son état dans le jeu
    for(int i=0;i < 12;i++){ // Va parcourir toutes les cartes
        if(chosenCard[i].status != 'p'){// Si la carte n'est pas cachée, on la remet en position cachée
            chosenCard[i].status = 'h'; 
        }

        if(i == userPosition){ // Si la carte parcourue est égale à la carte où se trouve le joueur, alors son status est égal à o
            chosenCard[userPosition].status = 'o' ;
        }

        switch (chosenCard[i].status) // Switch qui va visuellement mettre à jour la carte selon son status
        {
        case 'o':
            onCard(chosenCard[i],debugMode); // Affiche la carte en vert 
            break;
        case 'h':
            hiddenCard(chosenCard[i],debugMode); // Affiche la carte en mode caché selon si le mode debug est activé ou non
            break;
        }

        if(chosenCard[i].selected == true) { // La met en bleu et affiche sa valeur
            selectedCard(chosenCard[i]) ;
        }

        if(chosenCard[i].paired == true) { // Si la carte est pairée, alors on l'affiche en mode pairé
            pairedCard(chosenCard[i]) ;
        }

    }
}

/*
Fonction : checkPaires
Param : *chosenCard est un pointeur sur la liste des cartes, start_time récupère le temps de la machine auquel le programme a commencé, current_time récupère le temps actuel de la machine, myWindow correspond à la fenêtre sur laquelle la fonction va s'effectuer
Traitement : Regarde dans tout le paquet s'il y a des cartes sélectionnées ou non. Si deux cartes sont sélectionnées, alors on met un délai de 2 secondes et on les compare. Si elles sont égales, alors on change leur status en mode pairé et on ajoute une paire au nombre de paires total.
*/
void checkPaires(playcard *chosenCard,struct timeval start_time, struct timeval current_time, WINDOW * myWindow) { // Algorithme permettant de vérifier si la carte est pairée ou non  
    int paires[2] = {-1,-1}; // Liste qui va enregistrer les indices des 2 cartes sélectionées
    int elapsed_time,start_break ;

    for(int i = 0; i < 12;i++){ // Va parcourir toutes les cartes pour lire leur status
        if(chosenCard[i].selected == true) { // Si la carte est selectionnée, alors on va chercher à l'ajouter dans la liste des paires
            if(paires[0] == -1) { // Si pas de valeur, alors paires[0] = l'indice de la première sélection
                paires[0] = i ;
                selectedCard(chosenCard[i]) ; // Affiche la carte en mode sélectionné
            }
            else{ // Si une carte déjà sélectionnée, alors on enregistre le deuxième indice afin de l'utiliser 
                paires[1] = i ;
                selectedCard(chosenCard[i]) ;
            }
        }
    }

    if(paires[0] != -1 && paires[1] != -1){ // Si deux cartes sont sélectionnée, alors on va vérifier si elles sont paires
        inputDisable = true ; // Désactive les input
        start_break = affichage_temps(start_time,current_time,myWindow);

        while ((elapsed_time / 1000) < (start_break / 1000) + 2){ // Fait tourner le chrono pendant 2 secondes le temps de tester si les deux sont bien des paires
            gettimeofday(&current_time, NULL) ;
            elapsed_time = affichage_temps(start_time,current_time,myWindow); }// Refesh le chrono du temps
        inputDisable = false; // Redonne les inputs à la fin du timer

        for(int i = 0 ; i < 2; i++){ // Enlève l'état de sélection des deux cartes
            chosenCard[paires[i]].selected = false;
        } 

        if(chosenCard[paires[0]].value == chosenCard[paires[1]].value) { // Si la valeur des deux cartes est identique
            for(int i = 0; i < 2; i++){
                pairedCard(chosenCard[paires[i]]); // On affiche les cartes en mode pairé
                chosenCard[paires[i]].paired = true; // On donne le status paires
                numberOfPairs++; // On augmente le nombre de paires qui on été trouvée
            }
            return ;
        }
        
        else{ // Sinon, on retourne toutes les cartes en mode caché
            for(int i = 0;i < 2;i++){
                hiddenCard(chosenCard[paires[i]],false) ;
            }
        }
    }
    return ;
}

/*
Fonction : checkPose
Param : pose récupère la position sur laquelle se trouve le joueur, et *chosenCard est un pointeur sur le paquet de cartes
Traitement : Altère la position du joueur s'il sort des 12 cartes et le remet au début ou à la fin. De plus, si le carte du début ou de la fin est pairée, on le décale d'une carte supplémentaire.
Retour : Renvoie pose qui correspond à la position altérée de l'utilisateur
*/
int checkPose(int pose,playcard *chosenCard){ // Réajuste la position du joueur s'il sort de la liste
    if(pose > 11) { // S'il va en dehors du paquet de 12 cartes, on le remet à la position 0
        pose = 0 ;
        while(chosenCard[pose].paired == true) { // Si la carte est paire à cette position, alors on la décale encore de 1
               pose ++;
            }   
        } 
    else if(pose < 0) { // Idem mais dans l'autre sens
        pose = 11 ;
        while(chosenCard[pose].paired == true) {
           pose --;
        } 
    }
    return pose; // Retourne la position du joueur une fois ajustée
}