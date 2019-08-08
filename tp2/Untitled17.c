/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Igor Miranda Oliveira
Matricula: 201312040080
Data: 10/11/2017
************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"geraVetor.h"

void BubbleSort(int vetor[], int tam) {
      int fim,i,aux;
      for (fim = tam-1; fim > 0; --fim) {
          for ( i = 0; i < fim; ++i) {
             if (vetor[i] > vetor[i+1]) {
                  aux = vetor[i];
                  vetor[i] = vetor[i+1];
                  vetor[i+1] = aux;
              }
          }
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

 main(){
 int *A, n;
 FILE *selection;
if ((selection = fopen("bubble.csv", "w")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return 0;
	}
 for(n=10; n<3000; n++){
A = (int) malloc(sizeof(int)*n);

  Copia(semRep(n), A, n);
clock_t start = clock();
clock_t elapsed;
    BubbleSort(A,n);
    Testa(A,n);
    elapsed = clock() - start;
int milliSeconds = elapsed * 1000 / CLOCKS_PER_SEC;
  fprintf(selection," %d, %d\n",n,milliSeconds);
  }
 }
