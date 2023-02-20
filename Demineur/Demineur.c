#include <stdio.h>


int main()
{
    int tableau[4][4] = {
       {0, 0, 0, 0} ,
       {0, 0, 0, 0} ,
       {0, 0, 0, 0}
    };
    int i, j;

    for (i = 0; i < 4 ; i++) {
        printf("\n");
        for (j = 0; j < 4; j++) {
            printf("[%d]", tableau[i][j]);
        }
    }
        
}