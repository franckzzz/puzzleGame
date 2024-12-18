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

//Função para limpar a tela
void clrscr(){
    
    printf(CLEAR);
    
}

//Função para ir a uma coordenada
void gotoxy(int x, int y){
    
    printf("\e[%d;%df", y, x);
    fflush(stdout);
    
}

//Função para criar uma janela
void window(Board board){
    int flag;
    
    if(board.x*board.y <= 9){
        board.x = BOARD_X + 3*board.x + 1;
        flag = 0;
    } else if(board.x*board.y <= 99){
        board.x = BOARD_X + 4*board.x + 1;
        flag = 1;
    } else {
        board.x = BOARD_X + 5*board.x + 1;
        flag = 2;
    }
    board.y = BOARD_Y + board.y + 1;
    
    gotoxy(BOARD_X,BOARD_Y);
    printf("\033[97;105;1m");   
    printf("+");
    
    for(int i=BOARD_X+1; i<board.x; i++){
        printf("-");
        
    }
    
    printf("+");
    
    gotoxy(BOARD_X,board.y);
    printf("+");
    
    for(int i=BOARD_X+1; i<board.x; i++){
        printf("-");
        
    }
    
    printf("+");
    
    
    for(int i=1; i<(board.y-BOARD_Y); i++){
        gotoxy(BOARD_X, BOARD_Y+i);
        printf("|");
    }
    
    for(int i=1; i<board.y-BOARD_Y; i++){
        gotoxy(board.x, BOARD_Y+i);
        printf("|");
    }
    
   
    gotoxy(board.x-1, board.y-1);
    printf("\033[0;0;0m");
}

//Função para detectar o caractere inserido
char getMove(){
    
    int ch;
    struct termios oldt;
    struct termios newt;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    if (ch == '\033') { // Tecla especial (setas)
        getchar();  
        return getchar();
      } else if (ch == KEY_ENTER) {
         return 1;
      } else {
          return 0;
      }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}

//Função para exibir o cabeçalho
void exibir_cabecalho(const char *titulo) {
   printf("\033[H\033[J"); // Limpa a tela
   printf("\033[97;105;1m"); // Estilo do cabeçalho
   printf(" %s ", titulo);
   printf(RESET "\n\n"); // Reseta estilos após o cabeçalho
}

//Função para exibir o quadro com janela
void print_board(Board board){
    int flag = 0;
    if(board.x*board.y <= 9){
        flag = 0;
    } else if(board.x*board.y <= 99){
        flag = 1;
    } else {
        flag = 2;
    }
    window(board);
    printf("\033[97;105;1m");
    for (int i = 0; i < board.y; i++) {
            gotoxy(BOARD_X+1, BOARD_Y+1+i);
        for (int j = 0; j < board.x; j++) {
            switch(flag){
                case 0:
                    printf(" %d ", board.data[i][j]);
                    break;
                case 1:
                    printf(" %2d ", board.data[i][j]);
                    break;
                case 2:
                    printf(" %3d ", board.data[i][j]);
                    break;
            }
    
        }
        printf("\n");
    }
    deleteCurrentSquare(board);
    gotoxy(1, BOARD_Y+board.y+3);

    printf(RESET);
}

//Função para ir ao quadrado atual
void goToCurrentSquare(Board board){
     if(board.x*board.y <= 9){
        gotoxy(BOARD_X+(3*board.curSqx)-1, BOARD_Y+board.curSqy);
    } else if(board.x*board.y <= 99){
        gotoxy(BOARD_X+(4*board.curSqx)-2, BOARD_Y+board.curSqy);
    } else {
        gotoxy(BOARD_X+(5*board.curSqx)-3, BOARD_Y+board.curSqy);
    }
    
}
//Função para apagar o quadrado atual
void deleteCurrentSquare(Board board){
    goToCurrentSquare(board);
    printf("\033[97;105;1m");
    if(board.x*board.y <= 99){
        printf("  ");
    } else{
        printf("   ");
    }
    printf(RESET);
}

//Função para gerar número aleatório
int randomNumber(int x){
    int r = rand() % x;
    return r;
}

//Função para trocar 2 valores
void swap(int *x, int *y){
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

//Função para mexer os quadrados no quadro
int moveTile(Board *b, int move){
    int i = b->curSqy - 1;
    int j = b->curSqx - 1;
    switch(move){
        case 0:
            return 0;
            break;
        case 1:
            return -1;
            break;
    }   
    switch(move){
        case KEY_DOWN:
            if(i > 0){
                swap(&b->data[i][j], &b->data[i-1][j]);
                b->curSqy--;
            }
            return 1;
            break;
        case KEY_UP:
            if(i < b->y-1){
                swap(&b->data[i][j], &b->data[i+1][j]);
                b->curSqy++;
            }
            return 1;
            break;
        case KEY_RIGHT:
            if(j > 0){
                swap(&b->data[i][j], &b->data[i][j-1]);
                b->curSqx--;
            }
            return 1;
            break;
        case KEY_LEFT:
            if(j < b->x-1){
                swap(&b->data[i][j], &b->data[i][j+1]);
                b->curSqx++;
            }
            return 1;
            break;
        
    }
    return 0;
    
}

//Função para bagunçar o quadro
void shuffleBoard(int x, Board *board){
    int iter = 0;
    while(iter < x){
        int j = randomNumber(4);
        switch(j){
            case 0:
                moveTile(board, KEY_DOWN);
                break;
            case 1:
                moveTile(board, KEY_UP);
                  break;
            case 2:
                moveTile(board, KEY_LEFT);
                break;
            case 3:
                moveTile(board, KEY_RIGHT);
                break;
        }
        iter++;
    }
}

//Função para checar se o quadro está resolvido
int solvedBoard(Board board){
    int flag = 0;
    for (int i = 0; i < board.y; i++) {
        for (int j = 0; j < board.x; j++) {
            if(!(i == board.y-1 && j == board.x-1)){
                if(board.data[i][j] == (j + 1) + (board.x*i)){
                    flag++;
                }
            }
        }
    }
    if(flag == board.x*board.y-1){
        return 1;
    } else{
        return 0;
    }
}




