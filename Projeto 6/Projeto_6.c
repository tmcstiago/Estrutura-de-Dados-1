#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int random_number(int start, int end); //Gera número aleatório dentro do intervalo indicado, incluindo intervalo

typedef struct elemento {
	int valor;
	struct elemento *proximo;
} Elemento;

typedef struct lista {
	int tamanho;
	struct elemento *inicio;
	struct elemento *fim;
} Lista;

Lista * lista_vazia();
void insere_valor(Lista * lista, int valor); 

int main(){
	//Comando usado para que números gerados dentro do programa sejam aleatórios 
	srand(time(NULL));
	int i;
	Lista * pesos;
	pesos=lista_vazia();
	for(i=0; i<20; i++)
		insere_valor(pesos, random_number(1, 20));

	Elemento * atual;
	for(	i=0, atual=pesos->inicio; i<pesos->tamanho; i++, atual=atual->proximo){
		printf("%d\n", atual->valor);
	}
	printf("Primeiro valor da lista: %d\n", pesos->inicio->valor);
	printf("Último valor da lista: %d\n", pesos->fim->valor);
	printf("Tamanho da lista: %d\n", pesos->tamanho);
	return 0;
}

Lista * lista_vazia(){

	Lista * lista;
	lista = (Lista *) malloc(sizeof(Lista));
	if(lista==NULL){
		printf("Alocação falhou");
		exit(-1);
	}
	lista->inicio=NULL;
	lista->fim=NULL;
	lista->tamanho=0;

}

void insere_valor(Lista * lista, int valor){
	Elemento * novo_elemento;
	novo_elemento = (Elemento *) malloc(sizeof(Elemento));
	if(novo_elemento==NULL){
		printf("Alocação falhou");
		exit(-1);
	}
	novo_elemento->valor=valor;
	novo_elemento->proximo=NULL;

	if(lista->tamanho==0){
		lista->inicio=novo_elemento;
		lista->fim=novo_elemento;
		lista->tamanho++;
	}
	else{
		lista->fim->proximo=novo_elemento;
		lista->fim=novo_elemento;
		lista->tamanho++;
	}
}

int random_number(int start, int end){
	int number, diff;
	diff = end-start;
	number = rand()%(diff+1)+start;
	return number;
}
