#ifndef _H_VERIFY
#define _H_VERIFY

#include "defines.h"

int isEqual(char obj1, char obj2);
int ultrapassaLimiteHorizontal(int tam, int x, int y);
int ultrapassaLimiteVertical(int tam, int x, int y);
int isValidoHorizontal(char tabuleiro[TAMANHO][TAMANHO], int tam, int x, int y);
int isValidoVertical(char tabuleiro[TAMANHO][TAMANHO], int tam, int x, int y);

#endif