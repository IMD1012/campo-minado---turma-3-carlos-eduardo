#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcs.h"
#include "definitions.h"
#include "io.h"

// função que checa se um índice chamado está dentro do campo
int valid(int l, int c){
    if(l>=0 && l<lt && c>=0 && c<ct){
        return 1;
    }else{
        return 0;
    }
}

// função que conta e retorna quantas bombas há nas 8 casas ao redor de um determinado índice
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

// função que conta quantas casas ocultas existem ao redor de um determinado índice
int quantOcult(int l, int c, campo campo[lt][ct]){
    int n=0;
    
    if(valid(l-1, c-1) && campo[l-1][c-1].status==0){
        n++;
    }
    if(valid(l-1, c) && campo[l-1][c].status==0){
        n++;
    }
    if(valid(l-1, c+1) && campo[l-1][c+1].status==0){
        n++;
    }
    if(valid(l, c-1) && campo[l][c-1].status==0){
        n++;
    }
    if(valid(l, c+1) && campo[l][c+1].status==0){
        n++;
    }
    if(valid(l+1, c-1) && campo[l+1][c-1].status==0){
        n++;
    }
    if(valid(l+1, c) && campo[l+1][c].status==0){
        n++;
    }
    if(valid(l+1, c+1) && campo[l+1][c+1].status==0){
        n++;
    }
   return n;
}

// função que recebe o input de linha/coluna e altera o campo
int revelar(int l, int c, campo campo[lt][ct]){

    // se o campo não estiver revelado ainda e a casa do indicada não for uma bomba, o contador de casas reveladas aumenta, se não, nada acontece 
    if(campo[l][c].status==0 && campo[l][c].mina!=1){
        reveladas++;
    }else if(campo[l][c].status==1){
        printf("Coordenada ja revelada.\n");
    }

    if(campo[l][c].numero!=0 && campo[l][c].mina==0){ // se o índice for um número, somente ele é revelado
        campo[l][c].status=1;
        return 0;
    }else if(campo[l][c].mina==1){ // se o índice for uma mina, ela é revelada e o jogo acaba
        campo[l][c].status=1;
        endgame = 1;
        printar(*campo);
        printf("GAME OVER! Voce acertou uma mina.\n");
        return 0;
    }else if(campo[l][c].numero==0){ // se o índice for vazio (0), ele é revelado e a função é aplicada em todas as 
        campo[l][c].status=1;        // 8 casas vizinhas de forma recursiva

        if(valid(l-1, c-1) && campo[l-1][c-1].status==0){
            revelar(l-1, c-1, campo);
        }
        if(valid(l-1, c) && campo[l-1][c].status==0){
            revelar(l-1, c, campo);
        }
        if(valid(l-1, c+1) && campo[l-1][c+1].status==0){
            revelar(l-1, c+1, campo);
        }
        if(valid(l, c-1) && campo[l][c-1].status==0){
            revelar(l, c-1, campo);
        }
        if(valid(l, c+1) && campo[l][c+1].status==0){
            revelar(l, c+1, campo);
        }
        if(valid(l+1, c-1) && campo[l+1][c-1].status==0){
            revelar(l+1, c-1, campo);
        }
        if(valid(l+1, c) && campo[l+1][c].status==0){
            revelar(l+1, c, campo);
        }
        if(valid(l+1, c+1) && campo[l+1][c+1].status==0){
            revelar(l+1, c+1, campo);
        }
    }
    return 0;
}
