#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int row = 0;
// initialisation fonctions secondaires
void drawTabUser(char** tab_user);
void drawTabBomb(int** tab_bomb);
int askOneNumber(int min, int max, const char* message);
char** createCharTab(int row, char filling);
int** createIntTab(int row, int filling);
void getCoordinatesChoice(int* line, int* column, char** tab_user);
void removeTabValue(int** tab, int indice, int* size);
int initBomb(int line, int column, char** tab_user, int** tab_bomb, int bomb_number);
void revealSafeBoxes(int line, int column, char** tab_user, int** tab_bomb);
int isGameOver(int** tab_bomb, char** tab_user, int condition);

int main() {
    system("COLOR 5"); // changement couleur console
    // initialisation variables
    int condition = 1;
    int first_attempt = 1;
    int i, j;
    char** tab_user = NULL;
    int** tab_bomb = NULL;
    int bomb_number = 0;
    int win_counter = 0;
    int defeats_counter = 0;

    do {
        system("CLS");
        if (first_attempt == 1) {
            // demande au joueur taille tableau
            row = askOneNumber(3, 50, "Entrez la taille du tableau (entre 3 et 50): ");
            if (row == 26) {
                system("COLOR D7");
            }
            tab_user = createCharTab(row, 'X');
            tab_bomb = createIntTab(row, 0);
            // choix nombre de bombes
            int bomb_choice = askOneNumber(0, 1, "Voulez-vous choisir le nombre de bombes? 1:OUI 0:NON : ");
            if (bomb_choice == 1) {
                bomb_number = askOneNumber(1, row * row - 1, "Entrez le nombre de bombes : ");
            }
            else {
                bomb_number = row;
            }
        }
        drawTabUser(tab_user);
        /*drawTabBomb(tab_bomb);*/

        int line = -1;
        int column = -1;
        if (first_attempt == 1) { // 1er coup
            getCoordinatesChoice(&line, &column, tab_user);
            initBomb(line, column, tab_user, tab_bomb, bomb_number);
            first_attempt = 0;
        }
        else {
            int flag;
            flag = askOneNumber(0, 1, "\n\nVoulez-vous poser un drapeau ? 1:Oui 0:Non :  ");
            // jouer un drapeau
            if (flag == 1) {
                getCoordinatesChoice(&line, &column, tab_user);
                if (tab_user[line][column] == 'X') {
                    tab_user[line][column] = 'D';
                }
            }
            // jouer
            else if (flag == 0) {
                getCoordinatesChoice(&line, &column, tab_user);
                if (tab_user[line][column] == 'X' || tab_user[line][column] == 'D') {
                    if (tab_bomb[line][column] != 9) { // si pas de bombe
                        tab_user[line][column] = tab_bomb[line][column] + '0';
                    }
                    else if (tab_bomb[line][column] == 9) { // si bombe touche
                        tab_user[line][column] = 'b';
                    }
                }
            }
        }
        // changement cases 0 en [ ] et affichage cases indices autour
        revealSafeBoxes(line, column, tab_user, tab_bomb);

        // fin manche
        int win = 0;
        int defeat = 0;
        for (i = 0; i < row; i++) {
            for (j = 0; j < row; j++) {
                // defaite
                if (tab_user[i][j] == 'b') {
                    printf("\nPERDU\n");
                    defeat = 1;
                    defeats_counter++;
                    first_attempt = 1;
                }
                else if (tab_user[i][j] != 'X' && tab_user[i][j] != 'D') {
                    win++;
                }
            }
        }
        // victoire
        if (win == row * row - bomb_number) {
            printf("\nBravo ! Vous avez reussi.\n");
            win_counter++;
            first_attempt = 1;
        }
        // fin de manche
        if (defeat == 1 || win == row * row - bomb_number) {
            printf("\nVictoire(s) : %d     Defaite(s) : %d\n", win_counter, defeats_counter);
            condition = isGameOver(tab_bomb, tab_user, condition);
            free(tab_bomb);
            free(tab_user);
        }

    } while (condition);

    return 0;
}


void drawTabUser(char** tab_user) {
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

void drawTabBomb(int** tab_bomb) {
    int i, j;
    printf("\n\n ");
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
            printf("[%d]", tab_bomb[i][j]);
        }
    }
}

int askOneNumber(int min, int max, const char* message) {
    int result;
    printf("%s", message);
    scanf_s("%d", &result);
    while (getchar() != '\n');
    while (result < min || result > max) {
        printf("\nReponse non valide.\n%s", message);
        scanf_s("%d", &result);
        while (getchar() != '\n');
    }
    return result;
}

char** createCharTab(int row, char filling) {
    int i, j;
    char** table = (char**)malloc(sizeof(char*) * row);
    if (table == NULL)
        return 1;
    for (i = 0; i < row; ++i)
    {
        table[i] = (char*)malloc(sizeof(char) * row);
        if (table[i] == NULL)
            return 1;
        for (j = 0; j < row; ++j)
        {
            table[i][j] = filling;
        }
    }
    return table;
}


int** createIntTab(int row, int filling) {
    int i, j;
    int** table = (int*)malloc(sizeof(int*) * row);
    if (table == NULL)
        return 1;
    for (i = 0; i < row; ++i)
    {
        table[i] = (int*)malloc(sizeof(int) * row);
        if (table[i] == NULL)
            return 1;
        for (j = 0; j < row; ++j)
        {
            table[i][j] = filling;
        }
    }
    return table;
}

void removeTabValue(int** tab, int indice, int* size) {
    int newSize = *size - 1;

    for (int i = indice; i < newSize; i++) {
        tab[i] = tab[i + 1];
    }

    *size = newSize;
}

void getCoordinatesChoice(int* line, int* column, char** tab_user) {
    while (*line > row - 1 || *column > row - 1 || *line < 0 || *column < 0 || tab_user[*line][*column] != 'X' && tab_user[*line][*column] != 'D') {
        printf("\nSur quelle case voulez-vous jouer ?\nRentrez les coordonees : ");
        scanf_s("%d.%d", line, column);
        while (getchar() != '\n');
        (*line)--;
        (*column)--;
        if (*line > row - 1 || *column > row - 1 || *line < 0 || *column < 0) { // si mauvais chiffre
            printf("Rentrez des chiffres entre 1 et %d. (ligne.colonne)\n", row);
        }
        else if (tab_user[*line][*column] != 'X' && tab_user[*line][*column] != 'D') { // si positions pas libre
            printf("\nVous ne pouvez pas jouer sur cette case !\n");
        }
    }
}

int initBomb(int line, int column, char** tab_user, int** tab_bomb, int bomb_number) {
    srand(time(NULL));
    int bomb_in_tab = 0;
    int i, j;
    
    int size = row * row;
    int** bomb_possibilities = malloc(size * sizeof(int*));
    for (i = 0; i < row; i++) {
        for (j = 0; j < row; j++) {
            bomb_possibilities[i * row + j] = &tab_bomb[i][j];
        }
    }
    removeTabValue(bomb_possibilities, line * row + column, &size);
    //Pour ne pas mettre de bombes autour du 1er coup
    if (line < row - 1) {
        removeTabValue(bomb_possibilities, (line+1) * row + column, &size);
    }
    if (column < row - 1) {
        removeTabValue(bomb_possibilities, line * row + (column+1), &size);
    }
    if (line < row - 1 && column < row - 1) {
        removeTabValue(bomb_possibilities, (line+1) * row + (column+1), &size);
    }
    if (line > 0) {
        removeTabValue(bomb_possibilities, (line-1) * row + column, &size);
    }
    if (column > 0) {
        removeTabValue(bomb_possibilities, line * row + (column-1), &size);
    }
    if (line > 0 && column > 0) {
        removeTabValue(bomb_possibilities, (line-1) * row + (column-1), &size);
    }
    if (line < row - 1 && column > 0) {
        removeTabValue(bomb_possibilities, (line+1) * row + (column-1), &size);
    }
    if (line > 0 && column < row - 1) {
        removeTabValue(bomb_possibilities, (line-1) * row + (column+1), &size);
    }

    int* ptr;
    while (bomb_in_tab < bomb_number) { //Aleatoire de la position des bombes
        int random = rand() % size;
        ptr = bomb_possibilities[random];
        *ptr = 9;
        removeTabValue(bomb_possibilities, random, &size);
        bomb_in_tab++;
    }
    free(bomb_possibilities);


    //------------------------------------------------------------ Autre moyen de placer les bombes en aléatoire
    /*
    tab_user[line][column] = '0';
    // pour ne pas mettre de bombes autour du 1er coup
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
    // initialisation bombes
    int bomb_in_tab = 0;
    while (bomb_in_tab < bomb_number) { // aleatoire position des bombes
        i = rand() % row;
        j = rand() % row;
        if (tab_bomb[i][j] == 0 && tab_user[i][j] == 'X') {
            tab_bomb[i][j] = 9;
            bomb_in_tab++;
        }
    }*/
    //------------------------------------------------------------ 

    // initialisation indices
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
    return bomb_in_tab;
}

void revealSafeBoxes(int line, int column, char** tab_user, int** tab_bomb) {

    if (tab_user[line][column] != 'X' && tab_user[line][column] != '0')
        return;

    tab_user[line][column] = tab_bomb[line][column] + '0';

    if (tab_user[line][column] == '0') {
        tab_user[line][column] = ' ';

        if (line < row - 1) {
            revealSafeBoxes(line + 1, column, tab_user, tab_bomb);
        }
        if (column < row - 1) {
            revealSafeBoxes(line, column + 1, tab_user, tab_bomb);
        }
        if (line < row - 1 && column < row - 1) {
            revealSafeBoxes(line + 1, column + 1, tab_user, tab_bomb);
        }
        if (line > 0) {
            revealSafeBoxes(line - 1, column, tab_user, tab_bomb);
        }
        if (column > 0) {
            revealSafeBoxes(line, column - 1, tab_user, tab_bomb);
        }
        if (line > 0 && column > 0) {
            revealSafeBoxes(line - 1, column - 1, tab_user, tab_bomb);
        }
        if (line < row - 1 && column > 0) {
            revealSafeBoxes(line + 1, column - 1, tab_user, tab_bomb);
        }
        if (line > 0 && column < row - 1) {
            revealSafeBoxes(line - 1, column + 1, tab_user, tab_bomb);
        }
    }
}

int isGameOver(int** tab_bomb, char** tab_user, int condition) {
    int i, j;
    // tracer tableau en revelant les bombes
    for (i = 0; i < row; i++) {
        for (j = 0; j < row; j++) {
            if (tab_bomb[i][j] == 9) {
                tab_user[i][j] = 'b';
            }
        }
    }
    drawTabUser(tab_user);
    // rejouer
    condition = askOneNumber(0, 1, "\n\nVoulez-vous rejouer ? 1:OUI 0:NON : ");

    return condition;
}
