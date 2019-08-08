#include"geraVetor.h"
#include<stdio.h>
#include<time.h>

/*Merge: intercala A[i..m] e A[m+1..j] em A[i..j] */
void Merge(int* A, int i, int m, int j){
  int *B;
  B = (int) malloc(sizeof(int)*(j-i));
  int x;
  int k = i;
  int l = m+1;

  for (x=i;x<=j;x++) B[x] = A[x];
  x = i;
  while (k<=m && l<=j ) {
    if (B[k] <= B[l])
      A[x++] = B[k++];
    else
      A[x++] = B[l++];
  }

  while (k<=m) A[x++] = B[k++];

  while (l<=j) A[x++] = B[l++];

}

/*Mergesort: consiste na intercalação recursiva de vetores ordenados. */
void Mergesort(int* A, int i, int j){
  int m;
  if (i < j){
    m = (i + j - 1) / 2;
    Mergesort(A, i, m);
    Mergesort(A, m + 1, j);
    Merge(A,  i,  m, j); /*Intercala A[i..m] e A[m+1..j] em A[i..j] */
  }
}
 void Copia(int *Fonte, int *Destino, int n)
{ int i;
    for (i = 1; i <= n; i++)
    Destino[i] = Fonte[i];
}
void Imprime(int *V, int n)
{
    int i;
     for (i = 1; i <= n; i++)
    printf("%i ", V[i]);  printf("\n");
}

void Testa(int *V, int n)
{
    int i;
     for (i = 2; i <= n; i++) {
    if (V[i] < V[i-1]) {
      printf("ERRO: ");
      Imprime(V, n);
      return;
     }
  }
  printf("OK: ");
  Imprime(V, n);
}
int main(){
 int *A, n;
 FILE *selection;
if ((selection = fopen("merge.csv", "w")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return 0;
	}
 for(n=10; n<10000; n++){
A = (int) malloc(sizeof(int)*n);

  Copia(vetAle(n), A, n);
clock_t start = clock();
clock_t elapsed;
    Mergesort(A,0,n);
    Testa(A,n);
    elapsed = clock() - start;
int milliSeconds = elapsed * 1000 / CLOCKS_PER_SEC;
  fprintf(selection," %d, %d\n",n,milliSeconds);
  }
  return 0;
}


