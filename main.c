//TRABALHO 2 ALGORITMOS
//ACADÊMICOS: MATEUS ARTUR FRANCK - GUILHERME HENRIQUE VIAPIANA SMANIOTO
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "utils.h"


int main() {
    //Definir um título padrão
    const char *titulo1 = "Bem vindo ao 8 Puzzle!";
    
    exibir_cabecalho(titulo1);
    
    //Declarar o quadro e seus valores
    int x, y;
    Board board;
    
    printf("Digite as dimensões do tabuleiro: ");
    scanf("%d %d", &x, &y);
    getchar();
    
    //Alocar a matriz do quadro
    board.data = (int **)malloc(y*sizeof(int *));
    if (board.data == NULL) {
        return 1;
    }

    for (int i = 0; i < y; i++) {
        board.data[i] = (int *)malloc(x*sizeof(int));
        if (board.data[i] == NULL) {
            return 1;
        }
    }
    
    //Dar os valores para a matriz
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if(!(i == y-1 && j == x-1)){
                board.data[i][j] = (j + 1) + (x*i);
            }
        }
    }
    
    //Atribuir os valores da estrutura Board
    board.x = x;
    board.y = y;
    board.curSqx = x;
    board.curSqy = y;
    
    //Definir uma seed aleatória
    srand(time(NULL));
    
    //Bagunçar o quadro e limpar a tela;
    shuffleBoard(100, &board);
    clrscr();
    
    //Declarar a variável que conta as jogadas
    int count = 0;
    
    //Declarar a varoável do resultado
    int result;
    
    //Repete os comandos até o quadro estar resolvido
    while(!(solvedBoard(board))){
        gotoxy(1,1);
        printf("\033[97;105;1m");
        printf(" %s ", titulo1);
        printf(RESET);
        print_board(board);
        printf("Movimentos: Setas ← ↓ → ↑\n");
        printf("Para sair do jogo, pressione [ENTER]\n");
        printf("Digite o movimento: ");
        int move = getMove();
        result = moveTile(&board, move);
        if(result == 0){
            printf("     Movimento Inválido! Tente outro.");
        } else if (result == -1){
            break;
        } else{
            count++;
            clrscr();
        }
    }
    
    //Checa se o loop foi quebrado por resolução ou por desistência
    if(result == -1){
        exibir_cabecalho("Desistência :(");
        print_board(board);
        gotoxy(1, BOARD_Y+board.y+3);
        printf("Você desistiu do jogo.\nNúmero de jogadas: %d", count);
    } else{
        exibir_cabecalho("Vitória :)");
        print_board(board);
        gotoxy(1, BOARD_Y+board.y+3);
        printf("Parabéns! Você ganhou o jogo!\nNúmero de jogadas: %d", count);
    }
    
    //Desaloca a matriz do quadro
    for (int i = 0; i < y; i++) {
        free(board.data[i]);
    }
    free(board.data);
    
    return 0;
}