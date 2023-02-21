#include <stdio.h>

int main()
{
    char table_bomb[5][5] = {      //Tableau avec placement des bombes
       {'b', 'o', 'b', 'o', 'o'} ,
       {'o', 'o', 'b', 'o', 'o'} ,
       {'o', 'o', 'o', 'o', 'b'} ,
       {'o', 'b', 'o', 'o', 'o'} ,
       {'o', 'o', 'o', 'b', 'o'}
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

    while (condition) {
        //Tracer le tableau
        for (i = 0; i < 5; i++) {
            printf("  %d", i + 1);
        }
        for (i = 0; i < 5; i++) {
            printf("\n");
            printf("%d", i + 1);

            for (j = 0; j < 5; j++) {
                if (table_user[i][j] == 'X') {
                    printf("[X]");
                }
                else {
                    printf("[%c]", table_user[i][j]);
                }
            }
        }

        //Input user choix de case
        int colonne, ligne;
        printf("\nSur quelle case voulez-vous jouer ? :");
        scanf_s("%d %d", &colonne, &ligne);

        //Remplacer case joué dans tableau à afficher
        if (table_user[colonne][ligne] == 'X' && table_bomb[colonne][ligne] == 'o') { //Si pas de bombe
            table_user[colonne][ligne] = ' ';
        }
        else if (table_bomb == 'b') { //Si bombe touché
            table_user[colonne][ligne] = 'b';
        }
        else {
            printf("Refaite votre choix\n");
        }

        //Si perdu stop le jeu
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (table_user[i][j] == 'b') {
                    condition = 0;
                    printf("T as perdu miskin");
                }
            }
        }
    }

}