#include "game.h"
#include "gconio.h"
#include <windows.h>


void inicializar_interface();

int main() {
  inicializar_interface();
  jogar();
  liberar_memoria();

  clrscr();
  textbackground(BLACK);
  textcolor(WHITE);
  printf("Obrigado por jogar!\n");
  return 0;
}


void inicializar_interface() {

    system("chcp 65001");

    SetConsoleTitleA("Jokenpo - O Jogo");

    system("mode con: cols=90 lines=25");


    textbackground(LIGHTCYAN);
    textcolor(BLACK);
    clrscr();
}
