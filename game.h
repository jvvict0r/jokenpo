#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enumeração para as escolhas do jogo
typedef enum { PEDRA = 1, PAPEL, TESOURA } Escolha;

// Enumeração para os resultados da partida
typedef enum { VITORIA, DERROTA, EMPATE } Resultado;

// Exibe o menu principal do jogo
void exibir_menu();

// Exibe as regras do jogo Jokenpo
void exibir_regras();

// Obtém a escolha do jogador (Pedra, Papel ou Tesoura)
Escolha obter_escolha_jogador();

// Gera uma escolha aleatória para o bot
Escolha obter_escolha_bot();

// Determina o vencedor da rodada
Resultado determinar_vencedor(Escolha jogador, Escolha bot);

// Retorna o nome da escolha como uma string
const char *obter_nome_escolha(Escolha escolha);

// Função principal que gerencia o jogo
void jogar();

#endif