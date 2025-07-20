#include "game.h"
#include "ranking.h"
#include "gconio.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

static void borda_titulo();
static void exibir_menu_principal();
static void desenhar_tela_jogo(const char* status);
static void selecionar_jogador_visual();
static void cadastrar_jogador_visual();
static void exibir_ranking_visual();
static void exibir_regras_visual();
static Escolha obter_escolha_jogador_visual();

static void borda_titulo() {
    int col;
    textcolor(BLACK);
    gotoxy(5, 3); printf("╔");
    for (col = 6; col < 83; col++) { gotoxy(col, 3); printf("═"); }
    gotoxy(83, 3); printf("╗");
    for (int lin = 4; lin < 11; lin++) {
        gotoxy(5, lin); printf("║");
        gotoxy(83, lin); printf("║");
    }
    gotoxy(12, 4); printf("      ██╗ ██████╗ ██╗  ██╗███████╗███╗   ██╗██████╗  ██████╗ ");
    gotoxy(12, 5); printf("      ██║██╔═══██╗██║ ██╔╝██╔════╝████╗  ██║██╔══██╗██╔═══██╗");
    gotoxy(12, 6); printf("      ██║██║   ██║█████╔╝ █████╗  ██╔██╗ ██║██████╔╝██║   ██║");
    gotoxy(12, 7); printf(" ██   ██║██║   ██║██╔═██╗ ██╔══╝  ██║╚██╗██║██╔═══╝ ██║   ██║");
    gotoxy(12, 8); printf(" ╚█████╔╝╚██████╔╝██║  ██╗███████╗██║ ╚████║██║     ╚██████╔╝");
    gotoxy(12, 9); printf("  ╚════╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═╝      ╚═════╝ ");
    gotoxy(5, 10); printf("╚");
    for (col = 6; col < 83; col++) { gotoxy(col, 10); printf("═"); }
    gotoxy(83, 10); printf("╝");
}

void animacao_abertura() {
    clrscr();
    borda_titulo();
    gotoxy(25, 20); printf("Aperte Qualquer Tecla para Iniciar");
    getch();
    gotoxy(25, 20); printf("                                  ");

    for (int coluna = 60; coluna >= 30; coluna--) {
        gotoxy(12, 13); printf("                                                             ");
        gotoxy(coluna, 13); printf("BEM-VINDO!!");
        Sleep(20);
    }
    gotoxy(30, 15); printf("CARREGANDO... ");
    gotoxy(30, 16); textbackground(GREEN);
    for (int contador = 0; contador < 22; contador++) {
        Sleep(30); printf(" ");
    }
    textbackground(LIGHTCYAN);
    Sleep(500);
}

static void exibir_menu_principal() {
    clrscr();
    borda_titulo();
    textcolor(BLACK);
    gotoxy(30, 12); printf("MENU PRINCIPAL");
    if (jogadorAtual != -1) {
        gotoxy(30, 13); printf("Jogador: %s", ranking[jogadorAtual].nome);
    }
    gotoxy(30, 15); printf("(1) Jogar");
    gotoxy(30, 16); printf("(2) Selecionar Jogador");
    gotoxy(30, 17); printf("(3) Cadastrar Novo Jogador");
    gotoxy(30, 18); printf("(4) Ver Ranking");
    gotoxy(30, 19); printf("(5) Regras");
    gotoxy(30, 20); printf("(0) Sair");
    gotoxy(30, 22); printf("Escolha uma opcao: ");
}

static void desenhar_tela_jogo(const char* status) {
    clrscr();
    gotoxy(10, 1); printf("    _______                _______               _______   ");
    gotoxy(10, 2); printf("---'   ____)           ---'   ____)____         ---'    ____)___");
    gotoxy(10, 3); printf("      (_____)                   ______)                   ______)");
    gotoxy(10, 4); printf("      (_____)                  _______)               __________)");
    gotoxy(10, 5); printf("      (____)                   _______)              (____)");
    gotoxy(10, 6); printf("---.__(___)             ---.__________)         ---.__(___)");
    gotoxy(15, 8); printf("1. PEDRA");
    gotoxy(40, 8); printf("2. PAPEL");
    gotoxy(65, 8); printf("3. TESOURA");

    gotoxy(10, 12); printf("========================================================================");
    gotoxy(10, 13); printf(" STATUS: %s", status);
    gotoxy(10, 14); printf("========================================================================");

    if (jogadorAtual != -1) {
        gotoxy(10, 16); printf("JOGADOR: %s", ranking[jogadorAtual].nome);
        gotoxy(10, 17); printf("PONTUACAO: %d", ranking[jogadorAtual].pontuacao);
    }
    gotoxy(10, 19); printf("Sua escolha (1-3): ");
}

void liberar_memoria() {
    if (ranking != NULL) {
        free(ranking);
        ranking = NULL;
    }
}

void carregar_ranking() {
    FILE *f = fopen("ranking.txt", "r");
    if (f == NULL) return;

    capacidadeJogadores = 10;
    ranking = malloc(capacidadeJogadores * sizeof(Jogador));
    if (ranking == NULL) { printf("Falha de memoria inicial!"); exit(1); }

    while (fscanf(f, " %49[^,],%d\n", ranking[totalJogadores].nome, &ranking[totalJogadores].pontuacao) == 2) {
        totalJogadores++;
        if (totalJogadores == capacidadeJogadores) {
            capacidadeJogadores += 5;
            Jogador *novoRanking = realloc(ranking, capacidadeJogadores * sizeof(Jogador));
            if (novoRanking == NULL) { printf("Falha ao realocar memoria!"); exit(1); }
            ranking = novoRanking;
        }
    }
    fclose(f);
}

void cadastrar_jogador() {
    if (ranking == NULL) {
        capacidadeJogadores = 5;
        ranking = malloc(capacidadeJogadores * sizeof(Jogador));
        if (ranking == NULL) { printf("Falha de memoria inicial!"); exit(1); }
    }
    if (totalJogadores == capacidadeJogadores) {
        capacidadeJogadores += 5;
        Jogador *novoRanking = realloc(ranking, capacidadeJogadores * sizeof(Jogador));
        if (novoRanking == NULL) { printf("Falha ao realocar memoria!"); return; }
        ranking = novoRanking;
    }

    scanf(" %49[^\n]", ranking[totalJogadores].nome);
    ranking[totalJogadores].pontuacao = 0;
    jogadorAtual = totalJogadores;
    totalJogadores++;
}

void salvar_ranking() {
    FILE *f = fopen("ranking.txt", "w");
    if (f == NULL) return;
    for (int i = 0; i < totalJogadores; i++) {
        fprintf(f, "%s,%d\n", ranking[i].nome, ranking[i].pontuacao);
    }
    fclose(f);
}

static void selecionar_jogador_visual() {
    while(1) {
        clrscr();
        borda_titulo();
        gotoxy(30, 12); printf("SELECIONAR JOGADOR");

        if (totalJogadores == 0) {
            gotoxy(30, 14); printf("Nenhum jogador cadastrado!");
            gotoxy(30, 16); printf("Pressione qualquer tecla para voltar...");
            getch();
            return;
        }

        for (int i = 0; i < totalJogadores; i++) {
            gotoxy(30, 14 + i); printf("%d. %s", i + 1, ranking[i].nome);
        }
        gotoxy(30, 14 + totalJogadores + 1); printf("0. Voltar");

        gotoxy(30, 20); printf("Escolha uma opcao: ");
        char escolha_char = getch();

        if (escolha_char > '0' && escolha_char <= ('0' + totalJogadores)) {
            jogadorAtual = (escolha_char - '0') - 1;
            return;
        } else if (escolha_char == '0') {
            return;
        }
    }
}

static void cadastrar_jogador_visual() {
    clrscr();
    borda_titulo();
    gotoxy(30, 12); printf("CADASTRAR NOVO JOGADOR");
    gotoxy(30, 14); printf("Digite o nome: ");
    cadastrar_jogador();
    gotoxy(30, 16); printf("Jogador '%s' cadastrado e selecionado!", ranking[jogadorAtual].nome);
    gotoxy(30, 18); printf("Pressione qualquer tecla para continuar...");
    getch();
}

static void exibir_ranking_visual() {
    clrscr();
    borda_titulo();
    gotoxy(30, 12); printf("RANKING DE JOGADORES");

    for (int i = 0; i < totalJogadores - 1; i++) {
        for (int j = 0; j < totalJogadores - i - 1; j++) {
            if (ranking[j].pontuacao < ranking[j + 1].pontuacao) {
                Jogador temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < totalJogadores; i++) {
        gotoxy(30, 14 + i); printf("%d. %-20s %d pontos", i + 1, ranking[i].nome, ranking[i].pontuacao);
    }
    gotoxy(30, 20); printf("Pressione qualquer tecla para voltar...");
    getch();
}

static void exibir_regras_visual() {
    clrscr();
    borda_titulo();
    gotoxy(30, 12); printf("REGRAS DO JOGO");
    gotoxy(30, 14); printf("Pedra ganha de Tesoura");
    gotoxy(30, 15); printf("Tesoura ganha de Papel");
    gotoxy(30, 16); printf("Papel ganha de Pedra");
    gotoxy(30, 20); printf("Pressione qualquer tecla para voltar...");
    getch();
}

static Escolha obter_escolha_jogador_visual() {
    char c;
    do {
        c = getch();
    } while (c < '1' || c > '3');
    return (Escolha)(c - '0');
}

const char* obter_nome_escolha(Escolha e) {
    switch (e) {
        case PEDRA: return "Pedra";
        case PAPEL: return "Papel";
        case TESOURA: return "Tesoura";
    }
    return "Desconhecido";
}

Resultado determinar_vencedor(Escolha jogador, Escolha bot) {
    if (jogador == bot) return EMPATE;
    if ((jogador == PEDRA && bot == TESOURA) ||
        (jogador == PAPEL && bot == PEDRA) ||
        (jogador == TESOURA && bot == PAPEL)) {
        return VITORIA;
    }
    return DERROTA;
}

void jogar() {
    char opcao_menu;
    animacao_abertura();
    carregar_ranking();
    srand((unsigned int)time(NULL));

    do {
        exibir_menu_principal();
        opcao_menu = getch();

        switch (opcao_menu) {
            case '1':
                if (jogadorAtual == -1) {
                    gotoxy(30, 21);
                    printf("ERRO: Nenhum jogador selecionado!");
                    getch();
                } else {
                    char status[100] = "Escolha sua jogada!";
                    char repetir = '1';
                    while (repetir == '1') {
                        desenhar_tela_jogo(status);
                        Escolha escolha_jogador = obter_escolha_jogador_visual();
                        Escolha escolha_bot = (Escolha)(rand() % 3 + 1);
                        Resultado resultado = determinar_vencedor(escolha_jogador, escolha_bot);

                        if (resultado == VITORIA) {
                            sprintf(status, "VITORIA! Voce: %s vs Bot: %s.", obter_nome_escolha(escolha_jogador), obter_nome_escolha(escolha_bot));
                            ranking[jogadorAtual].pontuacao++;
                        } else if (resultado == DERROTA) {
                            sprintf(status, "DERROTA! Voce: %s vs Bot: %s.", obter_nome_escolha(escolha_jogador), obter_nome_escolha(escolha_bot));
                            ranking[jogadorAtual].pontuacao--;
                        } else {
                            sprintf(status, "EMPATE! Ambos escolheram %s.", obter_nome_escolha(escolha_jogador));
                        }
                        salvar_ranking();
                        desenhar_tela_jogo(status);
                        gotoxy(10, 20); printf("Jogar novamente? (1-Sim / Outra tecla-Nao): ");
                        repetir = getch();
                    }
                }
                break;
            case '2':
                selecionar_jogador_visual();
                break;
            case '3':
                cadastrar_jogador_visual();
                break;
            case '4':
                exibir_ranking_visual();
                break;
            case '5':
                exibir_regras_visual();
                break;
            case '0':
                salvar_ranking();
                break;
            default:
                gotoxy(30, 21);
                printf("Opcao invalida!");
                getch();
                break;

        }
    }while(opcao_menu != '0');
    }
