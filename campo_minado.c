#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int endgame = 0;
//lt = linhas totais
//ct = colunas totais
//Mude os números abaixos para alterar no programa inteiro
int lt = 10, ct = 20, minas = 40;

//índices do campo: status de aberto/fechado, status de é mina/não é e número correspondente a quantia de minas ao seu redor
typedef struct{
    int status;
    int mina;
    int numero;
}campo;

//função que checa se um índice chamado está dentro do campo
int valid(int l, int c){
    if(l>=0 && l<lt && c>=0 && c<ct){
        return 1;
    }else{
        return 0;
    }
}

//função que conta quantas bombas há nas 8 casas ao redor de um índice e retorna a quantia
int quantbombas(int l, int c, campo campo[lt][ct]){
    int n=0;
    
    if(valid(l-1, c-1) && campo[l-1][c-1].mina==1){
        n++;
    }
    if(valid(l-1, c) && campo[l-1][c].mina==1){
        n++;
    }
    if(valid(l-1, c+1) && campo[l-1][c+1].mina==1){
        n++;
    }
    if(valid(l, c-1) && campo[l][c-1].mina==1){
        n++;
    }
    if(valid(l, c+1) && campo[l][c+1].mina==1){
        n++;
    }
    if(valid(l+1, c-1) && campo[l+1][c-1].mina==1){
        n++;
    }
    if(valid(l+1, c) && campo[l+1][c].mina==1){
        n++;
    }
    if(valid(l+1, c+1) && campo[l+1][c+1].mina==1){
        n++;
    }
    
   return n;
}

//função que inicia o campo
void initCampo(campo campo[lt][ct]){
    int i, j, lrand, crand;

    //primeiro inicia todos os índices do struct do campo como 0 para ter a base
    for(i=0;i<lt;i++){
        for(j=0;j<ct;j++){
            campo[i][j].status = 0;
            campo[i][j].mina = 0;
            campo[i][j].numero = 0;
        }
    }

    //depois distribui as X bombas
    i = 0;
    srand(time(NULL));
    while(i!=minas){
        lrand = rand()%lt;
        crand = rand()%ct;
        if(campo[lrand][crand].mina == 0){
            campo[lrand][crand].mina = 1;
            i++;
        }
    }

    //e por último transforma as casas que não viraram bombas em números correspondentes a quantidade de bombas vizinhas
    for(i=0;i<lt;i++){
        for(j=0;j<ct;j++){
            campo[i][j].numero = quantbombas(i, j, campo);
        }
    }
}

//função para printar o campo gerado
void printar(campo campo[lt][ct]){
    int i, j, cont = 1;

    printf("   ");
    for(i=0;i<ct;i++){
        if(i==ct-1){
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
            if(campo[i][j].status == 0){
                printf("|__");
            }else if(campo[i][j].mina == 1){
                printf("|_X", campo[i][j].numero);
            }else{
                printf("|_%d", campo[i][j].numero);
            }
        }
        printf("\n");
    }
}

//função que inicia a partida
void initJogo(campo campo[lt][ct]){
    int input1, input2;
    initCampo(campo);

    while(endgame==0){
        printar(campo);
        int pass = 0;

        
        scanf("%d %d", &input1, &input2);
        if(input1>0){
            input1--;
        }
        if(input2>0){
            input2--;
        }
            

        if(campo[input1][input2].mina == 1){
            campo[input1][input2].status = 1;
            printar(campo);
            printf("GAME OVER\n");
            endgame = 1;
        }else{
            campo[input1][input2].status = 1;
        }
    }
}

int main(){
    campo campo[lt][ct];

    initJogo(campo);

    return 0;
}