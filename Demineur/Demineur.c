#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void drawTabUser(char tab_user[SIZE][SIZE]);
void getUserChoice(int* line, int* column, char tab_user[SIZE][SIZE]);
int bombInit(int line, int column, char tab_user[SIZE][SIZE], int tab_bomb[SIZE][SIZE], int bomb_number);
void revealCases(int line, int column, char tab_user[SIZE][SIZE], int tab_bomb[SIZE][SIZE]);
int isGameOver(int tab_bomb[SIZE][SIZE], char tab_user[SIZE][SIZE], int condition);

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
    int bomb_number = 0;
    int first_attempt;
   

    do {
        system("CLS");
        //Afficher le tableau
        drawTabUser(tab_user);

        //----------------------------- Afficher tab_bomb
        int i, j;
        printf(" \n\n");
        for (i = 0; i < SIZE; i++) {
            printf("  %d", i + 1);
        }
        for (i = 0; i < SIZE; i++) {
            printf("\n");
            printf("%d", i + 1);

            for (j = 0; j < SIZE; j++) {
                printf("[%d]", tab_bomb[i][j]);
            }
        }
        //----------------------------- 
        
        //Input user choix de case
        int line = -1;
        int column = -1;
        
        //1er coup et Initialisation du tableau bombe
        first_attempt = 0;
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                if (tab_user[i][j] == 'X') {
                    first_attempt++;
                }
            }
        }
        if (first_attempt == SIZE*SIZE) {
            getUserChoice(&line, &column, tab_user);
            bomb_number = bombInit(line, column, tab_user, tab_bomb, bomb_number);
        }
        else {
            //Drapeaux
            int flag;
            printf("\n\nVoulez-vous poser un drapeau ? 1:Oui 0:Non :  ");
            scanf_s("%d", &flag);
            while (getchar() != '\n');
            while (flag != 1 && flag != 0) {
                printf("\nReponse non valide.\nVoulez-vous poser un drapeau ? 1:Oui 0:Non :  ");
                scanf_s("%d", &flag);
                while (getchar() != '\n');
            }
            if (flag == 1) {
                getUserChoice(&line, &column, tab_user);
                if (tab_user[line][column] == 'X') {
                    tab_user[line][column] = 'D';
                }
            }
            else if (flag == 0) {
                getUserChoice(&line, &column, tab_user);
                if (tab_user[line][column] == 'X' || tab_user[line][column] == 'D') {
                    if (tab_bomb[line][column] != 9) { //Si pas de bombe
                        tab_user[line][column] = tab_bomb[line][column] + '0';
                    }
                    else if (tab_bomb[line][column] == 9) { //Si bombe touche
                        tab_user[line][column] = 'b';
                    }
                }
            }
        }
        //Changer les cases 0 en ' ' et afficher les cases autours
        revealCases(line, column, tab_user, tab_bomb);


        //Si perdu stop le jeu
        int win = 0;
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                if (tab_user[i][j] == 'b') {
                    printf("\nPERDU\n");
                    condition = isGameOver(tab_bomb, tab_user, condition);
                }

                if (tab_user[i][j] != 'X' && tab_user[i][j] != 'D') {
                    win++;
                }
                if (win == SIZE * SIZE - bomb_number) {
                    printf("\nBravo ! Vous avez reussi.\n");
                    condition = isGameOver(tab_bomb, tab_user, condition);
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

/*int askNumber(int min, int max, const char* message) {

    while ( ) {
        printf("%s", message);
        scanf_s("%d", &result);
        while (getchar() != '\n');
    }
    return result;
}
*/

void getUserChoice (int *line, int *column, char tab_user[SIZE][SIZE]) {
    while (*line > SIZE - 1 || *column > SIZE - 1 || *line < 0 || *column < 0 || tab_user[*line][*column] != 'X' && tab_user[*line][*column] != 'D') {
        printf("\nSur quelle case voulez-vous jouer ?\nRentrez les coordonees : ");
        scanf_s("%d.%d", line, column);
        while (getchar() != '\n');
        (*line)--;
        (*column)--;
        if (*line > SIZE - 1 || *column > SIZE - 1 || *line < 0 || *column < 0) {
            printf("Rentrez des chiffres entre 1 et %d. (ligne.colonne)\n", SIZE);
        }
        else if (tab_user[*line][*column] != 'X' && tab_user[*line][*column] != 'D') { //Si mauvais chiffre rentre
            printf("\nVous ne pouvez pas jouer sur cette case !\n");
        }
    }
}

int bombInit (int line, int column, char tab_user[SIZE][SIZE], int tab_bomb[SIZE][SIZE], int bomb_number){
    int i, j;
    tab_user[line][column] = '0';
    //Pour ne pas mettre de bombes autour du 1er coup
    if (line < SIZE - 1) {
        tab_user[line + 1][column] = '0';
    }
    if (column < SIZE - 1) {
        tab_user[line][column + 1] = '0';
    }
    if (line < SIZE - 1 && column < SIZE - 1) {
        tab_user[line + 1][column + 1] = '0';
    }
    if (line > 0) {
        tab_user[line - 1][column] = '0';
    }
    if (column > 0) {
        tab_user[line][column - 1] = '0';
    }
    if (line > 0 && column > 0) {
        tab_user[line - 1][column - 1] = '0';
    }
    if (line < SIZE - 1 && column > 0) {
        tab_user[line + 1][column - 1] = '0';
    }
    if (line > 0 && column < SIZE - 1) {
        tab_user[line - 1][column + 1] = '0';
    }
    //Initialisation du tableau bombe
    bomb_number = 0;
    while (bomb_number < SIZE) { //Aleatoire de la position des bombes
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
    if (tab_bomb[line][column] == 9) {
        tab_user[line][column] = ' ';
    }
    if (line < SIZE - 1) {
        tab_user[line + 1][column] = tab_bomb[line + 1][column] + '0';
    }
    if (column < SIZE - 1) {
        tab_user[line][column + 1] = tab_bomb[line][column + 1] + '0';
    }
    if (line < SIZE - 1 && column < SIZE - 1) {
        tab_user[line + 1][column + 1] = tab_bomb[line + 1][column + 1] + '0';
    }
    if (line > 0) {
        tab_user[line - 1][column] = tab_bomb[line - 1][column] + '0';
    }
    if (column > 0) {
        tab_user[line][column - 1] = tab_bomb[line][column - 1] + '0';
    }
    if (line > 0 && column > 0) {
        tab_user[line - 1][column - 1] = tab_bomb[line - 1][column - 1] + '0';
    }
    if (line < SIZE - 1 && column > 0) {
        tab_user[line + 1][column - 1] = tab_bomb[line + 1][column - 1] + '0';
    }
    if (line > 0 && column < SIZE - 1) {
        tab_user[line - 1][column + 1] = tab_bomb[line - 1][column + 1] + '0';
    }
    return bomb_number;
}

void revealCases(int line, int column, char tab_user[SIZE][SIZE], int tab_bomb[SIZE][SIZE]) {

    if (tab_user[line][column] != 'X' && tab_user[line][column] != '0')
        return;

    tab_user[line][column] = tab_bomb[line][column] + '0';

    if (tab_user[line][column] == '0') {
        tab_user[line][column] = ' ';
        
        if (line < SIZE - 1) {
            revealCases(line+1, column, tab_user, tab_bomb);
        }
        if (column < SIZE - 1) {
            revealCases(line, column + 1, tab_user, tab_bomb);
        }
        if (line < SIZE - 1 && column < SIZE - 1) {
            revealCases(line + 1, column + 1, tab_user, tab_bomb);
        }
        if (line > 0) {
            revealCases(line - 1, column, tab_user, tab_bomb);
        }
        if (column > 0) {
            revealCases(line, column - 1, tab_user, tab_bomb);
        }
        if (line > 0 && column > 0) {
            revealCases(line - 1, column - 1, tab_user, tab_bomb);
        }
        if (line < SIZE - 1 && column > 0) {
            revealCases(line + 1, column - 1, tab_user, tab_bomb);
        }
        if (line > 0 && column < SIZE - 1) {
            revealCases(line - 1, column + 1, tab_user, tab_bomb);
        }
    }
}

int isGameOver (int tab_bomb[SIZE][SIZE], char tab_user[SIZE][SIZE], int condition) {
    int i, j;
    //Tracer tableau en revelant les bombes
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
    while (getchar() != '\n');
    while (condition != 1 && condition != 0) {
        printf("\nReponse non valide.\nVoulez-vous rejouer ? 1:Oui 0:Non :  ");
        scanf_s("%d", &condition);
        while (getchar() != '\n');
    }
    //Remettre les tableaux a 0
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            tab_bomb[i][j] = 0;
            tab_user[i][j] = 'X';
        }
    }
    return condition;
}
