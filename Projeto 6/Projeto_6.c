#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

typedef struct elemento {
	int valor;
	struct elemento *proximo;
} Elemento;

typedef struct lista {
	int tamanho;
	struct elemento *inicio;
	struct elemento *fim;
} Lista;

int random_number(int start, int end); //Gera número aleatório dentro do intervalo indicado, incluindo intervalo
Lista * lista_vazia();
void insere_valor(Lista * lista, int valor);

double funcao_ativacao(Lista *p, Lista *w, int b);

int main(){
	//Comando usado para que números gerados dentro do programa sejam aleatórios 
	srand(time(NULL));
	int i;
	Lista * p=lista_vazia();
	Lista * w=lista_vazia();
	int b = 0;

	insere_valor(p, 1);
	insere_valor(w, 6);

	insere_valor(p, 0);
	insere_valor(w, 7);

	insere_valor(p, 1);
	insere_valor(w, 5);

	double s=funcao_ativacao(p, w, b);

	printf("s = %lf\n", s);

	return 0;
}

int random_number(int start, int end){
	int number, diff;
	diff = end-start;
	number = rand()%(diff+1)+start;
	return number;
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

double funcao_ativacao(Lista *p, Lista *w, int b){
	if(p->tamanho != w->tamanho){
		printf("Erro na função de ativação\n");
		exit(-1);
	}
	
	Elemento * p_atual=p->inicio;
	Elemento * w_atual=w->inicio;
	double n=b;
	for(int i=0 ; i<p->tamanho ; p_atual=p_atual->proximo, w_atual=w_atual->proximo, i++){
		n += p_atual->valor*w_atual->valor;
	}

	double s;
	s=1/(1+pow(M_E, (-1)*n));
	
	return s;
}
