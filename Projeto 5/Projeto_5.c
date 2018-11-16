#include <stdio.h>
#include <stdlib.h>

typedef struct ArvoreBinaria{
	int valor;
	struct ArvoreBinaria * esquerda;
	struct ArvoreBinaria * direita;	
} arvore;

arvore * iniciar_arvore();

int main(){
	arvore *numeros; 
	numeros = iniciar_arvore();
	printf("endereço da arvore %p\n", numeros);

	return 0;
}
arvore * iniciar_arvore(){
	arvore *nova_arvore;
	nova_arvore = (arvore *) malloc(sizeof(arvore));
	if(nova_arvore==NULL){
		printf("Alocação falhou\n");
		exit(-1);
	}
	nova_arvore->esquerda = NULL;
	nova_arvore->direita = NULL;
	return nova_arvore;
}

