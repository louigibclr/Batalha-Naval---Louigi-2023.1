#include "defines.h"
#include "verify.h"

#include <stdlib.h>

#define HORIZONTAL 0
#define VERTICAL 1

void iaPosicionaNavio(char tabuleiro[][TAMANHO], int tam, int qtde) {
  int x, y; // COORDENADAS
  for (int i = 0; i < qtde; i++) {
    int orient = rand() % 2, xlimit, ylimit;

    if (orient == HORIZONTAL)
    {
      xlimit = TAMANHO;
      ylimit = TAMANHO - tam + 1;
      do
      {
        x = rand() % xlimit;
        y = rand() % ylimit;
      } while (!isValidoHorizontal(tabuleiro, tam, x, y));
    }
    else if (orient == VERTICAL)
    {
      xlimit = TAMANHO - tam + 1;
      ylimit = TAMANHO;
      do
      {
        x = rand() % xlimit;
        y = rand() % ylimit;
      } while (!isValidoVertical(tabuleiro, tam, x, y));
    }

    for (int j = 0; j < tam; j++)
    {
      if (orient == HORIZONTAL)
        tabuleiro[x][y + j] = NAVIO;
      else
        tabuleiro[x + j][y] = NAVIO;
    }
  }
}