#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define CLEAR "\033[H\033[2J"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define REVERSE "\033[7m"
#define FG_WHITE "\033[37m"
#define BG_BLUE "\033[44m"

// Configuração para teclas
#define KEY_ENTER 10
#define KEY_ESC 27
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68

// Comprimento máximo de uma linha do menu
#define MENU_WIDTH 10

void clrscr();

void gotoxy(int x, int y);

void window(int x1, int y1, int x2, int y2);

char getch();

int keypress();

void configurar_terminal(struct termios *old);

void restaurar_terminal(struct termios *old);

void exibir_cabecalho(const char *titulo);

void formatar_opcao(const char *opcao, char *saida, int largura);

int mostrar_menu_interativo(const char *opcoes[], int n, const char *titulo);

void print_board(int x1, int y1, int x2, int y2, int **matriz);

int randomNumber(int x);

void shuffleBoard(int **matriz);


