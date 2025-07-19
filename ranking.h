#ifndef RANKING_H
#define RANKING_H


typedef struct {
    char nome[50];
    int pontuacao;
} Jogador;

extern Jogador *ranking;
extern int totalJogadores;
extern int capacidadeJogadores;
extern int jogadorAtual;

#endif
