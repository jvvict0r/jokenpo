#include "game.h"
#include "utils.h"

// Exibe o menu principal do jogo
void exibir_menu() {
  clear_screen();
  printf("=====================================\n");
  printf("        JOGO DE JOKENPOO EM C        \n");
  printf("=====================================\n");
  printf("1. Jogar\n");
  printf("2. Regras\n");
  printf("3. Sair\n");
  printf("=====================================\n");
  printf("Escolha uma opcao: ");
}

// Exibe as regras do jogo Jokenpo
void exibir_regras() {
  clear_screen();
  printf("=====================================\n");
  printf("           REGRAS DO JOKENPO         \n");
  printf("=====================================\n");
  printf("O Jokenpo, tambem conhecido como Pedra, Papel e Tesoura, \n");
  printf("e um jogo simples de mao jogado entre duas pessoas.\n\n");
  printf("As regras sao:\n");
  printf("1. Pedra quebra Tesoura (Pedra vence Tesoura)\n");
  printf("2. Papel cobre Pedra (Papel vence Pedra)\n");
  printf("3. Tesoura corta Papel (Tesoura vence Papel)\n");
  printf("4. Se ambos escolherem o mesmo, e um empate.\n");
  printf("=====================================\n");
  pause_screen();
}

// Obtém a escolha do jogador (Pedra, Papel ou Tesoura)
Escolha obter_escolha_jogador() {
  int escolha_int;
  while (1) {
    printf("Sua escolha:\n");
    printf("1. Pedra\n");
    printf("2. Papel\n");
    printf("3. Tesoura\n");
    printf("Escolha um numero (1-3): ");
    if (scanf("%d", &escolha_int) == 1) {
      if (escolha_int >= PEDRA && escolha_int <= TESOURA) {
        // Limpa o buffer de entrada
        while (getchar() != '\n')
          ;
        return (Escolha)escolha_int;
      } else {
        printf("Opcao invalida. Por favor, escolha um numero entre 1 e 3.\n");
      }
    } else {
      printf("Entrada invalida. Por favor, digite um numero.\n");
      // Limpa o buffer de entrada
      while (getchar() != '\n')
        ;
    }
  }
}

// Gera uma escolha aleatória para o bot
Escolha obter_escolha_bot() {
  return (Escolha)(rand() % 3 + 1); // Gera um número entre 1 e 3
}

// Determina o vencedor da rodada
Resultado determinar_vencedor(Escolha jogador, Escolha bot) {
  if (jogador == bot) {
    return EMPATE;
  } else if ((jogador == PEDRA && bot == TESOURA) ||
             (jogador == PAPEL && bot == PEDRA) ||
             (jogador == TESOURA && bot == PAPEL)) {
    return VITORIA;
  } else {
    return DERROTA;
  }
}

// Retorna o nome da escolha como uma string
const char *obter_nome_escolha(Escolha escolha) {
  switch (escolha) {
  case PEDRA:
    return "Pedra";
  case PAPEL:
    return "Papel";
  case TESOURA:
    return "Tesoura";
  default:
    return "Desconhecido";
  }
}

// Função principal que gerencia o jogo
void jogar() {
  int opcao;
  Escolha escolha_jogador, escolha_bot;
  Resultado resultado;

  // Inicializa o gerador de números aleatórios com base no tempo atual
  srand((unsigned int)time(NULL));

  do {
    exibir_menu();
    if (scanf("%d", &opcao) != 1) {
      printf("Entrada invalida. Por favor, digite um numero.\n");
      while (getchar() != '\n')
        ;
      opcao = 0;
      pause_screen();
      continue;
    }
    while (getchar() != '\n')
      ; // Limpa o buffer de entrada após scanf

    switch (opcao) {
    case 1: // Jogar
      clear_screen();
      printf("Iniciando Jokenpo...\n");
      escolha_jogador = obter_escolha_jogador();
      escolha_bot = obter_escolha_bot();

      printf("\n=====================================\n");
      printf(" Voce escolheu: %s\n", obter_nome_escolha(escolha_jogador));
      printf(" Bot escolheu:  %s\n", obter_nome_escolha(escolha_bot));
      printf("=====================================\n");

      resultado = determinar_vencedor(escolha_jogador, escolha_bot);

      switch (resultado) {
      case VITORIA:
        printf("         VOCE VENCEU! PARABENS!      \n");
        break;
      case DERROTA:
        printf("         VOCE PERDEU! MAIS SORTE NA PROXIMA! \n");
        break;
      case EMPATE:
        printf("         EMPATE!         \n");
        break;
      }
      printf("=====================================\n");
      pause_screen();
      break;
    case 2: // Regras
      exibir_regras();
      break;
    case 3: // Sair
      clear_screen();
      printf("Obrigado por jogar! Ate mais!\n");
      break;
    default:
      printf("Opcao invalida. Por favor, escolha novamente.\n");
      pause_screen();
      break;
    }
  } while (opcao != 3);
}