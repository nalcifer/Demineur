#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void drawTabUser(char tab_user[SIZE][SIZE]);
void choiceUser(int* colonne, int* ligne);
void bombInit(int colonne, int ligne, char tab_user[SIZE][SIZE], int tab_bomb[SIZE][SIZE]);
void end(int tab_bomb[SIZE][SIZE], char tab_user[SIZE][SIZE], int condition);

int main() {
    srand(time(NULL));
    int tab_bomb[SIZE][SIZE] = {      //Tableau avec placement des bombes
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0}
    };

    char tab_user[SIZE][SIZE] = {      //Tableau vu par le joueur
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'}
    };
    int i, j;
    int condition = 1;
   

    do {
        //Tracer le tableau
        drawTabUser(tab_user);

        //Input user choix de case
        int colonne, ligne;
        choiceUser(&colonne, &ligne);
        while (colonne > SIZE - 1 || ligne > SIZE - 1 || tab_user[colonne][ligne] != 'X') {
            if (colonne > SIZE - 1 || ligne > SIZE - 1) {
                printf("Rentrez des chiffres entre 1 et SIZE\n");
            }
            else if (tab_user[colonne][ligne] != 'X') { //Si mauvais chiffre rentré
                printf("\nVous ne pouvez pas jouer sur cette case !\n");
            }
            choiceUser(&colonne, &ligne);
        }

        //1er coup et Initialisation du tableau bombe
        int first_attempt = 0;
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                if (tab_user[i][j] == 'X') {
                    first_attempt++;
                }
            }
        }
        if (first_attempt == 25) {
            bombInit(colonne, ligne, tab_user, tab_bomb);
        }
        else if (tab_user[colonne][ligne] == 'X') {
            if (tab_bomb[colonne][ligne] != 9) { //Si pas de bombe
                tab_user[colonne][ligne] = tab_bomb[colonne][ligne] + '0';
            }
            else if (tab_bomb[colonne][ligne] == 9) { //Si bombe touché
                tab_user[colonne][ligne] = 'b';
            }
        }

        
        


        //Si perdu stop le jeu
        int win = 0;
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                if (tab_user[i][j] == 'b') {
                    printf("\nPERDU\n");
                    end(tab_bomb, tab_user, condition);

                    if (tab_user[i][j] != 'X') {
                        win++;
                    }
                    if (win == SIZE * SIZE) {
                        printf("\nBravo ! Vous avez reussi.\n");
                        end(tab_bomb, tab_user, condition);
                    }
                }
            }
        } 
    } while (condition);
}


void drawTabUser(char tab_user[SIZE][SIZE]) {
    //Tracer le tableau
    int i, j;
    for (i = 0; i < SIZE; i++) {
        printf("  %d", i + 1);
    }
    for (i = 0; i < SIZE; i++) {
        printf("\n");
        printf("%d", i + 1);

        for (j = 0; j < SIZE; j++) {
            printf("[%c]", tab_user[i][j]);
        }
    }
}

void choiceUser (int *colonne, int *ligne) {
    printf("\nSur quelle case voulez-vous jouer ?\nRentrez les coordonees : ");
    scanf_s("%d %d", colonne, ligne);
    *colonne = *colonne - 1;
    *ligne = *ligne - 1;
}


void bombInit (int colonne, int ligne, char tab_user[SIZE][SIZE], int tab_bomb[SIZE][SIZE]){
    int i, j;
    tab_user[colonne][ligne] = ' ';
        if (colonne < SIZE - 1) {
            tab_user[colonne + 1][ligne] = ' ';
        }
        if (ligne < SIZE - 1) {
            tab_user[colonne][ligne + 1] = ' ';
        }
        if (colonne < SIZE - 1 && ligne < SIZE - 1) {
            tab_user[colonne + 1][ligne + 1] = ' ';
        }
        if (colonne > 0) {
            tab_user[colonne - 1][ligne] = ' ';
        }
        if (ligne > 0) {
            tab_user[colonne][ligne - 1] = ' ';
        }
        if (colonne > 0 && ligne > 0) {
            tab_user[colonne - 1][ligne - 1] = ' ';
        }
        if (colonne < SIZE - 1 && ligne > 0) {
            tab_user[colonne + 1][ligne - 1] = ' ';
        }
        if (colonne > 0 && ligne < SIZE - 1) {
            tab_user[colonne - 1][ligne + 1] = ' ';
        }

        //Initialisation du tableau bombe
        int bomb_number = 0;
        while (bomb_number < SIZE) { //Aléatoire de la position des bombes
            i = rand() % SIZE;
            j = rand() % SIZE;
            if (tab_bomb[i][j] == 0 && tab_user[i][j] == 'X') {
                tab_bomb[i][j] = 9;
                bomb_number++;
            }
        }
        //Indices
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                if (tab_bomb[i][j] != 9) {
                    if (i < SIZE - 1) {
                        if (tab_bomb[i + 1][j] == 9) {
                            tab_bomb[i][j]++;
                        }
                    }
                    if (j < SIZE - 1) {
                        if (tab_bomb[i][j + 1] == 9) {
                            tab_bomb[i][j]++;
                        }
                    }
                    if (i < SIZE - 1 && j < SIZE - 1) {
                        if (tab_bomb[i + 1][j + 1] == 9) {
                            tab_bomb[i][j]++;
                        }
                    }

                    if (i > 0) {
                        if (tab_bomb[i - 1][j] == 9) {
                            tab_bomb[i][j]++;
                        }
                    }
                    if (j > 0) {
                        if (tab_bomb[i][j - 1] == 9) {
                            tab_bomb[i][j]++;
                        }
                    }
                    if (i > 0 && j > 0) {
                        if (tab_bomb[i - 1][j - 1] == 9) {
                            tab_bomb[i][j]++;
                        }
                    }
                    if (i < SIZE - 1 && j > 0) {
                        if (tab_bomb[i + 1][j - 1] == 9) {
                            tab_bomb[i][j]++;
                        }
                    }
                    if (i > 0 && j < SIZE - 1) {
                        if (tab_bomb[i - 1][j + 1] == 9) {
                            tab_bomb[i][j]++;
                        }
                    }
                }
            }
        }
        if (tab_bomb[colonne][ligne] == 9) {
            tab_user[colonne][ligne] = ' ';
        }
        if (colonne < SIZE - 1) {
            tab_user[colonne + 1][ligne] = tab_bomb[colonne + 1][ligne] + '0';
        }
        if (ligne < SIZE - 1) {
            tab_user[colonne][ligne + 1] = tab_bomb[colonne][ligne + 1] + '0';
        }
        if (colonne < SIZE - 1 && ligne < SIZE - 1) {
            tab_user[colonne + 1][ligne + 1] = tab_bomb[colonne + 1][ligne + 1] + '0';
        }
        if (colonne > 0) {
            tab_user[colonne - 1][ligne] = tab_bomb[colonne - 1][ligne] + '0';
        }
        if (ligne > 0) {
            tab_user[colonne][ligne - 1] = tab_bomb[colonne][ligne - 1] + '0';
        }
        if (colonne > 0 && ligne > 0) {
            tab_user[colonne - 1][ligne - 1] = tab_bomb[colonne - 1][ligne - 1] + '0';
        }
        if (colonne < SIZE - 1 && ligne > 0) {
            tab_user[colonne + 1][ligne - 1] = tab_bomb[colonne + 1][ligne - 1] + '0';
        }
        if (colonne > 0 && ligne < SIZE - 1) {
            tab_user[colonne - 1][ligne + 1] = tab_bomb[colonne - 1][ligne + 1] + '0';
        }
}


void end (int tab_bomb[SIZE][SIZE], char tab_user[SIZE][SIZE], int condition) {
    int i, j;
    //Tracer tableau en révélant les bombes
    for (i = 0; i < SIZE; i++) {
        printf("  %d", i + 1);
    }
    for (i = 0; i < SIZE; i++) {
        printf("\n");
        printf("%d", i + 1);

        for (j = 0; j < SIZE; j++) {
            if (tab_bomb[i][j] == 9) {
                printf("[b]");
            }
            else {
                printf("[%c]", tab_user[i][j]);
            }
        }
    }
    //Rejouer
    printf("\n\nVoulez-vous rejouer ? 1:Oui 0:Non :  ");
    scanf_s("%d", &condition);
    while (condition != 1 && condition != 0) {
        printf("\nReponse non valide.\nVoulez-vous rejouer ? 1:Oui 0:Non :  ");
        scanf_s("%d", &condition);
    }
}
