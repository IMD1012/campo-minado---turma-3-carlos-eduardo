#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcs.h"
#include "definitions.h"
#include "io.h"

// função que roda o menu e inicia o jogo/muda as configurações
int main(){

  int menu = 0, escolha = 0, input;
  campo campo[lt][ct];

    // enquanto o jogador não sair do programa, ele fica no loop do menu inicial
    while(menu==0){
      printf("\n(C)ampo Minado\n\n1: Iniciar Jogo\n2: Configuracoes\n3: Sair\n");
      scanf("%d", &menu);

      // loop de controle para garantir um comando válido
      while(menu!=1 && menu!=2 && menu!=3){
        printf("\nOpcao invalida. Tente novamente.\n");
        scanf("%d", &menu);
      }

      // opção do menu 1: inicia o jogo com as configurações atuais e pergunta se quer iniciar novamente ao acabar
      while(menu==1){
        initJogo(campo);
        printf("Iniciar novamente?\n1: Sim 2: Nao\n");
        scanf("%d", &escolha);

        // loop de controle para garantir um comando válido
        while(escolha!=1 && escolha!=2){
          printf("\nOpcao invalida. Tente novamente.\n");
          scanf("%d", &escolha);
        }
        
        // se não, volta ao menu
        if(escolha==2){
          menu = 0;
          escolha = 0;
        }
      }

      // opção do menu 2: acessa as configurações
      while(menu==2){
        
        // imprime as configurações atuais
        printf("\nConfiguracoes atuais:\nCampo %dx%d com %d minas\n", lt, ct, minas);
        if(modo==1){
            printf("Modo: Sempre iniciar com casa vazia\n");
        }else{
            printf("Modo: Sempre iniciar com numero\n");
        }
        if(automode==0){
            printf("Modo automatico: OFF\n");
        }else{
            printf("Modo automatico: ON\n");
        }

        // opções de mudança de configurações
        printf("1: Mudar tamanho do campo\n2: Mudar numero de minas\n3: Mudar modo\n4: Ligar/desligar automode\n5: Voltar\n");
        scanf("%d", &escolha);

        // loop de controle para garantir um comando válido
        while(escolha!= 1 && escolha!= 2 && escolha!= 3 && escolha!= 4 && escolha!= 5){
            printf("\nOpcao invalida. Tente novamente.\n");
            scanf("%d", &escolha);
        }
        
        if(escolha==1){ // 1: muda o tamanho do campo
            int input1, input2;
            printf("Escolha o novo tamanho do campo:\n");
            scanf("%d %d", &input1, &input2);

            // tratamento para que o tamanho do campo seja válido
            if(input1<2 || input2<2 || input1*input2>200){
                printf("\nTamanho de campo invalido. O campo tem que ser ao menos 2x2 e com no maximo 200 casas.\n");
            }else if(input1*input2<minas){
                printf("\nTamanho de campo invalido. O numero total de casas e menor que o numero de minas.\n");
            }else if(input1*input2<5 && modo==1){
                printf("\nTamanho de campo invalido. O campo nao pode ter menos que 9 casas se o modo de jogo for \"Sempre iniciar com casa vazia\". \n");
            }else{
                lt = input1;
                ct = input2;
            }
        }else if(escolha==2){ // 2: muda o número de minas
            printf("Escolha o novo numero de minas:\n");
            scanf("%d", &input);

            // tratamento para que o número de minas seja válido
            if(input<lt*ct){
                minas = input;
            }else{
                printf("\nNumero de minas invalido! Cheque o tamanho do campo.\n");
            }
        }else if(escolha==3){ // 3: alterna o modo de jogo entre 1(começar com 0) e 2(começar com número)
          if(modo==1){
            modo = 2;
          }else if(modo==2 && lt*ct<5){
            printf("\nNao e possivel trocar de modo pois o campo nao tem o tamanho minimo (9 casas).\n");
          }else if(modo==2){
            modo = 1;
          }
        }else if(escolha==4){ // 4: alterna o modo autómatico entre ligado e desligado
          if(automode==0){
            automode = 1;
          }else if(automode==1){
            automode = 0;
          }
        }else if(escolha==5){ // 5: volta pro menu inicial
          menu = 0;
        }
      }
        
    }
    // opção do menu 3: o loop do menu se encerra e o jogo fecha
    return 0;
}