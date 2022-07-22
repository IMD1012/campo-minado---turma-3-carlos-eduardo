#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "funcs.h"
#include "definitions.h"
#include "io.h"


void initCampo(campo campo[10][20], int init1, int init2, int modo){
    int i, j, lrand, crand;

    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            campo[i][j].status = 0;
            campo[i][j].mina = 0;
            campo[i][j].numero = 0;
        }
    }
    i = 0;

    srand(time(NULL));
    while(i!=40){
        lrand = rand()%10;
        crand = rand()%20;
        if(campo[lrand][crand].mina == 0){
            campo[lrand][crand].mina = 1;
            i++;
            if(modo==1){
                if((lrand == init1 && crand == init2) || quantbombas(init1, init2, campo)!=0){
                    campo[lrand][crand].mina = 0;
                    i--;
                }
            }else if(modo==2){
                if((lrand == init1 && crand == init2) || i==40 && quantbombas(init1, init2, campo)==0){
                    campo[lrand][crand].mina = 0;
                    i--;
                }
            }
        }
    }


    for(i=0;i<10;i++){
        for(j=0;j<20;j++){
            campo[i][j].numero = quantbombas(i, j, campo);
        }
    }
}

void printar(campo campo[10][20], int endgame){
    int i, j, cont = 1;

    printf("\n   ");
    for(i=0;i<20;i++){
        if(i<10 && i==20-1){
            printf(" %d\n", i+1);
        }else if(i==20-1){
            printf("%d\n", i+1);
        }else if(i+1>=10){
            printf("%d ", i+1);
        }else{
            printf(" %d ", i+1);
        }
    }

    for(i=0;i<10;i++){
        if(cont<10){
            printf(" %d", cont);
        }else{
            printf("%d", cont);
        }
        cont++;

        if(endgame==0){
            for(j=0;j<20;j++){
                if(campo[i][j].status == 0){
                    printf("|__");
                }else{
                    printf("|_%d", campo[i][j].numero);
                }
            }
        }else{
            for(j=0;j<20;j++){
                if(campo[i][j].mina == 1){
                    printf("|_X");
                }else if(campo[i][j].status == 0){
                    printf("|__");
                }else{
                    printf("|_%d", campo[i][j].numero);
                }
            }
        }
        printf("\n");
    }
}

void wincheck(campo campo[10][20], int reveladas, int endgame){
    if(reveladas==(10*20)-40){
        endgame = 1;
        printar(campo, endgame);
        printf("Vitoria! Todas as minas foram evitadas.\n");
    }
}

void sugerir_casa(campo campo[10][20], int reveladas, int endgame, int modo, int automode){
    int sugl, sugc, temp, templ, tempc;
    float chance, chanceN = 100;
    
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            temp = 100.00/quantOcult(i, j, campo);
            chance = temp*campo[i][j].numero;
            if(campo[i][j].status == 1 && campo[i][j].numero>0 && quantOcult(i, j, campo)>campo[i][j].numero && chance<chanceN){
                chanceN = chance;
                sugl = i;
                sugc = j;
            }
        }
    }
    printf("\n%.1f %% de chance de mina ao redor da casa %dx%d.\n", chanceN, sugl+1, sugc+1);

    templ = sugl;
    tempc = sugc;

    while(valid(sugl, sugc)==0 || campo[sugl][sugc].status==1){
        sugl = templ;
        sugc = tempc;
        int lrand = rand()%3+1;
        int crand = rand()%3+1;

        if(lrand==1){
            sugl--;
        }else if(lrand==3){
            sugl++;
        }

        if(crand==1){
         sugc--;
        }else if(crand==3){
         sugc++;
        }
    }

    if(automode==0){
        printf("tente na casa %dx%d!\n", sugl+1, sugc+1);
    }else if(automode==1){
        printf("tentando na casa %dx%d!\n", sugl+1, sugc+1);
        revelar(sugl, sugc, campo, reveladas, endgame);
        wincheck(campo, reveladas, endgame);
    }
}

void initJogo(campo campo[10][20], time_t start,time_t end, int reveladas, int endgame, int automode, int init1, int init2, int modo){
    int input1, input2, i, j, cont = 1, menu, rodada = 1;
    reveladas = 0;

    printf("   ");
    for(i=0;i<20;i++){
        if(i<10 && i==20-1){
            printf(" %d\n", i+1);
        }else if(i==20-1){
            printf("%d\n", i+1);
        }else if(i+1>=10){
            printf("%d ", i+1);
        }else{
            printf(" %d ", i+1);
        }
    }
    for(i=0;i<10;i++){
        if(cont<10){
            printf(" %d", cont);
        }else{
            printf("%d", cont);
        }
        cont++;
        
            for(j=0;j<20;j++){
                    printf("|__");
            }
        printf("\n");
    }
  
    if(automode==0){
        printf("Insira as coordenadas: ");
        scanf("%d %d", &init1, &init2);
        init1--;
        init2--;
        while(valid(init1, init2)==0 ||(10==3 && 20==3 && init1==1 && init2==1 && modo==1)){
            if(valid(init1, init2)==0){
                printf("Coordenada invalida! Tente outra.\n");
            }else if(10==3 && 20==3 && init1==1 && init2==1 && modo==1){
                printf("Coordenada invalida para o campo 3x3 modo \"Iniciar sempre com casa vazia\". Tente outra.\n");
            }
            scanf("%d %d", &init1, &init2);
            init1--;
            init2--;
        }
    }else{
        int lrand = rand()%10;
        int crand = rand()%20;

        while(10==3 && 20==3 && lrand==1 && crand==1 && modo==1){
            lrand = rand()%10;
            crand = rand()%20;
        }

        init1 = lrand;
        init2 = crand;
        printf("Comecando com %dx%d.\n", init1+1, init2+1);
    }

    endgame = 0;
    initCampo(campo, init1, init2, modo);
    start = time(NULL);
    revelar(init1, init2, campo, reveladas, endgame);
    wincheck(campo, reveladas, endgame);


    while(endgame==0){

        if(automode==0){
            printar(campo, endgame);
            printf("Digite:\n1: Coordenadas\n2: Tempo de jogo/Rodada\n3: Sugestao\n");
            scanf("%d", &menu);
        }else{
            printar(campo, endgame);
            menu = 3;
            rodada++;
        }

        if(menu == 1){
            printf("Insira as coordenadas: ");
            scanf("%d %d", &input1, &input2);
            input1--;
            input2--;
            if(valid(input1, input2)==0){
                printf("Coordenada invalida!\n");
            }else{
                rodada++;
                revelar(input1, input2, campo, reveladas, endgame);
                wincheck(campo, reveladas, endgame);
            }
        }
        else if (menu == 2) {
            end = time(NULL);
            printf("\nTempo de jogo: %ld segundos\n", end - start);
            printf("Rodadas: %d\n", rodada);
        }
        else if (menu == 3){
            sugerir_casa(campo, reveladas, endgame, modo, automode);
        }
    }

  end = time(NULL);
  printf("Tempo de jogo: %ld segundos\n", end - start);
  printf("Rodadas: %d\n", rodada);
}