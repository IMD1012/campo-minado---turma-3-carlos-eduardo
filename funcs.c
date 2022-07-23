#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"
#include "funcs.h"
#include "io.h"

int valid(int l, int c) {
  if (l >= 0 && l < 10 && c >= 0 && c < 20) {
    return 1;
  } else {
    return 0;
  }
}

int quantbombas(int l, int c, campo campo[10][20]) {
  int n = 0;
  
  for(int i=l-1;i<l+2;i++){
      for(int j=c-1;j<c+2;j++){
        if(valid(i, j) && campo[i][j].mina==1){
          n++;
        }
      }
    }

  return n;
}

int quantOcult(int l, int c, campo campo[10][20]) {
  int n = 0;

  for(int i=l-1;i<l+2;i++){
      for(int j=c-1;j<c+2;j++){
        if(valid(i, j) && campo[i][j].status==0){
          n++;
        }
      }
    }

  return n;
}

int quantReveladas(campo campo[10][20]){
  int contagem = 0;
  
  for(int i=0;i<10;i++){
    for(int j=0;j<20;j++){
      if(campo[i][j].status==1){
        contagem++;
      }
    }
  }

  return contagem;
}

int revelar(int l, int c, campo campo[10][20], int endgame) {

  if (campo[l][c].status == 1) {
    printf("Coordenada ja revelada.\n");
    return 0;
  }

  if (campo[l][c].numero != 0 && campo[l][c].mina == 0) {
    campo[l][c].status = 1;
    return 0;
  } else if (campo[l][c].mina == 1) {
    endgame = 1;
    campo[l][c].status = 1;
    printar(campo, endgame);
    printf("GAME OVER! Voce acertou uma mina.\n");
    return 1;
  } else if (campo[l][c].numero == 0) {
    campo[l][c].status = 1;

    for(int i=l-1;i<l+2;i++){
      for(int j=c-1;j<c+2;j++){
        if(valid(i, j) && campo[i][j].status==0){
          revelar(i, j, campo, endgame);
        }
      }
    }
  
  }
  return 0;
}