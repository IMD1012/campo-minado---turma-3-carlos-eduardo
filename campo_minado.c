#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//lt = linhas totais
//ct = colunas totais
//Mude os números abaixos para alterar no programa inteiro
int lt = 10, ct = 20, minas = 40;

//todos os índices do campo têm um status de aberto/fechado, um status de é bomba/não é e um número correspondente a quantia de bombas ao seu redor
typedef struct{
    int status;
    int bomba;
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
    
    if(valid(l-1, c-1) && campo[l-1][c-1].bomba==1){
        n++;
    }
    if(valid(l-1, c) && campo[l-1][c].bomba==1){
        n++;
    }
    if(valid(l-1, c+1) && campo[l-1][c+1].bomba==1){
        n++;
    }
    if(valid(l, c-1) && campo[l][c-1].bomba==1){
        n++;
    }
    if(valid(l, c+1) && campo[l][c+1].bomba==1){
        n++;
    }
    if(valid(l+1, c-1) && campo[l+1][c-1].bomba==1){
        n++;
    }
    if(valid(l+1, c) && campo[l+1][c].bomba==1){
        n++;
    }
    if(valid(l+1, c+1) && campo[l+1][c+1].bomba==1){
        n++;
    }
    
   return n;
}

//função que inicia o campo;
void init(campo campo[lt][ct]){
    int i, j, lrand, crand;

    //primeiro inicia todos os índices do struct do campo como 0 para ter a base
    for(i=0;i<lt;i++){
        for(j=0;j<ct;j++){
            campo[i][j].status = 0;
            campo[i][j].bomba = 0;
            campo[i][j].numero = 0;
        }
    }

    //depois distribui as X bombas
    i = 0;
    srand(time(NULL));
    while(i!=minas){
        lrand = rand()%lt;
        crand = rand()%ct;
        if(campo[lrand][crand].bomba == 0){
            campo[lrand][crand].bomba = 1;
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

//função para printar o campo gerado (usada para debugging, apagar/comentar no produto final)
void printar(campo campo[lt][ct]){
    int i, j;
    for(i=0;i<lt;i++){
        for(j=0;j<ct;j++){
            if(campo[i][j].bomba == 1){
                printf("X ");
            }else{
                printf("%d ", campo[i][j].numero);
            }
        }
        printf("\n");
    }
}

int main(){
    campo oculto[lt][ct];

    init(oculto);
    printar(oculto);

    return 0;
}