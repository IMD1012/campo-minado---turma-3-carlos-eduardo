
#ifndef DEF
#define DEF

#include <time.h>

  // mude os números abaixos para alterar no programa inteiro
  int lt = 10, ct = 20, minas = 40;
  // lt = linhas totais, ct = colunas totais

  // definição de algumas variáveis globais necessárias para o programa, NÃO MEXER
  int endgame = 0, reveladas = 0, init1, init2, modo = 1, automode = 0, rodada = 1;
  time_t start,end;

#ifndef DEF
#define DEF

#include <time.h>

  // mude os números abaixos para alterar no programa inteiro
  // int lt = 10, ct = 20, minas = 40;
  // lt = linhas totais, ct = colunas totais

  // definição de algumas variáveis globais necessárias para o programa, NÃO MEXER
  //int endgame = 0, reveladas = 0, init1, init2, modo = 1, automode = 0, rodada = 1;


typedef struct{
    int status; // status de aberto(1)/fechado(0)
    int mina;   // status de é mina(1)/não é(0)
    int numero; // número correspondente a quantia de minas ao redor da casa
} campo;



#endif

typedef struct{
    int status; // status de aberto(1)/fechado(0)
    int mina;   // status de é mina(1)/não é(0)
    int numero; // número correspondente a quantia de minas ao redor da casa
} campo;



#endif