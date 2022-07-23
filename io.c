#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "definitions.h"
#include "funcs.h"
#include "io.h"

void initCampo(campo campo[10][20], int init1, int init2, int modo) {
  int i, j, lrand, crand;

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 20; j++) {
      campo[i][j].status = 0;
      campo[i][j].mina = 0;
      campo[i][j].numero = 0;
    }
  }
  i = 0;

  srand(time(NULL));
  while (i != 40) {
    lrand = rand() % 10;
    crand = rand() % 20;
    if (campo[lrand][crand].mina == 0) {
      campo[lrand][crand].mina = 1;
      i++;
      if (modo == 1) {
        if ((lrand == init1 && crand == init2) ||
            quantbombas(init1, init2, campo) != 0) {
          campo[lrand][crand].mina = 0;
          i--;
        }
      } else if (modo == 2) {
        if ((lrand == init1 && crand == init2) ||
            i == 40 && quantbombas(init1, init2, campo) == 0) {
          campo[lrand][crand].mina = 0;
          i--;
        }
      }
    }
  }

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 20; j++) {
      campo[i][j].numero = quantbombas(i, j, campo);
    }
  }
}

void printar(campo campo[10][20], int endgame) {
  int i, j, cont = 1;

  printf("\n   ");
  for (i = 0; i < 20; i++) {
    if (i < 10 && i == 20 - 1) {
      printf(" %d\n", i + 1);
    } else if (i == 20 - 1) {
      printf("%d\n", i + 1);
    } else if (i + 1 >= 10) {
      printf("%d ", i + 1);
    } else {
      printf(" %d ", i + 1);
    }
  }

  for (i = 0; i < 10; i++) {
    if (cont < 10) {
      printf(" %d", cont);
    } else {
      printf("%d", cont);
    }
    cont++;

    if (endgame == 0) {
      for (j = 0; j < 20; j++) {
        if (campo[i][j].status == 0) {
          printf("|__");
        } else {
          printf("|_%d", campo[i][j].numero);
        }
      }
    } else {
      for (j = 0; j < 20; j++) {
        if (campo[i][j].mina == 1) {
          printf("|_X");
        } else if (campo[i][j].status == 0) {
          printf("|__");
        } else {
          printf("|_%d", campo[i][j].numero);
        }
      }
    }
    printf("\n");
  }
}

int wincheck(campo campo[10][20], int endgame) {
  if (quantReveladas(campo) == (10 * 20) - 40) {
    endgame = 1;
    printar(campo, endgame);
    printf("Vitoria! Todas as minas foram evitadas.\n");
    return 1;
  }else{
    return 0;
  }
}

int sugerir_casa(campo campo[10][20], int endgame, int automode) {
  int sugl, sugc, temp, templ, tempc;
  float chance, chanceN = 100;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      temp = 100.00 / quantOcult(i, j, campo);
      chance = temp * campo[i][j].numero;
      if (campo[i][j].status == 1 && campo[i][j].numero > 0 &&
          quantOcult(i, j, campo) > campo[i][j].numero && chance < chanceN) {
        chanceN = chance;
        sugl = i;
        sugc = j;
      }
    }
  }
  printf("\n%.1f %% de chance de mina ao redor da casa %dx%d.\n", chanceN,
         sugl + 1, sugc + 1);

  templ = sugl;
  tempc = sugc;

  while (valid(sugl, sugc) == 0 || campo[sugl][sugc].status == 1) {
    sugl = templ;
    sugc = tempc;
    int lrand = rand() % 3 + 1;
    int crand = rand() % 3 + 1;

    if (lrand == 1) {
      sugl--;
    } else if (lrand == 3) {
      sugl++;
    }

    if (crand == 1) {
      sugc--;
    } else if (crand == 3) {
      sugc++;
    }
  }

  if (automode == 0) {
    printf("tente na casa %dx%d!\n", sugl + 1, sugc + 1);
    return 0;
  } else if (automode == 1) {
    printf("tentando na casa %dx%d!\n", sugl + 1, sugc + 1);
    endgame = revelar(sugl, sugc, campo, endgame);
  }
  return endgame;
}

void initJogo(campo campo[10][20], int automode, int modo) {
  int input1, input2, cont = 1, menu, rodada = 1, endgame = 0;
  time_t start, end;

  printf("   ");
  for (int i = 0; i < 20; i++) {
    if (i < 10 && i == 20 - 1) {
      printf(" %d\n", i + 1);
    } else if (i == 20 - 1) {
      printf("%d\n", i + 1);
    } else if (i + 1 >= 10) {
      printf("%d ", i + 1);
    } else {
      printf(" %d ", i + 1);
    }
  }
  for (int i = 0; i < 10; i++) {
    if (cont < 10) {
      printf(" %d", cont);
    } else {
      printf("%d", cont);
    }
    cont++;

    for (int j = 0; j < 20; j++) {
      printf("|__");
    }
    printf("\n");
  }

  if (automode == 0) {
    printf("Insira as coordenadas: ");
    scanf("%d %d", &input1, &input2);
    input1--;
    input2--;
    
    while (valid(input1, input2) == 0) {
      printf("Coordenada invalida! Tente outra.\n");
      scanf("%d %d", &input1, &input2);
      input1--;
      input2--;
    }
  }else{
    int lrand = rand() % 10;
    int crand = rand() % 20;

    input1 = lrand;
    input2 = crand;
    printf("Comecando com %dx%d.\n", input1 + 1, input2 + 1);
  }

  endgame = 0;
  initCampo(campo, input1, input2, modo);
  start = time(NULL);
  revelar(input1, input2, campo, endgame);

  while (endgame == 0 && wincheck(campo, endgame)==0) {

    if (automode == 0) {
      printar(campo, endgame);
      printf("Digite:\n1: Coordenadas\n2: Tempo de jogo/Rodada\n3: Sugestao\n");
      scanf("%d", &menu);
    } else {
      printar(campo, endgame);
      menu = 3;
      rodada++;
    }

    if (menu == 1) {
      printf("Insira as coordenadas: ");
      scanf("%d %d", &input1, &input2);
      input1--;
      input2--;
      if (valid(input1, input2) == 0) {
        printf("Coordenada invalida!\n");
      } else {
        rodada++;
        endgame = revelar(input1, input2, campo, endgame);
      }
    } else if (menu == 2) {
      end = time(NULL);
      printf("Tempo de jogo: %ld minutos e %ld segundos\n",(end-start)/60, (end - start)%60);
      printf("Rodadas: %d\n", rodada);
    } else if (menu == 3) {
      endgame = sugerir_casa(campo, endgame, automode);
    }
  }

  end = time(NULL);
  printf("Tempo de jogo: %ld minutos e %ld segundos\n",(end-start)/60, (end - start)%60);
  printf("Rodadas: %d\n", rodada);
}