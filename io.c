#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcs.h"
#include "definitions.h"
#include "io.h"

// função que inicia o campo
void initCampo(campo campo[lt][ct]){
    int i, j, lrand, crand;

    // primeiro inicia todos os índices do struct do campo como 0 para ter a base
    for(i=0;i<lt;i++){
        for(j=0;j<ct;j++){
            campo[i][j].status = 0;
            campo[i][j].mina = 0;
            campo[i][j].numero = 0;
        }
    }
    i = 0;

    // depois distribui as X bombas
    srand(time(NULL));
    while(i!=minas){
        lrand = rand()%lt;
        crand = rand()%ct;
        if(campo[lrand][crand].mina == 0){
            campo[lrand][crand].mina = 1;
            i++;
            if(modo==1){
                if((lrand == init1 && crand == init2) || quantbombas(init1, init2, campo)!=0){
                    campo[lrand][crand].mina = 0;
                    i--;
                }
            }else if(modo==2){
                if((lrand == init1 && crand == init2) || i==minas && quantbombas(init1, init2, campo)==0){
                    campo[lrand][crand].mina = 0;
                    i--;
                }
            }
        }
    }

    // e por último transforma as casas que não viraram bombas em números correspondentes a quantidade de bombas vizinhas
    for(i=0;i<lt;i++){
        for(j=0;j<ct;j++){
            campo[i][j].numero = quantbombas(i, j, campo);
        }
    }
}

// função para printar o campo gerado
void printar(campo campo[lt][ct]){
    int i, j, cont = 1;

    //imprime o número de colunas
    printf("\n   ");
    for(i=0;i<ct;i++){
        if(i<10 && i==ct-1){
            printf(" %d\n", i+1);
        }else if(i==ct-1){
            printf("%d\n", i+1);
        }else if(i+1>=10){
            printf("%d ", i+1);
        }else{
            printf(" %d ", i+1);
        }
    }

    // imprime o número de linhas
    for(i=0;i<lt;i++){
        if(cont<10){
            printf(" %d", cont);
        }else{
            printf("%d", cont);
        }
        cont++;

        // e o campo em si (ao acertar uma mina todas as minas são expostas)
        if(endgame==0){
            for(j=0;j<ct;j++){
                if(campo[i][j].status == 0){
                    printf("|__");
                }else{
                    printf("|_%d", campo[i][j].numero);
                }
            }
        }else{
            for(j=0;j<ct;j++){
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

// função que checa se a condição de vitória foi alcançada
void wincheck(campo campo[lt][ct]){
    if(reveladas==(lt*ct)-minas){
        endgame = 1;
        printar(*campo);
        printf("Vitoria! Todas as minas foram evitadas.\n");
    }
}


// função que faz alguns cálculos e sugere uma casa com baixas chances de ser uma mina quando solicitada
void sugerir_casa(campo campo[lt][ct]){
    int sugl, sugc, temp, templ, tempc;
    float chance, chanceN = 100;
    
    // descobre qual a casa com a menor relação minas/casas ocultas
    for(int i=0;i<lt;i++){
        for(int j=0;j<ct;j++){
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
    // escolhe aleatoriamente uma casa oculta ao redor da casa escolhida para revelar
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

    // imprime qual casa o jogo escolheu como sugestão
    if(automode==0){
        printf("tente na casa %dx%d!\n", sugl+1, sugc+1);
    }else if(automode==1){ // OU se o jogo estiver no modo automático, o sistema declara qual casa vai tentar
        printf("tentando na casa %dx%d!\n", sugl+1, sugc+1);
        revelar(sugl, sugc, campo);
        wincheck(*campo);
    }
}

// função que inicia a partida
void initJogo(campo campo[lt][ct]){
    int input1, input2, i, j, cont = 1, menu, rodada = 1;
    reveladas = 0;

    // imprime um campo falso apenas para parecer que o jogo começou, mas aguarda
    // o primeiro par de coordenadas para gerar o campo e realmente começar
    printf("   ");
    for(i=0;i<ct;i++){
        if(i<10 && i==ct-1){
            printf(" %d\n", i+1);
        }else if(i==ct-1){
            printf("%d\n", i+1);
        }else if(i+1>=10){
            printf("%d ", i+1);
        }else{
            printf(" %d ", i+1);
        }
    }
    for(i=0;i<lt;i++){
        if(cont<10){
            printf(" %d", cont);
        }else{
            printf("%d", cont);
        }
        cont++;
        
            for(j=0;j<ct;j++){
                    printf("|__");
            }
        printf("\n");
    }
  
    // pequeno loop para garantir que a primeira coordenada é válida
    if(automode==0){
        printf("Insira as coordenadas: ");
        scanf("%d %d", &init1, &init2);
        init1--;
        init2--;
        while(valid(init1, init2)==0 ||(lt==3 && ct==3 && init1==1 && init2==1 && modo==1)){
            if(valid(init1, init2)==0){
                printf("Coordenada invalida! Tente outra.\n");
            }else if(lt==3 && ct==3 && init1==1 && init2==1 && modo==1){ // a casa 2x2 não pode ser revelada de primeira em um jogo de campo 3x3 com modo "iniciar sempre com casa vazia", pois isso quebra o jogo
                printf("Coordenada invalida para o campo 3x3 modo \"Iniciar sempre com casa vazia\". Tente outra.\n");
            }
            scanf("%d %d", &init1, &init2);
            init1--;
            init2--;
        }
    }else{ // ou caso o automode esteja ligado, um par de coordenadas aleatórias é gerado para iniciar o jogo
        int lrand = rand()%lt;
        int crand = rand()%ct;

        // esse loop aqui previne a mesma situação da casa 2x2 num campo 3x3 ali de cima
        while(lt==3 && ct==3 && lrand==1 && crand==1 && modo==1){
            lrand = rand()%lt;
            crand = rand()%ct;
        }

        init1 = lrand;
        init2 = crand;
        printf("Comecando com %dx%d.\n", init1+1, init2+1);
    }

    // com as primeiras coordenadas válidas, o campo é gerado, o tempo começa a contar e
    // as primeiras casas são reveladas (também ocorre um wincheck pois em alguns casos
    // bem específicos o jogo pode ser ganho nesse primeiro clique)
    endgame = 0;
    initCampo(*campo);
    start = time(NULL);
    revelar(init1, init2, campo);
    wincheck(*campo);


    while(endgame==0){

        // enquanto o jogo não acabar, o campo é impresso e o usuário escolhe se quer inserir uma
        // coordenada, consultar o tempo ou pedir uma sugestão a cada loop
        if(automode==0){
            printar(campo);
            printf("Digite:\n1: Coordenadas\n2: Tempo de jogo/Rodada\n3: Sugestao\n");
            scanf("%d", &menu);
        }else{ // mas se o automode estiver ligado, o input sempre será a sugestão
            printar(campo);
            menu = 3;
            rodada++;
        }

        if(menu == 1){ // inserir coordenadas
            printf("Insira as coordenadas: ");
            scanf("%d %d", &input1, &input2);
            input1--;
            input2--;
            if(valid(input1, input2)==0){
                printf("Coordenada invalida!\n");
            }else{
                rodada++;
                revelar(input1, input2, campo);
                wincheck(campo);
            }
        }
        else if (menu == 2) { // consultar o tempo
            end = time(NULL);
            printf("\nTempo de jogo: %ld segundos\n", end - start);
            printf("Rodadas: %d\n", rodada);
        }
        else if (menu == 3){ // pedir sugestão ao jogo
            sugerir_casa(campo);
        }
    }

  end = time(NULL);
  printf("Tempo de jogo: %ld segundos\n", end - start);
  printf("Rodadas: %d\n", rodada);
}