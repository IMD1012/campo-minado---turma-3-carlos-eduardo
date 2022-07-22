#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "funcs.h"
#include "definitions.h"
#include "io.h"

int valid(int l, int c){
    if(l>=0 && l<10 && c>=0 && c<20){
        return 1;
    }else{
        return 0;
    }
}

int quantbombas(int l, int c, campo campo[10][20]){
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

int quantOcult(int l, int c, campo campo[10][20]){
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

int revelar(int l, int c, campo campo[10][20], int reveladas, int endgame){
 
    if(campo[l][c].status==0 && campo[l][c].mina!=1){
        reveladas++;
    }else if(campo[l][c].status==1){
        printf("Coordenada ja revelada.\n");
    }

    if(campo[l][c].numero!=0 && campo[l][c].mina==0){
        campo[l][c].status=1;
        return 0;
    }else if(campo[l][c].mina==1){
        campo[l][c].status=1;
        endgame = 1;
        printar(campo, endgame);
        printf("GAME OVER! Voce acertou uma mina.\n");
        return 0;
    }else if(campo[l][c].numero==0){ 
        campo[l][c].status=1;

        if(valid(l-1, c-1) && campo[l-1][c-1].status==0){
            revelar(l-1, c-1, campo, reveladas, endgame);
        }
        if(valid(l-1, c) && campo[l-1][c].status==0){
            revelar(l-1, c, campo, reveladas, endgame);
        }
        if(valid(l-1, c+1) && campo[l-1][c+1].status==0){
            revelar(l-1, c+1, campo, reveladas, endgame);
        }
        if(valid(l, c-1) && campo[l][c-1].status==0){
            revelar(l, c-1, campo, reveladas, endgame);
        }
        if(valid(l, c+1) && campo[l][c+1].status==0){
            revelar(l, c+1, campo, reveladas, endgame);
        }
        if(valid(l+1, c-1) && campo[l+1][c-1].status==0){
            revelar(l+1, c-1, campo, reveladas, endgame);
        }
        if(valid(l+1, c) && campo[l+1][c].status==0){
            revelar(l+1, c, campo, reveladas, endgame);
        }
        if(valid(l+1, c+1) && campo[l+1][c+1].status==0){
            revelar(l+1, c+1, campo, reveladas, endgame);
        }
    }
    return 0;
}
