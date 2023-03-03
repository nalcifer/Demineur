#include <stdio.h>
#include <stdlib.h>
#include <time.h> //???

int row = 0; //???
void drawTabUser(char** tab_user);
int askBoolNumber(const char* message);
void getUserChoice(int* line, int* column, char** tab_user);
int bombInit(int line, int column, char** tab_user, int** tab_bomb, int bomb_number);
void revealCases(int line, int column, char** tab_user, int** tab_bomb);
int isGameOver(int** tab_bomb, char** tab_user, int condition);

int main() {
    srand(time(NULL));

    
    int i, j;
    int condition = 1;
    int bomb_number = 0;
    int first_attempt = 0; //???
   
    //--------------------------------------------- Choix taille tableau
    printf("Entrez la taille du tableaux : \n");
    if (scanf_s("%d", &row) != 1)
    {
        printf("Reponse invalide.\n");
    }

    char** tab_user = (char**)malloc(sizeof(char*) * row);
    if (tab_user == NULL)
        return 1;

    for (i = 0; i < row; ++i)
    {
        tab_user[i] = (char*)malloc(sizeof(char) * row);
        if (tab_user[i] == NULL)
            return 1;

        for (j = 0; j < row; ++j)
        {
            tab_user[i][j] = 'X';
        }
    }

    int** tab_bomb = malloc(sizeof(int*) * row);
    for (i = 0; i < row; ++i)
    {
        tab_bomb[i] = (int*)malloc(sizeof(int) * row);

        for (int j = 0; j < row; ++j)
        {
            tab_bomb[i][j] = 0;
        }
    }

    //---------------------------------------------

    do {
        system("CLS");
        //Afficher le tableau
        drawTabUser(tab_user);

        //----------------------------- Afficher tab_bomb
        /*int i, j;
        printf(" \n\n");
        for (i = 0; i < row; i++) {
            printf("  %d", i + 1);
        }
        for (i = 0; i < row; i++) {
            printf("\n");
            printf("%d", i + 1);

            for (j = 0; j < row; j++) {
                printf("[%d]", tab_bomb[i][j]);
            }
        }*/
        //----------------------------- 
        
        //Input user choix de case
        int line = -1;
        int column = -1;
        
        //1er coup et Initialisation du tableau bombe
        first_attempt = 0;
        for (i = 0; i < row; i++) {
            for (j = 0; j < row; j++) {
                if (tab_user[i][j] == 'X') {
                    first_attempt++;
                }
            }
        }
        if (first_attempt == row*row) {
            getUserChoice(&line, &column, tab_user);
            bomb_number = bombInit(line, column, tab_user, tab_bomb, bomb_number);
        }
        else {
            //Drapeaux
            int flag;
            flag = askBoolNumber("Voulez-vous poser un drapeau ? 1:Oui 0:Non :  ");
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
        for (i = 0; i < row; i++) {
            for (j = 0; j < row; j++) {
                if (tab_user[i][j] == 'b') {
                    printf("\nPERDU\n");
                    condition = isGameOver(tab_bomb, tab_user, condition);
                }

                if (tab_user[i][j] != 'X' && tab_user[i][j] != 'D') {
                    win++;
                }
                if (win == row * row - bomb_number) {
                    printf("\nBravo ! Vous avez reussi.\n");
                    condition = isGameOver(tab_bomb, tab_user, condition);
                }
            }
        } 
    } while (condition);
}


void drawTabUser(char** tab_user) {
    //Tracer le tableau
    int i, j;

    printf(" ");
    for (i = 0; i < row; i++) {
        if (i >= 9) 
        {
            printf(" %d", i + 1);
        }
        else 
        {
            printf("  %d", i + 1);
        }
    }
    for (i = 0; i < row; i++) {
        printf("\n");
        printf("%2d", i + 1);

        for (j = 0; j < row; j++) {
            printf("[%c]", tab_user[i][j]);
        }
    }
}

int askBoolNumber(const char* message) {
    int result;
    printf("\n\n%s", message);
    scanf_s("%d", &result);
    while (getchar() != '\n');
    while (result != 0 && result != 1 ) {
        printf("\nReponse non valide.\n%s", message);
        scanf_s("%d", &result);
        while (getchar() != '\n');
    }
    return result;
}


void getUserChoice (int *line, int *column, char** tab_user) {
    while (*line > row - 1 || *column > row - 1 || *line < 0 || *column < 0 || tab_user[*line][*column] != 'X' && tab_user[*line][*column] != 'D') {
        printf("\nSur quelle case voulez-vous jouer ?\nRentrez les coordonees : ");
        scanf_s("%d.%d", line, column);
        while (getchar() != '\n');
        (*line)--;
        (*column)--;
        if (*line > row - 1 || *column > row - 1 || *line < 0 || *column < 0) {
            printf("Rentrez des chiffres entre 1 et %d. (ligne.colonne)\n", row);
        }
        else if (tab_user[*line][*column] != 'X' && tab_user[*line][*column] != 'D') { //Si mauvais chiffre rentre
            printf("\nVous ne pouvez pas jouer sur cette case !\n");
        }
    }
}

int bombInit (int line, int column, char** tab_user, int** tab_bomb, int bomb_number){
    int i, j;
    tab_user[line][column] = '0';
    //Pour ne pas mettre de bombes autour du 1er coup
    if (line < row - 1) {
        tab_user[line + 1][column] = '0';
    }
    if (column < row - 1) {
        tab_user[line][column + 1] = '0';
    }
    if (line < row - 1 && column < row - 1) {
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
    if (line < row - 1 && column > 0) {
        tab_user[line + 1][column - 1] = '0';
    }
    if (line > 0 && column < row - 1) {
        tab_user[line - 1][column + 1] = '0';
    }
    //Initialisation du tableau bombe
    bomb_number = 0;
    while (bomb_number < row) { //Aleatoire de la position des bombes
        i = rand() % row;
        j = rand() % row;
        if (tab_bomb[i][j] == 0 && tab_user[i][j] == 'X') {
            tab_bomb[i][j] = 9;
            bomb_number++;
        }
    }
    //Indices
    for (i = 0; i < row; i++) {
        for (j = 0; j < row; j++) {
            if (tab_bomb[i][j] != 9) {
                if (i < row - 1) {
                    if (tab_bomb[i + 1][j] == 9) {
                        tab_bomb[i][j]++;
                    }
                }
                if (j < row - 1) {
                    if (tab_bomb[i][j + 1] == 9) {
                        tab_bomb[i][j]++;
                    }
                }
                if (i < row - 1 && j < row - 1) {
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
                if (i < row - 1 && j > 0) {
                    if (tab_bomb[i + 1][j - 1] == 9) {
                        tab_bomb[i][j]++;
                    }
                }
                if (i > 0 && j < row - 1) {
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
    if (line < row - 1) {
        tab_user[line + 1][column] = tab_bomb[line + 1][column] + '0';
    }
    if (column < row - 1) {
        tab_user[line][column + 1] = tab_bomb[line][column + 1] + '0';
    }
    if (line < row - 1 && column < row - 1) {
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
    if (line < row - 1 && column > 0) {
        tab_user[line + 1][column - 1] = tab_bomb[line + 1][column - 1] + '0';
    }
    if (line > 0 && column < row - 1) {
        tab_user[line - 1][column + 1] = tab_bomb[line - 1][column + 1] + '0';
    }
    return bomb_number;
}

void revealCases(int line, int column, char** tab_user, int** tab_bomb) {

    if (tab_user[line][column] != 'X' && tab_user[line][column] != '0')
        return;

    tab_user[line][column] = tab_bomb[line][column] + '0';

    if (tab_user[line][column] == '0') {
        tab_user[line][column] = ' ';
        
        if (line < row - 1) {
            revealCases(line+1, column, tab_user, tab_bomb);
        }
        if (column < row - 1) {
            revealCases(line, column + 1, tab_user, tab_bomb);
        }
        if (line < row - 1 && column < row - 1) {
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
        if (line < row - 1 && column > 0) {
            revealCases(line + 1, column - 1, tab_user, tab_bomb);
        }
        if (line > 0 && column < row - 1) {
            revealCases(line - 1, column + 1, tab_user, tab_bomb);
        }
    }
}

int isGameOver (int** tab_bomb, char** tab_user, int condition) {
    int i, j;
    //Tracer tableau en revelant les bombes
    for (i = 0; i < row; i++) {
        printf("  %d", i + 1);
    }
    for (i = 0; i < row; i++) {
        printf("\n");
        printf("%d", i + 1);

        for (j = 0; j < row; j++) {
            if (tab_bomb[i][j] == 9) {
                printf("[b]");
            }
            else {
                printf("[%c]", tab_user[i][j]);
            }
        }
    }
    //Rejouer
    condition = askBoolNumber("Voulez - vous rejouer ? 1 : Oui 0 : Non : ");
    free(malloc);
    //Remettre les tableaux a 0
    for (i = 0; i < row; i++) {
        for (j = 0; j < row; j++) {
            tab_bomb[i][j] = 0;
            tab_user[i][j] = 'X';
        }
    }
    return condition;
}
