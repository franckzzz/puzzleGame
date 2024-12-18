#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "utils.h"


void clrscr(){
    
    printf(CLEAR);
    
}

void gotoxy(int x, int y){
    
    printf("\e[%d;%df", y, x);
    fflush(stdout);
    
}

void window(int x1, int y1, int x2, int y2){
    int flag;
    
    if(x2*y2 <= 9){
        x2 = x1 + 2*x2 + 1;
        flag = 0;
    } else if(x2*y2 <= 99){
        x2 = x1 + 3*x2 + 1;
        flag = 1;
    } else {
        x2 = x1 + 4*x2 + 1;
        flag = 2;
    }
    y2 = y1 + y2 + 1;
    
    gotoxy(x1,y1);
    printf("\033[97;105;1m");   
    printf("+");
    
    for(int i=x1+1; i<x2; i++){
        printf("-");
        
    }
    
    printf("+");
    
    gotoxy(x1,y2);
    printf("+");
    
    for(int i=x1+1; i<x2; i++){
        printf("-");
        
    }
    
    printf("+");
    
    
    for(int i=1; i<(y2-y1); i++){
        gotoxy(x1, y1+i);
        printf("|");
    }
    
    for(int i=1; i<y2-y1; i++){
        gotoxy(x2, y1+i);
        printf("|");
    }
    
   
    gotoxy(x2-1, y2-1);
    printf("\033[0;0;0m");
}

char getch(){
    
    int ch;
    struct termios oldt;
    struct termios newt;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}

 int keypress(void){

    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt); 
    newt = oldt; 
    newt.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar(); 
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void configurar_terminal(struct termios *old) {
   struct termios new;
   tcgetattr(STDIN_FILENO, old);
   new = *old;
   new.c_lflag &= ~(ICANON | ECHO);
   tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

void restaurar_terminal(struct termios *old) {
   tcsetattr(STDIN_FILENO, TCSANOW, old);
}

void exibir_cabecalho(const char *titulo) {
   printf("\033[H\033[J"); // Limpa a tela
   printf(BG_BLUE FG_WHITE BOLD); // Estilo do cabeçalho
   printf(" %s ", titulo);
   printf(RESET "\n\n"); // Reseta estilos após o cabeçalho
}

void formatar_opcao(const char *opcao, char *saida, int largura) {
   int len = strlen(opcao);
   int padding = largura - len; // Espaços para completar
   if (padding < 0) padding = 0; // Evita valores negativos
   snprintf(saida, largura + 1, "%s%*s", opcao, padding, ""); // Adiciona espaços ao final
}

int mostrar_menu_interativo(const char *opcoes[], int n, const char *titulo) {
   int selecionado = 0;
   struct termios terminal_original;

   configurar_terminal(&terminal_original);

   while (1) {
      exibir_cabecalho(titulo); // Mostra o cabeçalho

      // Exibe as opções do menu
      for (int i = 0; i < n; i++) {
         char opcao_formatada[MENU_WIDTH + 1];
         formatar_opcao(opcoes[i], opcao_formatada, MENU_WIDTH);

         if (i == selecionado) {
            printf(REVERSE " %s " RESET "\n", opcao_formatada); // Destaca a opção com vídeo reverso
         } else {
            printf(" %s\n", opcao_formatada);
         }
      }

      // Lê a tecla pressionada
      int ch = getchar();
      if (ch == '\033') { // Tecla especial (setas)
         getchar(); // Ignora '['
         switch (getchar()) {
            case KEY_UP:
               if (selecionado > 0) selecionado--;
               break;
            case KEY_DOWN:
               if (selecionado < n - 1) selecionado++;
               break;
         }
      } else if (ch == KEY_ENTER) {
         break; // Sai do loop ao pressionar Enter
      } 
   }
   restaurar_terminal(&terminal_original);
   return selecionado;
}

void print_board(int x1, int y1, int x2, int y2, int **matriz){
    int flag = 0;
    if(x2*y2 <= 9){
        flag = 0;
    } else if(x2*y2 <= 99){
        flag = 1;
    } else {
        flag = 2;
    }

    printf("\033[97;105;1m");
    for (int i = 0; i < y2; i++) {
            gotoxy(x1+1, y1+1+i);
        for (int j = 0; j < x2; j++) {
            switch(flag){
                case 0:
                    printf("%d ", matriz[i][j]);
                    break;
                case 1:
                    printf("%2d ", matriz[i][j]);
                    break;
                case 2:
                    printf("%3d ", matriz[i][j]);
                    break;
            }
    
        }
        printf("\n");
    }
    
    printf(RESET);
}


int randomNumber(int x){
    int r;
    srand(time(NULL)); 
    r = rand() % x;
    return r;
}

void shuffleBoard(int **matriz){
    
}
