#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ligne 2
#define colonne 6

void affichePlateau(int **plateau){
    for(int i = 0; i < ligne; i++){
        for (int j = 0; j < colonne; j++)
        {
            printf("%d", plateau[i][j]);
        }
        printf("\n");
    }
}
    
 

int main(void){
    int **plateau = (int**) malloc(ligne * sizeof(int*));
    for(int i = 0; i < ligne; i++){
        plateau[i] = (int*) malloc(colonne * sizeof(int));
        for (int j = 0; j < colonne; j++)
        {
            plateau[i][j] = 4;
        }
    }
    affichePlateau(plateau);


     
}