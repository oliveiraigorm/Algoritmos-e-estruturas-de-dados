/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Igor Miranda Oliveira
Matricula: 201312040080
Data: 10/11/2017
************************************************/
#include   <limits.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <time.h>
#include   "geraVetor.h"


typedef long TipoChave;
typedef struct TipoItem {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;

typedef int TipoIndice;
typedef TipoItem TipoVetor;
/* MAXTAM+1 por causa da sentinela em Insercao */
int *A;
TipoIndice i, n;

void Selecao(TipoItem *A, TipoIndice n)
{ TipoIndice i, j, Min;
  TipoItem x;
  for (i = 1; i <= n - 1; i++)
    { Min = i;
      for (j = i + 1; j <= n; j++)
        if (A[j].Chave < A[Min].Chave) Min = j;
      x = A[Min]; A[Min] = A[i]; A[i] = x;
    }
}

void Insercao(TipoItem *A, TipoIndice n)
{ TipoIndice i, j;
  TipoItem x;
  for (i = 2; i <= n; i++)
    { x = A[i];  j = i - 1;
      A[0] = x;  /* sentinela */
      while (x.Chave < A[j].Chave)
        { A[j+1] = A[j];  j--;
        }
      A[j+1] = x;
    }
}

void Shellsort(TipoItem *A, TipoIndice n)
{ int i, j;  int h = 1;
  TipoItem x;
  do h = h * 3 + 1; while (h < n);
  do
    { h /= 3;
      for (i = h + 1; i <= n; i++)
        { x = A[i];  j = i;
          while (A[j - h].Chave > x.Chave)
            { A[j] = A[j - h];  j -= h;
              if (j <= h) goto L999;
            }
            L999: A[j] = x;
        }
    } while (h != 1);
}

void Particao(TipoIndice Esq, TipoIndice Dir,
              TipoIndice *i, TipoIndice *j, TipoItem *A)
{ TipoItem x, w;
  *i = Esq;  *j = Dir;
  x = A[(*i + *j) / 2]; /* obtem o pivo x */
  do
    { while (x.Chave > A[*i].Chave) (*i)++;
      while (x.Chave < A[*j].Chave) (*j)--;
      if (*i <= *j)
      { w = A[*i]; A[*i] = A[*j]; A[*j] = w;
        (*i)++; (*j)--;
      }
    } while (*i <= *j);
}

void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ TipoIndice i, j;
  Particao(Esq, Dir, &i, &j, A);
  if (Esq < j) Ordena(Esq, j, A);
  if (i < Dir) Ordena(i, Dir, A);
}

void QuickSort(TipoItem *A, TipoIndice n)
{ Ordena(1, n, A); }

void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ TipoIndice i = Esq;
  int j;
  TipoItem x;
  j = i * 2;
  x = A[i];
  while (j <= Dir)
    { if (j < Dir)
      { if (A[j].Chave < A[j+1].Chave)
        j++;
      }
      if (x.Chave >= A[j].Chave) goto L999;
      A[i] = A[j];
      i = j;  j = i * 2;
    }
  L999: A[i] = x;
}

void Constroi(TipoItem *A, TipoIndice n)
{ TipoIndice Esq;
  Esq = n / 2 + 1;
  while (Esq > 1)
    { Esq--;
      Refaz(Esq, n, A);
    }
}

/*--Entra aqui a funcao Refaz do Programa 4.9 --*/
/*--Entra aqui a funcao Constroi do Programa 4.10--*/

void Heapsort(TipoItem *A, TipoIndice n)
{ TipoIndice Esq, Dir;
  TipoItem x;
  Constroi(A, n);  /* constroi o heap */
  Esq = 1;  Dir = n;
  while (Dir > 1)
    { /* ordena o vetor */
      x = A[1];  A[1] = A[Dir];  A[Dir] = x;  Dir--;
      Refaz(Esq, Dir, A);
    }
}

void Imprime(TipoItem *V, TipoIndice n)
{ for (i = 1; i <= n; i++)
    printf("%li ", V[i].Chave);  printf("\n");
}

void Copia(TipoItem *Fonte, TipoItem *Destino, TipoIndice n)
{ for (i = 1; i <= n; i++)
    Destino[i] = Fonte[i];
}

void Testa(TipoItem *V, TipoIndice n)
{ for (i = 2; i <= n; i++) {
    if (V[i].Chave < V[i-1].Chave) {
      printf("ERRO: ");
      Imprime(V, n);
      return;
    }
  }
  //printf("OK: ");
  Imprime(V, n);
}

double rand0a1()
{ double resultado=  (double) rand()/ INT_MAX; /* Dividir pelo maior inteiro */
  if(resultado>1.0) resultado= 1.0;
  return resultado;
}

void Permut( TipoItem *A, int n)
{ int i,j;
  TipoItem b;

  for(i = n-1; i>0; i --)
  { j = (i * rand0a1()) +1 ;
    b = A[i];
    A[i] = A[j];
    A[j] = b;
  }
}

int main(int argc, char *argv[])
{ int *B;
  n = 20;   /*Tamanho do arranjo a ser ordenado*/
FILE *selection;
//out = fopen("out.csv", "rw");
if ((selection = fopen("shell.csv", "w")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return 0;
	}

 /* for(n=10; n<10000; n++){
B = (int) malloc(sizeof(int)*n);
A = (int) malloc(sizeof(int)*n);

  Copia(vetAle(n), A, n);
  Copia (A,B,n);

clock_t start = clock();
clock_t elapsed;

  Selecao(B, n);
  Testa(B, n);
  elapsed = clock() - start;
int milliSeconds = elapsed * 1000 / CLOCKS_PER_SEC;
  fprintf(selection," %d, %d\n",n,milliSeconds);
  }
  for(n=10; n<10000; n++){
B = (int) malloc(sizeof(int)*n);
A = (int) malloc(sizeof(int)*n);

  Copia(vetAle(n), A, n);
  Copia (A,B,n);

clock_t start = clock();
clock_t elapsed;


  elapsed = clock() - start;
    Insercao(B, n);
    Testa(B, n);
int milliSeconds = elapsed * 1000 / CLOCKS_PER_SEC;
  fprintf(selection," %d, %d\n",n,milliSeconds);
  }
*/
for(n=10; n<10000; n++){
B = (int) malloc(sizeof(int)*n);
A = (int) malloc(sizeof(int)*n);

  Copia(semRep(n), A, n);
  Copia (A,B,n);

clock_t start = clock();
clock_t elapsed;



  //printf("Shellsort ");
  Shellsort(B, n);
Testa(B, n);
elapsed = clock() - start;
int milliSeconds = elapsed * 1000 / CLOCKS_PER_SEC;
  fprintf(selection," %d, %d\n",n,milliSeconds);
  }/*

  printf("Quicksort ");
  QuickSort(B, n);
  Testa(B, n);
  Copia(A, B, n);

  printf("Heapsort  ");
  Heapsort(B, n);
  Testa(B, n);
  Copia(A, B, n);
*/
  return 0;
}
