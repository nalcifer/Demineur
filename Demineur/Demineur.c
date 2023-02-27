#include <stdio.h>
#include <stdlib.h>

int main(){
    srand(time(NULL));
    int tab_bomb[5][5] = {      //Tableau avec placement des bombes
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0}
    };

    char tab_user[5][5] = {      //Tableau vu par le joueur
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'} ,
       {'X', 'X', 'X', 'X', 'X'}
    };
    int i, j;
    int condition = 1;
    int bomb_number = 0;

    do {
        //Tracer le tableau
        for (i = 0; i < 5; i++) {
            printf("  %d", i + 1);
        }
        for (i = 0; i < 5; i++) {
            printf("\n");
            printf("%d", i + 1);

            for (j = 0; j < 5; j++) {
                printf("[%c]", tab_user[i][j]);
            }
        }

        //Input user choix de case
        int colonne, ligne;
        printf("\nSur quelle case voulez-vous jouer ?\nRentrez les coordonees : ");
        scanf_s("%d %d", &colonne, &ligne);
        colonne = colonne - 1;
        ligne = ligne - 1;

        //Remplacer case joué dans tableau à afficher
        int first_attempt = 0; //Verifier si 1er coup
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (tab_user[i][j] == 'X') {
                    first_attempt++;
                }
            }
        }
        if (first_attempt == 25) { //1er coup 
            tab_user[colonne][ligne] = ' ';
            tab_user[colonne + 1][ligne] = ' ';
            tab_user[colonne][ligne + 1] = ' ';
            tab_user[colonne + 1][ligne + 1] = ' ';
            tab_user[colonne - 1][ligne] = ' ';
            tab_user[colonne][ligne - 1] = ' ';
            tab_user[colonne - 1][ligne - 1] = ' ';
            tab_user[colonne + 1][ligne - 1] = ' ';
            tab_user[colonne - 1][ligne + 1] = ' ';
        //------------------------------------------------------------------------------------
            //Initialisation du tableau bombe
            while (bomb_number < 5) { //Aléatoire de la position des bombes
                i = rand() % 5;
                j = rand() % 5;
                if (tab_bomb[i][j] == 0 && tab_user[i][j] == 'X') {
                    tab_bomb[i][j] = 9;
                    bomb_number++;
                }
            }
            //Indices
            for (i = 0; i < 5; i++) {
                for (j = 0; j < 5; j++) {
                    if (tab_bomb[i][j] != 9) {
                        if (i < 4) {
                            if (tab_bomb[i + 1][j] == 9) {
                                tab_bomb[i][j]++;
                            }
                        }
                        if (j < 4) {
                            if (tab_bomb[i][j + 1] == 9) {
                                tab_bomb[i][j]++;
                            }
                        }
                        if (i < 4 && j < 4) {
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
                        if (i < 4 && j > 0) {
                            if (tab_bomb[i + 1][j - 1] == 9) {
                                tab_bomb[i][j]++;
                            }
                        }
                        if (i > 0 && j < 4) {
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
            if (colonne < 4) {
                tab_user[colonne + 1][ligne] = tab_bomb[colonne + 1][ligne] + '0';
            }
            if (ligne < 4) {
                tab_user[colonne][ligne + 1] = tab_bomb[colonne][ligne + 1] + '0';
            }
            if (colonne < 4 && ligne < 4) {
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
            if (colonne < 4 && ligne > 0) {
                tab_user[colonne + 1][ligne - 1] = tab_bomb[colonne + 1][ligne - 1] + '0';
            }
            if (colonne > 0 && ligne < 4) {
                tab_user[colonne - 1][ligne + 1] = tab_bomb[colonne - 1][ligne + 1] + '0';
            }
        }
        //------------------------------------------------------------------------------------
        else if (tab_user[colonne][ligne] == 'X') {
            if (tab_bomb[colonne][ligne] != 9) { //Si pas de bombe
                tab_user[colonne][ligne] = tab_bomb[colonne][ligne] + '0';
            }
            else if (tab_bomb[colonne][ligne] == 9) { //Si bombe touché
                tab_user[colonne][ligne] = 'b';
            }
        }

        else if (colonne > 4 || ligne > 4) { //Si mauvais chiffre rentré
            printf("Rentrez des chiffres entre 1 et 5\n");
        }
        else if (tab_user[colonne][ligne] != 'X') { //Si mauvais chiffre rentré
            printf("\nVous ne pouvez pas jouer sur cette case !\n");
        }
        

        //Si perdu stop le jeu
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (tab_user[i][j] == 'b') {
                    printf("\nPERDU\n"); 
                    //Tracer tableau en révélant les bombes
                    for (i = 0; i < 5; i++) {
                        printf("  %d", i + 1);
                    }
                    for (i = 0; i < 5; i++) {
                        printf("\n");
                        printf("%d", i + 1);

                        for (j = 0; j < 5; j++) {
                            if (tab_bomb[i][j] == 9) {
                                printf("[b]");
                            }
                            else {
                                printf("[%c]", tab_user[i][j]);
                            }
                        }
                    }
                    printf("\n\nVoulez-vous rejouer ? 1:Oui 0:Non :  ");
                    scanf_s("%d", &condition);
                    while (condition != 1 && condition != 0) {
                        printf("\nReponse non valide.\nVoulez-vous rejouer ? 1:Oui 0:Non :  ");
                        scanf_s("%d", &condition);
                    }
                }
            }
        }
    } while (condition);
}
