//début partie Fire Order

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int values[12];
int occurrences[12] = {0};  // Ajuster la taille pour correspondre au nombre de cartes

static inline void init();
static inline void cardLettersDistrib();
static inline void setSecondCardBlue();

int main() {
    int height = 7, width = 9;
    int start_y = 2, start_x = 2;
    int horizontal_spacing = width + 2;
    int vertical_spacing = height + 2;

    int player_x = 3;
    int player_y = 1;

    int selected_indices[2] = {-1, -1};  // Stocker les indices des cartes sélectionnées
    int selected_values[2] = {-1, -1};   // Stocker les valeurs des cartes sélectionnées
    int selected_count = 0;  // Nombre de cartes sélectionnées

    int first_card_y = -1;
    int first_card_x = -1;

    int second_card_y = -1;
    int second_card_x = -1;

    init();
    cardLettersDistrib(values);

    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Initialise la paire de couleur verte
    init_pair(2, COLOR_CYAN, COLOR_BLACK); // Initialise la paire de couleur cyan
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // Initialise la paire de couleur blanche

    while (1) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 6; j++) {
                WINDOW *win = newwin(height, width, start_y + i * vertical_spacing, start_x + j * horizontal_spacing);
                refresh();

                int index = i * 6 + j;

                box(win, 0, 0);

                // Vérifier si la carte est retournée ou si le curseur du joueur est positionné sur cette carte
                if (occurrences[index] == 1 || (j == player_x && i == player_y)) {
                    // Vérifier si la carte est actuellement sélectionnée pour la mise en surbrillance
                    if (selected_count > 0 && index == selected_indices[selected_count - 1]) {
                        wattron(win, COLOR_PAIR(2));  // Utiliser la nouvelle paire de couleur pour la surbrillance
                    } else {
                        // Utiliser la paire de couleur blanche pour les cartes correspondantes
                        if (occurrences[index] == 1) {
                            wattron(win, COLOR_PAIR(3));
                            mvwprintw(win, 0, 0, "o-------o");
                            mvwprintw(win, 6, 0, "o-------o");
                        } else {
                            // Utiliser la paire de couleur verte pour les cartes non sélectionnées
                            wattron(win, COLOR_PAIR(1));
                        }
                    }
                }

                mvwprintw(win, 0, 0, " ------- ");
                mvwprintw(win, 6, 0, " ------- ");

                for (int k = 1; k <= 5; k++) {
                    mvwprintw(win, k, 0, "|       |");
                }

                if (occurrences[index] == 1) {
                    mvwprintw(win, height / 2, (width - 1) / 2, "%c", values[index]);
                }

                // Vérifier si la carte est retournée ou si le curseur du joueur est positionné sur cette carte
                if (occurrences[index] == 1 || (j == player_x && i == player_y)) {
                    // Vérifier si la carte est actuellement sélectionnée pour la mise en surbrillance
                    if (selected_count > 0 && index == selected_indices[selected_count - 1]) {
                        wattron(win, COLOR_PAIR(2));  // Utiliser la nouvelle paire de couleur pour la surbrillance
                    } else {
                        // Utiliser la paire de couleur blanche pour les cartes correspondantes
                        if (occurrences[index] == 1) {
                            wattron(win, COLOR_PAIR(3));
                            mvwprintw(win, 0, 0, "o-------o");
                            mvwprintw(win, 6, 0, "o-------o");
                        } else {
                            // Utiliser la paire de couleur verte pour les cartes non sélectionnées
                            wattron(win, COLOR_PAIR(1));
                        }
                    }
                }

            wrefresh(win);
        }
    }

        int c = getch();
        switch (c) {
            case 'a':
                do {
                    if (player_x > 0) {
                        player_x--;
                    } else {
                        if (player_y == 0) {
                            player_y = 1;
                            player_x = 5;
                        } else if (player_y == 1) {
                            player_y = 0;
                            player_x = 5;
                        }
                    }
                } while (occurrences[player_y * 6 + player_x] == 1);
                break;
            case 'z':
                do {
                    if (player_x < 5) {
                        player_x++;
                    } else {
                        if (player_y == 0) {
                            player_y = 1;
                            player_x = 0;
                        } else if (player_y == 1) {
                            player_y = 0;
                            player_x = 0;
                        }
                    }
                } while (occurrences[player_y * 6 + player_x] == 1);
                break;
            case 'e':
            // Vérifier si la carte sélectionnée n'a pas encore été retournée et que le nombre maximal de cartes sélectionnées n'a pas été atteint
            if (selected_count < 2) {
            // Marquer la carte comme retournée si elle ne l'est pas déjà
                if (occurrences[player_y * 6 + player_x] == 0) {
                    occurrences[player_y * 6 + player_x] = 1;
                    refresh();


                    // Stocker l'index de la carte sélectionnée
                    selected_indices[selected_count] = player_y * 6 + player_x;

                    // Stocker la valeur de la carte sélectionnée
                    selected_values[selected_count] = values[selected_indices[selected_count]];

                    // Incrémenter le nombre de cartes sélectionnées
                    selected_count++;
                }
            }

            // Vérifier si deux cartes ont été sélectionnées
            if (selected_count == 2) {

                refresh();

                // Coordonnées de la deuxième carte sélectionnée
                int second_card_y = start_y + player_y * vertical_spacing;
                int second_card_x = start_x + player_x * horizontal_spacing;
                int middle_values = values[player_y * 6 + player_x];

                setSecondCardBlue(second_card_y, second_card_x, middle_values);

                // Attendre 2 secondes
                sleep(2);

                // Sauvegarder la position des deux cartes
                if (selected_values[0] != selected_values[1]) {
                    for (int i = 0; i < 2; i++) {
                        occurrences[selected_indices[i]] = 0;
                    }
                }

                selected_count = 0;
            }
            break;
            case 'q':
          keypad(stdscr, TRUE); //Permet l'utilisation du clavier      endwin();
                return 0;
            }

        clear();
    }
}


static inline void init() {
    initscr(); // Initialise l'écran d'affichage des cartes
    start_color();
    cbreak();
    noecho(); // Désactivation de l'affichage automatique des caractères saisis
    curs_set(0); // Désactivation de l'affichage automatique du curseur
    keypad(stdscr, TRUE); //Permet l'utilisation du clavier

    return;
}

static inline void cardLettersDistrib(int entry[12]){
    for (int i = 0; i < 6; i++) {
        entry[i] = 'A' + i;
        entry[i + 6] = 'A' + i;
    }

    for (int i = 11; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = entry[i];
        entry[i] = entry[j];
        entry[j] = temp;
    }

    return;
}

static inline void setSecondCardBlue(int card_y, int card_x, int value) {
    wattron(stdscr, COLOR_PAIR(2));
    mvwprintw(stdscr, card_y, card_x, " ------- ");
    mvwprintw(stdscr, card_y + 1, card_x, "|       |");
    mvwprintw(stdscr, card_y + 2, card_x, "|       |");
    mvwprintw(stdscr, card_y + 3, card_x, "|   %c   |", value);
    mvwprintw(stdscr, card_y + 4, card_x, "|       |");
    mvwprintw(stdscr, card_y + 5, card_x, "|       |");
    mvwprintw(stdscr, card_y + 6, card_x, " ------- ");
    wrefresh(stdscr);

    return;
}

//Fin partie Fire Order
