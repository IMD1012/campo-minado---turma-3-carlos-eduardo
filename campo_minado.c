#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "funcs.h"
#include "definitions.h"
#include "io.h"

int main(){

  time_t start,end;

  int endgame = 0, reveladas = 0, init1, init2, modo = 1, automode = 0, rodada = 1;
  
  int menu = 0, escolha = 0, input;
  campo campo[10][20];

    while(menu==0){
      printf("\n(C)ampo Minado\n\n1: Iniciar Jogo\n2: Configuracoes\n3: Sair\n");
      scanf("%d", &menu);

      while(menu!=1 && menu!=2 && menu!=3){
        printf("\nOpcao invalida. Tente novamente.\n");
        scanf("%d", &menu);
      }

      while(menu==1){
        initJogo(campo, start, end, reveladas, endgame, automode, init1, init2, modo);
        printf("Iniciar novamente?\n1: Sim 2: Nao\n");
        scanf("%d", &escolha);

        while(escolha!=1 && escolha!=2){
          printf("\nOpcao invalida. Tente novamente.\n");
          scanf("%d", &escolha);
        }
        
        if(escolha==2){
          menu = 0;
          escolha = 0;
        }
      }

      while(menu==2){
        
        printf("\nConfiguracoes atuais:\nCampo %dx%d com %d minas\n", 10, 20, 40);
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

        printf("1: Mudar tamanho do campo\n2: Mudar numero de minas\n3: Mudar modo\n4: Ligar/desligar automode\n5: Vo10ar\n");
        scanf("%d", &escolha);

        while(escolha!= 1 && escolha!= 2 && escolha!= 3 && escolha!= 4 && escolha!= 5){
            printf("\nOpcao invalida. Tente novamente.\n");
            scanf("%d", &escolha);
        }
        
        if(escolha==3){
          if(modo==1){
            modo = 2;
          }else if(modo==2 && 10*20<5){
            printf("\nNao e possivel trocar de modo pois o campo nao tem o tamanho minimo (9 casas).\n");
          }else if(modo==2){
            modo = 1;
          }
        }else if(escolha==4){ 
          if(automode==0){
            automode = 1;
          }else if(automode==1){
            automode = 0;
          }
        }else if(escolha==5){
          menu = 0;
        }
      }
        
    }
    return 0;
}