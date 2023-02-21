#include <stdio.h>


int main()
{
    int tableau[5][5] = {
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0} ,
       {0, 0, 0, 0, 0}
    };
    int i, j;

    for (i = 0; i < 5; i++) {
        printf("  %d", i+1);
    }
    for (i = 0; i < 5; i++) {
        printf("\n");
        printf("%d", i + 1);

        for (j = 0; j < 5; j++) {
            if (tableau[i][j] == 0) {
                printf("[ ]");
            }
            else {
                printf("[%d]", tableau[i][j]);
            }
        }
    }

}