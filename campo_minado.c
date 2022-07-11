#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int status;
    int bomba;
    int numero;
}campo;

void init(int l, int c, campo campo[l][c]){
    int i, j;
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            campo[i][j].status = 0;
            campo[i][j].bomba = 0;
            campo[i][j].numero = 0;
        }
    }
}

void bombas(int l, int c, campo campo[l][c]){
    int i=0, lrand, crand;
    srand(time(NULL));
    while(i!=40){
        lrand = rand()%10;
        crand = rand()%20;
        if(campo[lrand][crand].bomba == 0){
            campo[lrand][crand].bomba = 1;
            i++;
        }
    }
}

void printar(int l, int c, campo campo[l][c]){
    int i, j, cont = 0;
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            printf("%d ", campo[i][j].bomba);
        }
        printf("\n");
    }
}

int main(){
    int l = 10, c = 20;
    campo oculto[l][c];

    init(l, c, oculto);
    bombas(l, c, oculto);
    printar(l, c, oculto);

    return 0;
}