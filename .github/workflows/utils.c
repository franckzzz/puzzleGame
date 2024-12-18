#include <stdio.h>
#include <string.h>
#include "utils.h"

#define BOARD_X 7
#define BOARD_Y 5

int main() {
    
    const char *titulo1 = "Bem vindo ao 8 Puzzle!";
    
    exibir_cabecalho(titulo1);
    
    int x, y;
    
    printf("Digite as dimensões do tabuleiro: ");
    scanf("%d %d", &x, &y);
    
    int **matriz;
    
    matriz = (int **)malloc(y*sizeof(int *));
    if (matriz == NULL) {
        return 1;
    }

    for (int i = 0; i < y; i++) {
        matriz[i] = (int *)malloc(x*sizeof(int));
        if (matriz[i] == NULL) {
            return 1;
        }
    }
    
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if(!(i == y-1 && j == x-1))
            matriz[i][j] = (j + 1) + (x*i);
        }
    }
    
    window(BOARD_X, BOARD_Y, x, y);
    print_board(BOARD_X, BOARD_Y, x, y, matriz);

    printf(" ");
    
    
    for (int i = 0; i < y; i++) {
        free(matriz[i]);
    }
    free(matriz);
    
    

    return 0;
}
