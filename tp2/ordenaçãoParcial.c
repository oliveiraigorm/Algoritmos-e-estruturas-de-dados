#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAXTAM          20
typedef int TipoChave;
typedef struct TipoItem {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;
typedef int  TipoIndice;
typedef TipoItem TipoVetor[MAXTAM + 1];
TipoVetor A, B;
TipoIndice i, n, k;

void SelecaoParcial(TipoVetor A, TipoIndice n, TipoIndice k)
{ TipoIndice i, j, Min;  TipoItem x;
  for (i = 1; i <= k; i++)
    { Min = i;
      for (j = i + 1; j <= n; j++)
        if (A[j].Chave < A[Min].Chave) Min = j;
      x = A[Min]; A[Min] = A[i]; A[i] = x;
    }
}

void InsercaoParcial(TipoVetor A, TipoIndice n, TipoIndice k)
{ /*-- Nao preserva o restante do vetor --*/
  TipoIndice i, j;  TipoItem x;
  for (i = 2; i <= n; i++)
    { x = A[i];
      if (i > k) j = k; else j = i - 1;
      A[0] = x;   /* sentinela */
      while (x.Chave < A[j].Chave)
        { A[j+1] = A[j];
	  j--;
	}
      A[j+1] = x;
    }
}

void InsercaoParcial2(TipoVetor A, TipoIndice n, TipoIndice k)
{ /*-- Preserva o restante do vetor --*/
  TipoIndice i, j;  TipoItem x;
  for (i = 2; i <= n; i++)
    { x = A[i];
      if (i > k)
      { j = k;
        if (x.Chave < A[k].Chave) A[i] = A[k];
      }
      else j = i - 1;
      A[0] = x;   /* sentinela */
      while (x.Chave < A[j].Chave)
        { if (j < k) {A[j+1] = A[j];}
          j--;
        }
      if (j < k) A[j+1] = x;
  }
}

void Particao(TipoVetor A, TipoIndice Esq,
              TipoIndice Dir, TipoIndice *i, TipoIndice *j)
{ TipoItem x, w;
  *i = Esq;
  *j = Dir;
  x = A[(*i + *j) / 2];   /* obtem o pivo x */
  do
    { while (x.Chave > A[*i].Chave) (*i)++;
      while (x.Chave < A[*j].Chave) (*j)--;
      if (*i <= *j)
      { w = A[*i]; A[*i] = A[*j]; A[*j] = w;
        (*i)++; (*j)--;
      }
    } while (*i <= *j);
}
void Ordena(TipoVetor A, TipoIndice Esq, TipoIndice Dir, TipoIndice k)
{ TipoIndice i, j;
  Particao(A, Esq, Dir, &i, &j);
  if (j - Esq >= k - 1) { if (Esq < j) Ordena(A, Esq, j, k); return; }
  if (Esq < j) Ordena(A, Esq, j, k);
  if (i < Dir) Ordena(A, i, Dir, k);
}

void QuickSortParcial(TipoVetor A, TipoIndice n, TipoIndice k)
{ Ordena(A, 1, n, k); }

void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ TipoIndice i = Esq;
  int j;
  TipoItem x;

  j = i * 2;
  x = A[i];
  while (j <= Dir)
    { if (j < Dir)
      { if (A[j].Chave > A[j+1].Chave) j++;
      }
      if (x.Chave <= A[j].Chave) goto L999;
      A[i] = A[j];
      i = j;
      j = i * 2;
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

/*-- Coloca menor em A[n], segundo menor em A[n-1],...,    --*/
/*-- k-esimo em A[n-k]                                       --*/
void HeapsortParcial(TipoItem *A, TipoIndice n, TipoIndice k)
{ TipoIndice Esq = 1;  TipoIndice Dir;
  TipoItem x;  long Aux = 0;
  Constroi(A, n);   /* constroi o heap */
  Dir = n;
  while (Aux < k)
    { /* ordena o vetor */
      x = A[1];
      A[1] = A[n - Aux];
      A[n - Aux] = x;
      Dir--;
      Aux++;
      Refaz(Esq, Dir, A);
    }
}

void ParticaoDavisort(TipoItem *A, TipoIndice Esq,
                      TipoIndice Dir, TipoIndice *i,
                      TipoIndice *j)
{ TipoItem x, w;
  *i = Esq;
  *j = Dir;
  x = A[(*i + *j) / 2];   /* obtem o pivo x */
  do
    { while (x.Chave > A[*i].Chave) (*i)++;
      while (x.Chave < A[*j].Chave) (*j)--;
      if (*i <= *j)
      { w = A[*i];
        A[*i] = A[*j];
        A[*j] = w;
        (*i)++;
        (*j)--;
      }
    } while (*i <= *j);
}

void EncontraPivo(TipoItem *A, TipoIndice Esq, TipoIndice Dir,
                  TipoIndice k)
{ TipoIndice i, j;
  ParticaoDavisort(A,Esq, Dir, &i, &j);
  if (j >= k) EncontraPivo(A,Esq, j, k);
  if (i <= k) EncontraPivo(A,i, Dir, k);
}

void OrdenaDavisort (TipoItem *A, TipoIndice Esq,
                     TipoIndice Dir, TipoIndice k)
{ TipoIndice i, j;
  ParticaoDavisort(A,Esq, Dir, &i, &j);
  if (j - Esq >= k - 1) {
    if (Esq < j)
    OrdenaDavisort(A, Esq, j, k);
    return;
  }
  if (Esq < j)
  OrdenaDavisort(A, Esq, j, k);
  if (i < Dir)
  OrdenaDavisort(A, i, Dir, k);
}

void DavisortParcial(TipoItem *A, TipoIndice n, TipoIndice k)
{ TipoIndice candidatos, pivo, i; TipoItem x;
  if (k * 2 >= n) { OrdenaDavisort(A, 1, n, k); goto L999; }
  EncontraPivo(A, 1, k, k);
  candidatos = k;
  pivo = A[k].Chave;
  for (i = k + 1; i <= n; i++)
    { if (A[i].Chave <= pivo)
      { candidatos++;  x = A[candidatos];
        A[candidatos] = A[i];  A[i] = x;
      }
      if (candidatos == k * 2)
      { EncontraPivo(A, 1, candidatos, k);
        pivo = A[k].Chave;  candidatos = k + 1;
      }
    }
  OrdenaDavisort(A, 1, candidatos, k);
  L999: ;
}

void Imprime(TipoVetor V, TipoIndice n)
{ for (i = 1; i <= n; i++)
    printf("%d ", V[i].Chave);
  putchar('\n');
}

void Copia(TipoVetor Fonte, TipoVetor Destino, TipoIndice n)
{ for (i = 1; i <= n; i++)
    Destino[i] = Fonte[i];
}

void Testa(TipoVetor V, TipoIndice n, TipoIndice k)
{ for (i = 2; i <= k; i++)
    { if (V[i].Chave < V[i-1].Chave)
      { printf("ERRO: ");
        Imprime(V, n);
        exit(1);
      }
    }
  printf("OK  : ");
  Imprime(V, n);
}

int main(int argc, char *argv[])
{ int TEMP;
  n = 10;   /*Tamanho do arranjo a ser ordenado*/
  for (i = 1; i <= n; i++)
    { A[i].Chave =  1+(int) (10.0*rand()/(RAND_MAX+1.0));
      B[i].Chave = A[i].Chave;
    }
  printf("Desordenado   : ");
  Imprime(A, n);

  printf("SelecaoParcial com k = ");
  scanf("%d%*[^\n]", &TEMP);
  getchar();
  k = TEMP;
  SelecaoParcial(B, n, k);
  Testa(B, n, k);
  Copia(A, B, n);

  printf("InsercaoParcial (sem preservar restante do vetor) com k = ");
  scanf("%d%*[^\n]", &TEMP);
  getchar();
  k = TEMP;
  InsercaoParcial(B, n, k);
  Testa(B, n, k);
  Copia(A, B, n);

  printf("InsercaoParcial (preserva restante do vetor) com k = ");
  scanf("%d%*[^\n]", &TEMP);
  getchar();
  k = TEMP;
  InsercaoParcial2(B, n, k);
  Testa(B, n, k);
  Copia(A, B, n);

  printf("QuicksortParcial com k = ");
  scanf("%d%*[^\n]", &TEMP);
  getchar();
  k = TEMP;
  QuickSortParcial(B, n, k);
  Testa(B, n, k);
  Copia(A, B, n);

  printf("Heapsort com k =  ");
  scanf("%d%*[^\n]", &TEMP);
  getchar();
  k = TEMP;
  HeapsortParcial(B, n, k);
  printf("A parte ordenada esta no final do :\n");
  Imprime(B,n);
  Copia(A, B, n);

  printf("Davisort com k =  ");
  scanf("%d%*[^\n]", &TEMP);
  getchar();
  k = TEMP;
  DavisortParcial(B, n, k);
  Testa(B, n, k);
  Copia(A, B, n);

  return 0;
}

