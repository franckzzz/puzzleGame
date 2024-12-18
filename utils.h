//TRABALHO 2 ALGORITMOS
//ACADÊMICOS: MATEUS ARTUR FRANCK - GUILHERME HENRIQUE VIAPIANA SMANIOTO
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//Definição de padrões
#define CLEAR "\033[H\033[2J"
#define RESET "\033[0m"

// Configuração para teclas
#define KEY_ENTER 10
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68

//Definição das coordenadas do quadro
#define BOARD_X 7
#define BOARD_Y 5

//Definição do tipo quadro
typedef struct{
    int x; //tamanho x
    int y; //tamaho y
    int curSqx; //coordenada x do quadrado atual
    int curSqy; //coordenada y do quadrado atual
    int **data; //dados da matriz
} Board;

void clrscr();

void gotoxy(int x, int y);

void window(Board board);

char getMove();

void exibir_cabecalho(const char *titulo);

void print_board(Board board);

void goToCurrentSquare(Board board);

void deleteCurrentSquare(Board board);

int randomNumber(int x);

void swap(int *x, int *y);

int moveTile(Board *board, int move);

void shuffleBoard(int x, Board *board);

int solvedBoard(Board board);





