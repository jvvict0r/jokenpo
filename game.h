#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef enum { PEDRA = 1, PAPEL, TESOURA } Escolha;
typedef enum { VITORIA, DERROTA, EMPATE } Resultado;


void jogar();
void animacao_abertura();


const char* obter_nome_escolha(Escolha escolha);
Resultado determinar_vencedor(Escolha jogador, Escolha bot);

void carregar_ranking();
void salvar_ranking();
void cadastrar_jogador();
void liberar_memoria();

#endif
