/************************************************
LAED1 - Trabalho Pratico 1
Aluno: Igor Miranda Oliveira
Matricula: 201312040080
Data: 14/09/2017
************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Item{
    int peso;
    int valor;
    int num;
}item;
main(){
    time_t start,end;
    double dif;
    time (&start);
	int *peso, *valor,cap, n,pesoTotal = 0,valorTotal = 0, i,j,aux;
	item *itens;
    FILE *input; //arquivo que lera as entradas
    FILE *output;
    output = fopen("Saida Guloso.txt", "w");
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


    itens = malloc(sizeof(item) * n);
	for (i=0; i<n; i++){
		fscanf(input, "%d %d", &itens[i].peso, &itens[i].valor);
        itens[i].num=i;
	}

    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++) {
            if (itens[i].valor/itens[i].peso < itens[j].valor/itens[j].peso) {
                aux = itens[i].valor;
                itens[i].valor = itens[j].valor;
                itens[j].valor = aux;

                aux = itens[i].peso;
                itens[i].peso = itens[j].peso;
                itens[j].peso = aux;

                aux = itens[i].num;
                itens[i].num = itens[j].num;
                itens[j].num = aux;
            }
        }
    }

    aux=0;
    for(i=0;aux < cap;i++){
        aux += itens[i].peso;
        if(aux<=cap){
            pesoTotal += itens[i].peso;
            valorTotal += itens[i].valor;
            fprintf(output,"Item: %d - Peso: %d - Valor: %d\n", itens[i].num, itens[i].peso, itens[i].valor);
        }
    }
    fprintf(output, "Peso Total: %d\nValor Total: %d", pesoTotal, valorTotal);

    printf("Solucao gerada com sucesso, consulte o arquivo\n");
        time (&end);
    dif = difftime (end,start);
    printf ("Tempo de execucao: %lf segundos\n", dif );
    free(peso);
    free(valor);
    free(itens);
    fclose(output);
    fclose(input);
    return 0;
}
