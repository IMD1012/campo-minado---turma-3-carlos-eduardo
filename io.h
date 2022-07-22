
#ifndef IO
#define IO

#include "definitions.h"

void initCampo(campo[10][20], int, int, int);
void printar(campo[10][20], int);
void wincheck(campo[10][20], int, int);
void sugerir_casa(campo[10][20], int, int, int, int);
void initJogo(campo[10][20], time_t, time_t, int, int, int, int, int, int);

#endif