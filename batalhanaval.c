/** clibs **/

#include "defines.h"
#include "ia.h"
#include "verify.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
  printf("\t");
  for (int i = 0; i < TAMANHO; i++)
  {
    printf("%d  ", i + 1);
  }
  printf("\n");

  for (int i = 0; i < TAMANHO; i++)
  {
    printf("%c\t", 'A' + i);
    for (int j = 0; j < TAMANHO; j++)
    {
      printf("%c  ", tabuleiro[i][j]);
    }
    printf("\n");
  }
}

void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
  for (int i = 0; i < TAMANHO; i++) {
    for (int j = 0; j < TAMANHO; j++) {
      tabuleiro[i][j] = AGUA;
    }
  }
}

int ataqueComputador(char tabuleiro[TAMANHO][TAMANHO], int acertos, int cpu)
{
  int linha, coluna;

  do
  {
    linha = 'A' + rand() % TAMANHO;
    coluna = rand() % TAMANHO;
  } while (tabuleiro[linha - 'A'][coluna] == 'E' || tabuleiro[linha - 'A'][coluna] == 'A');

  if (tabuleiro[linha - 'A'][coluna] == NAVIO)
  {
    printf("Computador %d acertou em %c %d!\n", cpu, linha, coluna + 1);
    tabuleiro[linha - 'A'][coluna] = ACERTO;
    acertos++;
  }
  else
  {
    printf("Computador %d errou em %c %d!\n", cpu, linha, coluna + 1);
    tabuleiro[linha - 'A'][coluna] = ERRO;
  }

  return acertos;
}

int ataqueHumano(char tabuleiro[TAMANHO][TAMANHO], char tabuleiroVisivel[TAMANHO][TAMANHO], char linhaDeAtaque, int colunaDeAtaque, int acertos)
{
  linhaDeAtaque = toupper(linhaDeAtaque);
  if (tabuleiro[linhaDeAtaque - 'A'][colunaDeAtaque - 1] == NAVIO)
  {
    printf("O Jogador ACERTOU em %c %d!\n", linhaDeAtaque, colunaDeAtaque);
    tabuleiroVisivel[linhaDeAtaque - 'A'][colunaDeAtaque - 1] = ACERTO;
    acertos++;
  }
  else
  {
    printf("O Jogador ERROU em %c %d!\n", linhaDeAtaque, colunaDeAtaque);
    tabuleiroVisivel[linhaDeAtaque - 'A'][colunaDeAtaque - 1] = ERRO;
  }

  return acertos;
}

void posicionarNavioHumano(int tam_navio, char tabuleiro[][TAMANHO], int quantidade)
{
  int quantidadenavio = 0;
  do
  {
    char linhaNavioJogador; //letra
    char orient;          
    int colunaNavioJogador; //numero

    printf("-----Escolha a posicao dos NAVIOS-----\n");
    printf("Escolha entre HORIZONTAL ou VERTICAL: (h / v)\n");
    scanf("%c", &orient);
    while (getchar() != '\n');

    orient = tolower(orient);

    printf("Digite a POSICAO do navio: (coordenada X e Y)\n");
    scanf("%c %d", &linhaNavioJogador, &colunaNavioJogador);
    while (getchar() != '\n');
    linhaNavioJogador = toupper(linhaNavioJogador);

    if (orient == 'h') {
      int castx = linhaNavioJogador - 'A';
      int casty = colunaNavioJogador - 1;

      if (!ultrapassaLimiteHorizontal(tam_navio, castx, casty)) { //maybe the function
        if (isValidoHorizontal(tabuleiro, tam_navio, castx, casty)) {
          for (int i = 0; i < tam_navio; i++)
          {
            tabuleiro[castx][casty+i] = NAVIO;
          }
          quantidadenavio++;
        }
        else {
          printf("Posicao Invalida.\n");
        }
      } else {
        printf("Posicao Invalida.\n");
      }
    }
    else if (orient == 'v')
    {
      if (!ultrapassaLimiteVertical(tam_navio, linhaNavioJogador - 'A', colunaNavioJogador - 1)) {
        if (isValidoVertical(tabuleiro, tam_navio, (linhaNavioJogador - 'A'), (colunaNavioJogador - 1)))
        {
          for (int i = 0; i < tam_navio; i++)
          {
            tabuleiro[(linhaNavioJogador - 'A') + i][colunaNavioJogador - 1] = NAVIO;
           
              
          }
          quantidadenavio++;  
        }
        else
        {
          printf("Posicao Invalida.\n");
        }
      }
    }
    imprimirTabuleiro(tabuleiro);
  } while (quantidadenavio < quantidade);
}

void clearscr(void) {
  printf("\x1b[2J");
  printf("\x1b[H");
}

int main()
{
  char tabuleiroComputador1[TAMANHO][TAMANHO];
  char tabuleiroComputador2[TAMANHO][TAMANHO];
  char tabuleiroComputadorVisivel[TAMANHO][TAMANHO];

  int acertosJogador1 = 0, acertosComputador2 = 0, colunaAtaque;
  char linhaAtaque;
  srand(time(NULL));

  inicializarTabuleiro(tabuleiroComputador1);
  inicializarTabuleiro(tabuleiroComputador2);
  inicializarTabuleiro(tabuleiroComputadorVisivel);

  //clearscr();

  printf("----------------------------------------------------\n");
  printf("| Escolha a posicao dos seus navios no tabuleiro   |\n");
  printf("| Voce tem 5 navios disponiveis:                   |\n");
  printf("| Sendo eles:                                      |\n");
  printf("| 1 Porta-Aviao [N][N][N][N][N]                    |\n");
  printf("| 2 Contra-Torpedeiros [N][N][N]                   |\n");
  printf("| 2 Navios Tanque [N][N][N][N]                     |\n");
  printf("| 3 Submarinos [N][N]                              |\n");
  printf("----------------------------------------------------\n");
  printf("\n-----OBS: os navios DEVEM ter pelo menos UM quadrado de distancia um dos outros e NAO PODEM se sobrepor-----\n");
  printf("\n-----OBS: os navios nao podem ser colocados DIAGONALMENTE-----\n");

  iaPosicionaNavio(tabuleiroComputador2, tamPORTAVIAO, quantPORTAVIAO);
  iaPosicionaNavio(tabuleiroComputador2, tamNAVIOTANQUE, quantNAVIOTANQUE);
  iaPosicionaNavio(tabuleiroComputador2, tamCONTRATORPEDEIROS, quantCONTRATORPEDEIROS);
  iaPosicionaNavio(tabuleiroComputador2, tamSUBMARINO, quantSUBMARINO);
 
  printf("\nTabuleiro do Jogador:\n");
  imprimirTabuleiro(tabuleiroComputador1);

  printf("\n-----Posicione os PORTA AVIOES [N][N][N][N][N] -----\n");
  posicionarNavioHumano(tamPORTAVIAO, tabuleiroComputador1, quantPORTAVIAO);

  printf("\n-----Posicione os NAVIOS TANQUE [N][N][N][N] -----\n");
  posicionarNavioHumano(tamNAVIOTANQUE, tabuleiroComputador1, quantNAVIOTANQUE);

  printf("\n-----Posicione os CONTRA-TORPEDEIROS [N][N][N] -----\n");
  posicionarNavioHumano(tamCONTRATORPEDEIROS, tabuleiroComputador1, quantCONTRATORPEDEIROS);

  printf("\n-----Posicione os SUBMARINOS [N][N] -----\n");
  posicionarNavioHumano(tamSUBMARINO, tabuleiroComputador1, quantSUBMARINO);

  putchar('\n');

  while (1)
  {
    printf("Tabuleiro do Jogador:\n");
    imprimirTabuleiro(tabuleiroComputador1);
    printf("\n");
    printf("Tabuleiro do Computador:\n");
    imprimirTabuleiro(tabuleiroComputador2);
    printf("Escolha onde deseja atacar o tabuleiro do computador: (Coordenada X, Coordenada Y): ");
    scanf("%c %d", &linhaAtaque, &colunaAtaque);

    acertosJogador1 = ataqueHumano(tabuleiroComputador2, tabuleiroComputadorVisivel, linhaAtaque, colunaAtaque, acertosJogador1);

    if (acertosJogador1 == 13)
    {
      printf("O Jogador venceu! \n");
      imprimirTabuleiro(tabuleiroComputador2);
      break;
    }

    acertosComputador2 = ataqueComputador(tabuleiroComputador1, acertosComputador2, 2);

    if (acertosComputador2 == 13)
    {
      printf("Computador 2 venceu! \n");
      imprimirTabuleiro(tabuleiroComputador1);
      break;
    }

    getchar();
  }
  return 0;
}