#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define TAMANHO 10
#define NAVIOS 5

#define AGUA '~'
#define NAVIO 'N'

#define ERRO 'E'
#define ACERTO 'A'

#define quantPORTAVIAO 1
#define quantCONTRATORPEDEIROS 2
#define quantNAVIOTANQUE 2
#define quantSUBMARINO 3

#define tamPORTAVIAO 5
#define tamSUBMARINO 2
#define tamCONTRATORPEDEIROS 3
#define tamNAVIOTANQUE 4

int isEqual(int obj1, int obj2)
{
  return obj1 == obj2;
}

int isValidoHorizontal(char tabuleiro[TAMANHO][TAMANHO], int tam, int x, int y)
{
  int xlimit, ylimit;
  xlimit = TAMANHO;
  ylimit = TAMANHO - tam + 1;
  for (int i = 0; i < tam; i++)
  {
    if (!isEqual(tabuleiro[x][y + i], AGUA))
    {
      return 0;
    } else if (x > xlimit || y + i > ylimit ) 
    {
      return 0;
    } 
  }

  return 1;
}

int isValidoVertical(char tabuleiro[TAMANHO][TAMANHO], int tam, int x, int y)
{
  int xlimit, ylimit;
  xlimit = TAMANHO - tam + 1;
  ylimit = TAMANHO;
  for (int i = 0; i < tam; i++)
  {
    if (!isEqual(tabuleiro[x + i][y], AGUA))
    {
      return 0;
    } else if (x + i > xlimit || y > ylimit ) 
    {
      return 0;
    } 
  }

  return 1;
}

void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
  printf("      ");
  for (int i = 0; i < TAMANHO; i++)
  {
    printf("%d  ", i + 1);
  }
  printf("\n");

  for (int i = 0; i < TAMANHO; i++)
  {
    // printf("%d  ", i);
    printf("%c     ", 'A' + i);
    for (int j = 0; j < TAMANHO; j++)
    {
      printf("%c  ", tabuleiro[i][j]);
    }
    printf("\n");
  }
}

void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
  for (int i = 0; i < TAMANHO; i++)
  {
    for (int j = 0; j < TAMANHO; j++)
    {
      tabuleiro[i][j] = AGUA;
    }
  }
}

void posicionarContraTorpedeiro(char tabuleiro[TAMANHO][TAMANHO])
{
  int x, y; // COORDENADAS
  for (int i = 0; i < quantCONTRATORPEDEIROS; i++)
  {
    int orient = rand() % 2, xlimit, ylimit;

    if (orient == 0)
    {
      xlimit = TAMANHO;
      ylimit = TAMANHO - tamPORTAVIAO + 1;
      do
      {
        x = rand() % xlimit;
        y = rand() % ylimit;
      } while (!isValidoHorizontal(tabuleiro, tamPORTAVIAO, x, y));
    }
    else if (orient == 1)
    {
      xlimit = TAMANHO - tamPORTAVIAO + 1;
      ylimit = TAMANHO;
      do
      {
        x = rand() % xlimit;
        y = rand() % ylimit;
      } while (!isValidoVertical(tabuleiro, tamPORTAVIAO, x, y));
    }

    for (int j = 0; j < tamCONTRATORPEDEIROS; j++)
    {
      if (orient == 0)
        tabuleiro[x][y + j] = NAVIO;
      else
        tabuleiro[x + j][y] = NAVIO;
    }
  }
}

void posicionarNavioTanque(char tabuleiro[TAMANHO][TAMANHO])
{
  int x, y;

  for (int i = 0; i < quantNAVIOTANQUE; i++)
  {
    int orient = rand() % 2, xlimit, ylimit;

    if (orient == 0)
    {
      xlimit = TAMANHO;
      ylimit = TAMANHO - tamPORTAVIAO + 1;
      do
      {
        x = rand() % xlimit;
        y = rand() % ylimit;
      } while (!isValidoHorizontal(tabuleiro, tamPORTAVIAO, x, y));
    }
    else if (orient == 1)
    {
      xlimit = TAMANHO - tamPORTAVIAO + 1;
      ylimit = TAMANHO;
      do
      {
        x = rand() % xlimit;
        y = rand() % ylimit;
      } while (!isValidoVertical(tabuleiro, tamPORTAVIAO, x, y));
    }

    for (int j = 0; j < tamNAVIOTANQUE; j++)
    {
      if (orient == 0)
        tabuleiro[x][y + j] = NAVIO;
      else
        tabuleiro[x + j][y] = NAVIO;
    }
  }
}

void posicionarPortaAviao(char tabuleiro[TAMANHO][TAMANHO])
{
  int x, y;

  for (int i = 0; i < quantPORTAVIAO; i++)
  {
    int orient = rand() % 2, xlimit, ylimit;

    if (orient == 0)
    {
      xlimit = TAMANHO;
      ylimit = TAMANHO - tamPORTAVIAO + 1;
      do
      {
        x = rand() % xlimit;
        y = rand() % ylimit;
      } while (!isValidoHorizontal(tabuleiro, tamPORTAVIAO, x, y));
    }
    else if (orient == 1)
    {
      xlimit = TAMANHO - tamPORTAVIAO + 1;
      ylimit = TAMANHO;
      do
      {
        x = rand() % xlimit;
        y = rand() % ylimit;
      } while (!isValidoVertical(tabuleiro, tamPORTAVIAO, x, y));
    }

    for (int j = 0; j < tamPORTAVIAO; j++)
    {
      if (orient == 0)
        tabuleiro[x][y + j] = NAVIO;
      else
        tabuleiro[x + j][y] = NAVIO;
    }
  }
}

void posicionarSubmarino(char tabuleiro[TAMANHO][TAMANHO])
{
  int x, y;
  for (int i = 0; i < quantSUBMARINO; i++)
  {

    do
    {
      x = rand() % TAMANHO;
      y = rand() % TAMANHO;
    } while (!isValidoVertical(tabuleiro, tamSUBMARINO, x, y) && !isValidoHorizontal(tabuleiro, tamSUBMARINO, x, y));

    tabuleiro[x][y] = NAVIO;
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

void posicionarNavioHumano(int tam_navio, char tabuleiro[TAMANHO][TAMANHO], int quantidade)
{
  int quantidadenavio = 0;
  do
  {
    char linhaNavioJogador;
    char escolha;
    int colunaNavioJogador;
    int temp = 0;

    printf("-----Escolha a posicao dos NAVIOS-----\n");
    printf("Escolha entre HORIZONTAL ou VERTICAL: (h / v)\n");
    scanf("%c", &escolha);
    while (getchar() != '\n');

    escolha = tolower(escolha);

    printf("Digite a POSICAO do navio: (coordenada X e Y)\n");
    scanf("%c %d", &linhaNavioJogador, &colunaNavioJogador);
    while (getchar() != '\n');
    linhaNavioJogador = toupper(linhaNavioJogador);

    if (escolha == 'h')
    {
      if (isValidoHorizontal(tabuleiro, tam_navio, (linhaNavioJogador - 'A'), (colunaNavioJogador - 1)))
      {
        for (int i = 0; i < tam_navio; i++)
        {
          tabuleiro[linhaNavioJogador - 'A'][(colunaNavioJogador - 1) + i] = NAVIO;
          temp++;
          if (temp == tam_navio)
            quantidadenavio++;
        }
      }
      else
      {
        printf("Posicao Invalida.\n");
      }
      imprimirTabuleiro(tabuleiro);
    }
    else if (escolha == 'v')
    {
      if (isValidoVertical(tabuleiro, tam_navio, (linhaNavioJogador - 'A'), (colunaNavioJogador - 1)))
      {
        for (int i = 0; i < tam_navio; i++)
        {
          tabuleiro[(linhaNavioJogador - 'A') + i][colunaNavioJogador - 1] = NAVIO;
          temp++;
          if (temp == tam_navio)
          quantidadenavio++;
        }
        imprimirTabuleiro(tabuleiro);
      }
      else
      {
        printf("Posicao Invalida.\n");
      }
    }
  } while (quantidadenavio != quantidade);
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

  posicionarContraTorpedeiro(tabuleiroComputador2);
  posicionarNavioTanque(tabuleiroComputador2);
  posicionarSubmarino(tabuleiroComputador2);
  posicionarPortaAviao(tabuleiroComputador2);

  printf("\nTabuleiro do Jogador:\n");
  imprimirTabuleiro(tabuleiroComputador1);

  printf("\n-----Posicione os PORTA AVIOES [N][N][N][N][N] -----\n");
  posicionarNavioHumano(tamPORTAVIAO, tabuleiroComputador1, quantPORTAVIAO);

  printf("\n-----Posicione os CONTRA-TORPEDEIROS [N][N][N] -----\n");
  posicionarNavioHumano(tamCONTRATORPEDEIROS, tabuleiroComputador1, quantCONTRATORPEDEIROS);

  printf("\n-----Posicione os NAVIOS TANQUE [N][N][N][N] -----\n");
  posicionarNavioHumano(tamNAVIOTANQUE, tabuleiroComputador1, quantNAVIOTANQUE);

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
