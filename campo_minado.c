#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"
#include "funcs.h"
#include "io.h"

int main() {
  campo campo[10][20];

  int modo = 1, automode = 0;

  int menu = 0, escolha = 0;

  while (menu == 0) {
    printf("\n(C)ampo Minado\n\n1: Iniciar Jogo\n2: Configuracoes\n3: Sair\n");
    scanf("%d", &menu);

    while (menu != 1 && menu != 2 && menu != 3) {
      printf("Opcao invalida. Tente novamente.\n");
      scanf("%d", &menu);
    }

    while (menu == 1) {
      initJogo(campo, automode, modo);
      printf("Iniciar novamente?\n1: Sim 2: Nao\n");
      scanf("%d", &escolha);

      while (escolha != 1 && escolha != 2) {
        printf("Opcao invalida. Tente novamente.\n");
        scanf("%d", &escolha);
      }

      if (escolha == 2) {
        menu = 0;
        escolha = 0;
      }
    }

    while (menu == 2) {

      printf("\nConfiguracoes atuais:\nCampo 10x20 com 40 minas\n");
      if (modo == 1) {
        printf("Modo: Sempre iniciar com casa vazia\n");
      } else {
        printf("Modo: Sempre iniciar com numero\n");
      }
      if (automode == 0) {
        printf("Modo automatico: OFF\n");
      } else {
        printf("Modo automatico: ON\n");
      }

      printf("1: Mudar modo\n2: Ligar/desligar automode\n3: Voltar\n");
      scanf("%d", &escolha);

      while (escolha != 1 && escolha != 2 && escolha != 3) {
        printf("Opcao invalida. Tente novamente.\n");
        scanf("%d", &escolha);
      }

      if (escolha == 1) {
        if (modo == 1) {
          modo = 2;
        }else if (modo == 2) {
          modo = 1;
        }
      } else if (escolha == 2) {
        if (automode == 0) {
          automode = 1;
        } else if (automode == 1) {
          automode = 0;
        }
      } else if (escolha == 3) {
        menu = 0;
        escolha = 0;
      }
    }
  }
  return 0;
}