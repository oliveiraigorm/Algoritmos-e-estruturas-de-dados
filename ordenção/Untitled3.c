#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX 10


typedef char TipoChave[100];
typedef struct {
  TipoChave Nome;
  int Nota;
} TipoItem;
typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;
typedef struct {
  TipoApontador Fundo, Topo;
  int Tamanho;
} TipoPilha;

void FPVazia(TipoPilha *Pilha)
{ Pilha->Topo = (TipoApontador) malloc(sizeof(TipoCelula));
  Pilha->Fundo = Pilha->Topo;
  Pilha->Topo->Prox = NULL;
  Pilha->Tamanho = 0;
}

int Vazia(TipoPilha Pilha)
{ return (Pilha.Topo == Pilha.Fundo); }

void Empilha(TipoItem x, TipoPilha *Pilha)
{ TipoApontador Aux;
  Aux = (TipoApontador) malloc(sizeof(TipoCelula));
  Pilha->Topo->Item = x;
  Aux->Prox = Pilha->Topo;
  Pilha->Topo = Aux;
  Pilha->Tamanho++;
}

void Desempilha(TipoPilha *Pilha, TipoItem *Item)
{ TipoApontador q;
  if (Vazia(*Pilha)) { printf("Erro: lista vazia\n"); return; }
  q = Pilha->Topo;
  Pilha->Topo = q->Prox;
  *Item = q->Prox->Item;
  free(q);  Pilha->Tamanho--;
}

int Tamanho(TipoPilha Pilha)
{ return (Pilha.Tamanho);
}

int main(int argc, char *argv[]){
    char nome[140];
    int i;
    TipoPilha pilha, vet[11],paux;
    TipoItem item;
    FILE *input; //arquivo que lera as entradas
    printf("Digite o nome do arquivo: ");
    scanf("%s",nome);
    FPVazia(&pilha);
    FPVazia(&paux);
    for(i=0;i<11;i++){
        FPVazia(&vet[i]);
    }
	if ((input = fopen(nome, "rb")) == NULL){
		printf("Erro ao abrir o arquivo.\n");
		return 0;
	}

        while(!feof(input)){
            fread(&item, sizeof(TipoItem), 1, input);
            Empilha(item,&vet[item.Nota]);
            }
    for(i=0;i<11;i++){
        while(!Vazia(vet[i])){
        Desempilha(&vet[i],&item);
        Empilha(item,&paux);
        }
        while(!Vazia(paux)){
        Desempilha(&paux,&item);
        printf ("\n%s \n%d", item.Nome, item.Nota);
        }
    }


  return 0;
}








