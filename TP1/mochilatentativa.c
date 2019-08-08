/************************************************
LAED1 - Trabalho Pr�tico 1
Aluno: Igor Miranda Oliveira
Matr�cula: 201312040080
Data: 14/09/2017
************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
typedef struct Item{
    int peso;
    int valor;
}item;
main(){
    time_t start,end;
    double dif;
    time (&start);
    item *itens;
	int *A,*B,cap, n,c;
	int valorTotal=0, pesoTotal=0,i,j,k,pesoTemp = 0,valorTemp = 0;
    FILE *input;
    FILE *output;
    output = fopen("Saida Tentativa.txt", "w");
    fprintf(output, "/************************************************\n");
    fprintf(output,"\tLAED1 - Trabalho Pratico 1\n\tAluno: Igor Miranda Oliveira\n\tMatricula: 201312040080\n\tData: 14/09/2017\n");
    fprintf(output,"************************************************/\n");
	if ((input = fopen("arq.txt", "r")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		return 0;
	}
	fscanf(input, "%d", &cap);
	fscanf(input,"%d", &n);

    A = malloc(sizeof(int) * n);
    B = malloc(sizeof(int) * n);
    itens = malloc(sizeof(item) * n);
	for (i=0; i<n; i++){
		fscanf(input, "%d %d", &itens[i].peso, &itens[i].valor);
	}

    for(i=0;i<n;i++){
        A[i]=0;
        B[i]=0;
    }

    for (i = 0;; i++){
        pesoTemp = 0;
        valorTemp = 0;
        k =1;
        for (j = 0; j < n; j++) {
            A[j] += k;
            k = A[j] / 2;
            A[j] = A[j] % 2;
        }
        if (k)
            break;

        for (k = 0; k < n; k++) {
            if (A[k] == 1) {
                pesoTemp+= itens[k].peso;
                valorTemp += itens[k].valor;
            }
        }

        if (valorTemp > valorTotal && pesoTemp <= cap) {
            valorTotal = valorTemp;
            pesoTotal = pesoTemp;
            for(c=0;c<n;c++){
                B[c]=A[c];
            }
        }
    }
    for(i=0;i<n;i++){
        if(B[i])
        fprintf(output,"Item: %d - Peso: %d - Valor: %d\n", i, itens[i].peso, itens[i].valor);
    }

    fprintf(output, "Peso Total: %d\nValor Total: %d", pesoTotal, valorTotal);
    printf("Solucao gerada com sucesso, consulte o arquivo\n");
    time (&end);
    dif = difftime (end,start);
    printf ("Tempo de execucao: %lf segundos\n", dif );
    free(A);
    free(B);
    free(itens);
    fclose(output);
    fclose(input);
    return 0;
}
