#include <stdio.h>
#include <stdlib.h>

int main(){
    srand(time(NULL));
    int table_bomb[5][5] = {      //Tableau avec placement des bombes
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0}
    };

    char table_user[5][5] = {      //Tableau vu par le joueur
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'}
    };
    int i, j;
    int condition = 1;

    //Initialisation du tableau bombe (avec indices)
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (table_bomb[i][j] == 0) {
                table_bomb[i][j] = rand() % 4 + 1;   //Aléatoire des bombes
            }
        }
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (table_bomb[i + 1][j] == 1) {
                table_bomb[i][j] = table_bomb[i][j] + 1;
            }
            if (table_bomb[i][j + 1] == 1) {
                table_bomb[i][j]++;
            }
            if (table_bomb[i + 1][j + 1] == 1) {
                table_bomb[i][j]++;
            }
        }
    }

    while (condition) {
        //Tracer le tableau
        for (i = 0; i < 5; i++) {
            printf("  %d", i + 1);
        }
        for (i = 0; i < 5; i++) {
            printf("\n");
            printf("%d", i + 1);

            for (j = 0; j < 5; j++) {
                printf("[%c]", table_user[i][j]);
            }
        }

        //Input user choix de case
        int colonne, ligne;
        printf("\nSur quelle case voulez-vous jouer ?\nRentrez les coordonees : ");
        scanf_s("%d %d", &colonne, &ligne);
        colonne = colonne - 1;
        ligne = ligne - 1;

        //Remplacer case joué dans tableau à afficher
        if (table_user[colonne][ligne] == 'X') {
            if (table_bomb[colonne][ligne] != 1) { //Si pas de bombe
                table_user[colonne][ligne] = "%c",table_bomb[colonne][ligne];
            }
            else if (table_bomb[colonne][ligne] == 1) { //Si bombe touché
                table_user[colonne][ligne] = 'b';
            }
        }
        else if (colonne > 5 || ligne > 5) { //Si mauvais chiffre rentré
            printf("Rentrez des chiffres entre 1 et 5\n");
        }
        else if (table_user[colonne][ligne] != 'X') { //Si mauvais chiffre rentré
            printf("\nVous ne pouvez pas jouer sur cette case !\n");
        }
        

        //Si perdu stop le jeu
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (table_user[i][j] == 'b') {
                    condition = 0;
                    printf("\nPERDU\n"); 
                    //Tracer tableau en révélant les bombes
                    for (i = 0; i < 5; i++) {
                        printf("  %d", i + 1);
                    }
                    for (i = 0; i < 5; i++) {
                        printf("\n");
                        printf("%d", i + 1);

                        for (j = 0; j < 5; j++) {
                            if (table_bomb[i][j] == 1) {
                                printf("[b]");
                            }
                            else {
                                printf("[%c]", table_user[i][j]);
                            }
                        }
                    }

                }
            }
        }
    }

}
