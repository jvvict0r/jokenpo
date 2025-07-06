#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Limpa a tela do console
void clear_screen() {
  system("cls");
}

// Pausa a execução do programa e aguarda o usuário pressionar uma tecla
void pause_screen() {
  printf("\nPressione ENTER para continuar...");
  // Limpa o buffer de entrada antes de ler o próximo caractere
  while (getchar() != '\n')
    ;        // Garante que o buffer de entrada esteja limpo
  getchar(); // Espera por um caractere 
}