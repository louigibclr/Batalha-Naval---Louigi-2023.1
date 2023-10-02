/** clibs **/

#include "defines.h"
#include "ia.h"
#include "verify.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int posicoesVizinhas[32];
int totalDePosicoesVizinhas = -1;

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

void imprimirTabuleiroIA(char tabuleiro[TAMANHO][TAMANHO])
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
      printf("%c  ", (tabuleiro[i][j] == ERRO || tabuleiro[i][j] == ACERTO) ? tabuleiro[i][j] : AGUA);
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

void armazenarVizinhos(int linha, int coluna)
{
  if((linha - 1) >= 0)
  {
    posicoesVizinhas[++totalDePosicoesVizinhas] = linha - 1;
    posicoesVizinhas[++totalDePosicoesVizinhas] = coluna;
  }

  if((coluna - 1) >= 0)
  {
    posicoesVizinhas[++totalDePosicoesVizinhas] = linha;
    posicoesVizinhas[++totalDePosicoesVizinhas] = coluna - 1;
  }

  if((linha + 1) <= (TAMANHO - 1))
  {
    posicoesVizinhas[++totalDePosicoesVizinhas] = linha + 1;
    posicoesVizinhas[++totalDePosicoesVizinhas] = coluna;
  }


  if((coluna + 1) <= (TAMANHO - 1))
  {
    posicoesVizinhas[++totalDePosicoesVizinhas] = linha;
    posicoesVizinhas[++totalDePosicoesVizinhas] = coluna + 1;
  }
}

int ataqueComputador(char tabuleiroHumano[TAMANHO][TAMANHO], int acertos)
{
  int linha, coluna;

  do 
  {
    if(totalDePosicoesVizinhas < 0) {
      linha  = rand() % TAMANHO;
      coluna = rand() % TAMANHO;
    }
    else
    {
      coluna = posicoesVizinhas[totalDePosicoesVizinhas--];
      linha = posicoesVizinhas[totalDePosicoesVizinhas--];
    }

  } while (tabuleiroHumano[linha][coluna] == 'E' || tabuleiroHumano[linha][coluna] == 'A');

  if (tabuleiroHumano[linha][coluna] == NAVIO)
  {
    printf("\n\tComputador acertou em %c %d!\n", linha + 'A', coluna + 1);
    tabuleiroHumano[linha][coluna] = ACERTO;
    armazenarVizinhos(linha, coluna);
    acertos++;
  }
  else
  {
    printf("\n\tComputador errou em %c %d!\n", linha + 'A', coluna + 1);
    tabuleiroHumano[linha][coluna] = ERRO;
  }

  return acertos;
}

int ataqueHumano(char tabuleiroCPU[TAMANHO][TAMANHO], int acertos)
{
  char linhaDeAtaque;
  int colunaDeAtaque;

  printf("\n\t\x1b[34;40mEscolha onde deseja atacar o tabuleiro da CPU: (Coordenada X, Coordenada Y):\x1b[0m ");
  scanf("%c %d", &linhaDeAtaque, &colunaDeAtaque);
  while(getchar() != '\n');

  linhaDeAtaque = toupper(linhaDeAtaque);

  if (colunaDeAtaque <= TAMANHO && linhaDeAtaque - 'A' < TAMANHO && colunaDeAtaque > 0 && (linhaDeAtaque - 'A') >= 0) {
    int castx = linhaDeAtaque - 'A';
    int casty = colunaDeAtaque - 1;
    
    if (tabuleiroCPU[castx][casty] == NAVIO)
    {
      printf("\n\tO Jogador ACERTOU em %c %d!\n", linhaDeAtaque, colunaDeAtaque);
      tabuleiroCPU[castx][casty] = ACERTO;
      acertos++;
    }
    else if(tabuleiroCPU[castx][casty] == AGUA)
    {
      printf("\n\tO Jogador ERROU em %c %d!\n", linhaDeAtaque, colunaDeAtaque);
      tabuleiroCPU[castx][casty] = ERRO;
    } 
    else {
      printf("\n\t\x1b[30;41mCoordenada ja posicionada. Escolha outra.\x1b[0m\n");
      ataqueHumano(tabuleiroCPU, acertos);
    }
  }
  else {
    printf("\n\t\x1b[30;41mEssa posicao ultrapassa os limites do tabuleiro.\x1b[0m\n");
    ataqueHumano(tabuleiroCPU, acertos);
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

    printf("\n-----Escolha a posicao dos NAVIOS-----\n");
    printf("\nEscolha entre HORIZONTAL ou VERTICAL: (h / v)\n");
    scanf("%c", &orient);
    while (getchar() != '\n');

    orient = tolower(orient);

    if(orient != 'v' && orient != 'h') {
      printf("\n\t\x1b[30;41mEscolha uma orientacao valida.\x1b[0m\n");
    }
    else {
      printf("Digite a POSICAO do navio: (coordenada X e Y)\n");
      scanf("%c %d", &linhaNavioJogador, &colunaNavioJogador);
      while (getchar() != '\n');
      linhaNavioJogador = toupper(linhaNavioJogador);

      int castx = linhaNavioJogador - 'A';
      int casty = colunaNavioJogador - 1;
      if (orient == 'h') {
        if (!ultrapassaLimiteHorizontal(tam_navio, castx, casty)) { //maybe the function
          if (isValidoHorizontal(tabuleiro, tam_navio, castx, casty)) {
            for (int i = 0; i < tam_navio; i++)
            {
              tabuleiro[castx][casty+i] = NAVIO;
            }
            quantidadenavio++;
          }
          else {
            printf("\n\t\x1b[30;41mPosicao Invalida.\x1b[0m\n");
          }
        } else {
          printf("\n\t\x1b[30;41mPosicao Invalida.\x1b[0m\n");
        }
      }
      else if (orient == 'v')
      {
        if (!ultrapassaLimiteVertical(tam_navio, castx, casty)) {
          if (isValidoVertical(tabuleiro, tam_navio, castx, casty))
          {
            for (int i = 0; i < tam_navio; i++)
            {
              tabuleiro[castx + i][casty] = NAVIO;   
            }
            quantidadenavio++;  
          }
          else
          {
            printf("\n\t\x1b[30;41mPosicao Invalida.\x1b[0m\n");
          }
        }
        else {
          printf("\n\t\x1b[30;41mPosicao Invalida.\x1b[0m\n");
        }
      }
      imprimirTabuleiro(tabuleiro);
    }
  } while (quantidadenavio < quantidade);
}

void clearscr(void) {
  printf("\x1b[2J");
  printf("\x1b[H");
}

int main()
{
  char tabuleiroHumano[TAMANHO][TAMANHO];
  char tabuleiroCPU[TAMANHO][TAMANHO];

  int acertosJogador1 = 0, acertosComputador2 = 0, colunaAtaque;
  char linhaAtaque;
  srand(time(NULL));

  inicializarTabuleiro(tabuleiroHumano);
  inicializarTabuleiro(tabuleiroCPU);

  //clearscr();

  printf("\n----------------------------------------------------\n");
  printf("\n| Escolha a posicao dos seus navios no tabuleiro   |\n");
  printf("\n| Voce tem 5 navios disponiveis:                   |\n");
  printf("\n| Sendo eles:                                      |\n");
  printf("\n| 1 Porta-Aviao [N][N][N][N][N]                    |\n");
  printf("\n| 2 Navios Tanque [N][N][N][N]                     |\n");
  printf("\n| 2 Contra-Torpedeiros [N][N][N]                   |\n");
  printf("\n| 3 Submarinos [N][N]                              |\n");
  printf("\n----------------------------------------------------\n");
  
  iaPosicionaNavio(tabuleiroCPU, tamPORTAVIAO, quantPORTAVIAO);
  iaPosicionaNavio(tabuleiroCPU, tamNAVIOTANQUE, quantNAVIOTANQUE);
  iaPosicionaNavio(tabuleiroCPU, tamCONTRATORPEDEIROS, quantCONTRATORPEDEIROS);
  iaPosicionaNavio(tabuleiroCPU, tamSUBMARINO, quantSUBMARINO);
 
  printf("\nTabuleiro do Jogador:\n");
  imprimirTabuleiro(tabuleiroHumano);

  printf("\n-----Posicione os PORTA AVIOES [N][N][N][N][N] -----\n");
  posicionarNavioHumano(tamPORTAVIAO, tabuleiroHumano, quantPORTAVIAO);

  printf("\n-----Posicione os NAVIOS TANQUE [N][N][N][N] -----\n");
  posicionarNavioHumano(tamNAVIOTANQUE, tabuleiroHumano, quantNAVIOTANQUE);

  printf("\n-----Posicione os CONTRA-TORPEDEIROS [N][N][N] -----\n");
  posicionarNavioHumano(tamCONTRATORPEDEIROS, tabuleiroHumano, quantCONTRATORPEDEIROS);

  printf("\n-----Posicione os SUBMARINOS [N][N] -----\n");
  posicionarNavioHumano(tamSUBMARINO, tabuleiroHumano, quantSUBMARINO);

  printf("\n\t\x1b[30;47mNavios posicionados. QUE O JOGO COMECE!\x1b[0m\n");
  do
  {
    clearscr();
    printf("Tabuleiro do Jogador:\n");
    imprimirTabuleiro(tabuleiroHumano);
    printf("\n");
    printf("Tabuleiro do Computador:\n");
    imprimirTabuleiroIA(tabuleiroCPU);

    acertosJogador1 = ataqueHumano(tabuleiroCPU, acertosJogador1);
    acertosComputador2 = ataqueComputador(tabuleiroHumano, acertosComputador2);

    printf("\nPressione enter para continuar ...");
    getchar();
  }
  while(acertosJogador1 < 25 && acertosComputador2 < 25);

  if (acertosJogador1 == 25)
  {
    printf("O Jogador venceu! \n");
    printf("\n\t\x1b[30;42m - - - - - - - - - - \n\x1b[0m\n");
    printf("\t\x1b[30;42m| O Jogador venceu! |\x1b[0m\n\n");
    printf("\t\x1b[30;42m - - - - - - - - - - \x1b[0m\n");
    imprimirTabuleiro(tabuleiroCPU);
  }

  if (acertosComputador2 == 25)
  {
    printf("\n\t\x1b[30;42m - - - - - - - - \x1b[0m\n");
    printf("\t\x1b[30;42m| A CPU venceu! |\x1b[0m\n");
    printf("\t\x1b[30;42m - - - - - - - - \x1b[0m\n");
    imprimirTabuleiro(tabuleiroHumano);
  }

  return 0;
}
