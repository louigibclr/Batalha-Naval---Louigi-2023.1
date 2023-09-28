#include "defines.h"

int isEqual(char obj1, char obj2) {
  return obj1 == obj2;
}

int ultrapassaLimiteHorizontal(int tam, int x, int y) {
  /** retorna verdadeiro se nao ultrapassa o liimite*/
  int xlimit = TAMANHO;
  int ylimit = TAMANHO - tam + 1;

  if(x >= xlimit || y >= ylimit) return 1;
  
  return 0;
}

int ultrapassaLimiteVertical(int tam, int x, int y)
{
  int xlimit = TAMANHO - tam + 1;
  int ylimit = TAMANHO;
  
  if(x >= xlimit || y >= ylimit) return 1;
  
  return 0;
}

int isValidoHorizontal(char tabuleiro[TAMANHO][TAMANHO], int tam, int x, int y)
{
  for (int i = 0; i < tam; i++)
  {
    if (!isEqual(tabuleiro[x][y + i], AGUA))
    {
      return 0;
    }
  }

  return 1;
}

int isValidoVertical(char tabuleiro[TAMANHO][TAMANHO], int tam, int x, int y)
{
  for (int i = 0; i < tam; i++)
  {
    if (!isEqual(tabuleiro[x + i][y], AGUA))
    {
      return 0;
    }
  }

  return 1;
}