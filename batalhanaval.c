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

int ataqueComputador(char tabuleiro[TAMANHO][TAMANHO], int acertos)
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

  } while (tabuleiro[linha][coluna] == 'E' || tabuleiro[linha][coluna] == 'A');

  if (tabuleiro[linha][coluna] == NAVIO)
  {
    printf("\n\tA CPU acertou em %c %d!\n", linha + 'A', coluna + 1);
    tabuleiro[linha][coluna] = ACERTO;
    armazenarVizinhos(linha, coluna);
    acertos++;
  }
  else
  {
    printf("\n\tA CPU errou em %c %d!\n", linha + 'A', coluna + 1);
    tabuleiro[linha][coluna] = ERRO;
  }

  return acertos;
}

int ataqueHumano(char tabuleiro[TAMANHO][TAMANHO], char tabuleiroVisivel[TAMANHO][TAMANHO], int acertos)
{
  char linhaAtaque;
  int colunaAtaque;
  printf("\n\t\x1b[34;40mEscolha onde deseja atacar o tabuleiro da CPU: (Coordenada X, Coordenada Y):\x1b[0m ");
  scanf("%c %d", &linhaAtaque, &colunaAtaque);
  linhaAtaque = toupper(linhaAtaque);
  
  if (colunaAtaque <= TAMANHO && linhaAtaque - 'A' < TAMANHO) {
    
    int castx = linhaAtaque - 'A';
    int casty = colunaAtaque - 1;
    if (tabuleiro[castx][casty] == NAVIO) {
      printf("\n\tO Jogador ACERTOU em %c %d!\n", linhaAtaque, colunaAtaque);
      tabuleiro[castx][casty] = ACERTO;
      tabuleiroVisivel[castx][casty] = ACERTO;
      acertos++;
  } else if (tabuleiro[castx][casty] == AGUA) {
    printf("\n\tO Jogador ERROU em %c %d!\n", linhaAtaque, colunaAtaque);
    tabuleiro[castx][casty] = ERRO;
    tabuleiroVisivel[castx][casty] = ERRO;
  } else if(tabuleiro[castx][casty] == ACERTO || tabuleiro[castx][casty] == ERRO) {
    printf("\n\t\x1b[30;41mCoordenada ja posicionada. Escolha outra.\x1b[0m\n");
  }
  } else {
    printf("\n\t\x1b[30;41mEssa posicao ultrapassa os limites do tabuleiro.\x1b[0m\n");
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

    printf("\n- - - Escolha a posicao dos NAVIOS - - -\n");
    printf("\nEscolha entre HORIZONTAL ou VERTICAL: (h / v) \n");
    scanf("%c", &orient);
    while (getchar() != '\n');

    orient = tolower(orient);
  
    if (orient == 'h') {
      printf("Digite a POSICAO do navio: (coordenada X (letra) e Y (numero) )\n");
      scanf("%c %d", &linhaNavioJogador, &colunaNavioJogador);
      while (getchar() != '\n');
      linhaNavioJogador = toupper(linhaNavioJogador);
      
      int castx = linhaNavioJogador - 'A';
      int casty = colunaNavioJogador - 1;
      if (!ultrapassaLimiteHorizontal(tam_navio, castx, casty) && colunaNavioJogador <= TAMANHO) {
        if (isValidoHorizontal(tabuleiro, tam_navio, castx, casty)) {
          for (int i = 0; i < tam_navio; i++)
          {
            tabuleiro[castx][casty + i] = NAVIO;
          }
          quantidadenavio++;
        }
        else {
          printf("\n\t\x1b[30;41mPosicao Invalida.\x1b[0m\n");
        }
      } else {
        printf("\n\t\x1b[30;41mPosicao Invalida.\x1b[0m\n");
      }
    } else if (orient == 'v') {
      printf("Digite a POSICAO do navio: (coordenada X (letra) e Y (numero) )\n");
      scanf("%c %d", &linhaNavioJogador, &colunaNavioJogador);
      while (getchar() != '\n');
      linhaNavioJogador = toupper(linhaNavioJogador);
      
      int castx = linhaNavioJogador - 'A';
      int casty = colunaNavioJogador - 1;
      if (!ultrapassaLimiteVertical(tam_navio, castx, casty) && colunaNavioJogador <= TAMANHO) {
        if (isValidoVertical(tabuleiro, tam_navio, castx, casty)) {
          for (int i = 0; i < tam_navio; i++)
          {
            tabuleiro[castx + i][casty] = NAVIO;
          }
          quantidadenavio++;  
        } else {
          printf("\n\t\x1b[30;41mPosicao Invalida.\x1b[0m\n");
        }
      } else {
        printf("\n\t\x1b[30;41mPosicao Invalida.\x1b[0m\n");
      }
    } else {
      printf("\n\t\x1b[30;41mEscolha uma orientacao valida.\x1b[0m\n");
    }
    printf("\n");
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

  int acertosJogador1 = 0, acertosComputador2 = 0;
  
  srand(time(NULL));

  inicializarTabuleiro(tabuleiroComputador1);
  inicializarTabuleiro(tabuleiroComputador2);
  inicializarTabuleiro(tabuleiroComputadorVisivel);

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

  iaPosicionaNavio(tabuleiroComputador2, tamPORTAVIAO, quantPORTAVIAO);
  iaPosicionaNavio(tabuleiroComputador2, tamNAVIOTANQUE, quantNAVIOTANQUE);
  iaPosicionaNavio(tabuleiroComputador2, tamCONTRATORPEDEIROS, quantCONTRATORPEDEIROS);
  iaPosicionaNavio(tabuleiroComputador2, tamSUBMARINO, quantSUBMARINO);
 
  printf("\nTabuleiro do Jogador:\n");
  imprimirTabuleiro(tabuleiroComputador1);

  printf("\n- - - Posicione os PORTA AVIOES [N][N][N][N][N] - - -\n");
  posicionarNavioHumano(tamPORTAVIAO, tabuleiroComputador1, quantPORTAVIAO);

  printf("\n- - - Posicione os NAVIOS TANQUE [N][N][N][N] - - -\n");
  posicionarNavioHumano(tamNAVIOTANQUE, tabuleiroComputador1, quantNAVIOTANQUE);

  printf("\n- - - Posicione os CONTRA-TORPEDEIROS [N][N][N] - - -\n");
  posicionarNavioHumano(tamCONTRATORPEDEIROS, tabuleiroComputador1, quantCONTRATORPEDEIROS);

  printf("\n- - - Posicione os SUBMARINOS [N][N] - - -\n");
  posicionarNavioHumano(tamSUBMARINO, tabuleiroComputador1, quantSUBMARINO);

  printf("\n\t\x1b[30;47mNavios posicionados. QUE O JOGO COMECE!\x1b[0m\n");

  clearscr();
  
  while (1)
  {
    
    printf("\n\tTabuleiro do Jogador:\n");
    imprimirTabuleiro(tabuleiroComputador1);
    printf("\n");
    printf("\tTabuleiro da CPU:\n");
    imprimirTabuleiro(tabuleiroComputadorVisivel);
    
    
    acertosJogador1 = ataqueHumano(tabuleiroComputador2, tabuleiroComputadorVisivel, acertosJogador1);

    if (acertosJogador1 == 25)
    {
      printf("\n\t\x1b[30;42m - - - - - - - - - - \n\x1b[0m\n");
      printf("\t\x1b[30;42m| O Jogador venceu! |\x1b[0m\n\n");
      printf("\t\x1b[30;42m - - - - - - - - - - \x1b[0m\n");
      imprimirTabuleiro(tabuleiroComputador2);
      break;
    }

    acertosComputador2 = ataqueComputador(tabuleiroComputador1, acertosComputador2);

    if (acertosComputador2 == 25)
    {
      printf("\n\t\x1b[30;42m - - - - - - - - \x1b[0m\n");
      printf("\t\x1b[30;42m| A CPU venceu! |\x1b[0m\n");
      printf("\t\x1b[30;42m - - - - - - - - \x1b[0m\n");
      imprimirTabuleiro(tabuleiroComputador2);
      break;
    }


    getchar();
  }
  return 0;
}
