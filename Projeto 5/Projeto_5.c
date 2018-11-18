#include <stdio.h>
#include <stdlib.h>

typedef struct ArvoreBinaria{
	int valor;
	struct ArvoreBinaria * esquerda;
	struct ArvoreBinaria * direita;	
} Arvore;

// Funções pedidas no trabalho
//As comentadas estão faltando

Arvore * loadTreeFromFile(char *path);
void showTree(Arvore *arvore);
//void isFull(Arvore *arvore);
//void searchValue(Arvore *arvore, value);
void getHeight(Arvore *arvore);
//void removeValue(Arvore *arvore, int value);
void printInOrder(Arvore *arvore);
void printPreOrder(Arvore *arvore);
void printPostOrder(Arvore *arvore);
//void balanceTree(Arvore *arvore);

//Funções criadas para auxilio no programa
int altura(Arvore *arvore);
Arvore * iniciar_arvore(int valor);
void insere_valor(Arvore * item, int valor);
void imprimeLinha(Arvore * arvore, int aux, int linha);
int tamanho(Arvore *arvore);
void imprimeNo(char c, int b);

int main(){
	Arvore *arvore; 
	arvore = loadTreeFromFile("example.txt");
	getHeight(arvore);
	showTree(arvore);
	printInOrder(arvore);
	return 0;
}

Arvore * loadTreeFromFile(char *path){
	FILE *arquivo;
	arquivo = fopen(path, "r");
	if (arquivo == NULL){
		printf("Erro na leitura do arquivo\n");
		return NULL;
	}
	int value;
	Arvore *arvore;
	if(fscanf(arquivo,"%d", &value)!=EOF){
		arvore = iniciar_arvore(value);
		printf("Criando arvore com %d...\n", value);
	}
	else
		return NULL;
	while(fscanf(arquivo,"%d", &value)!=EOF){
		insere_valor(arvore, value);
	}
	return arvore;
}

Arvore * iniciar_arvore(int valor){
	Arvore *nova_arvore;
	nova_arvore = (Arvore *) malloc(sizeof(Arvore));
	if(nova_arvore==NULL){
		printf("Alocação falhou\n");
		exit(-1);
	}
	nova_arvore->esquerda = NULL;
	nova_arvore->direita = NULL;
	nova_arvore->valor = valor;
	return nova_arvore;
}
void insere_valor(Arvore * arvore, int valor){
	if(valor == arvore->valor)
		return;
	else if(valor > arvore->valor){
		if(arvore->direita==NULL){
			printf("%d > %d\n", valor, arvore->valor);
			Arvore *novo_valor;
			novo_valor=iniciar_arvore(valor);
			arvore->direita=novo_valor;
			printf("Inserindo %d a direita...\n", valor);
		}
		else{
			insere_valor(arvore->direita, valor);
		}
	}
	else{
		if(arvore->esquerda==NULL){
			printf("%d < %d\n", valor, arvore->valor);
			Arvore *novo_valor;
			novo_valor=iniciar_arvore(valor);
			arvore->esquerda=novo_valor;
			printf("Inserindo %d a esquerda...\n", valor);
		}
		else{
			insere_valor(arvore->esquerda, valor);
		}
	}
}
void showTree(Arvore *arvore){
	int tam = tamanho(arvore);
	int h = altura(arvore);
	for (int i=0; i<h; i++){
		for(int j=i; j<h; j++)
			printf("   ");
		imprimeLinha(arvore, 0, i);
		printf("\n");
		for(int j=i; j<h; j++)
			printf("   ");
		for(int k=0; k<=i; k++){
			printf("/ ");
			printf("\\  ");
		}
		printf("\n");
	}
}
void imprimeLinha(Arvore *arvore, int aux, int linha){
	if(arvore==NULL){		
        	return;
	}
	imprimeLinha(arvore->esquerda, aux+1, linha);
	if(aux==linha){
		printf("%2d   ", arvore->valor);
		return;
	}
	imprimeLinha(arvore->direita, aux+1, linha);
}
int tamanho(Arvore*arvore){
	if(arvore==NULL){
		return 0;
	}
	else{
		int tam1 = tamanho(arvore->esquerda);
		int tam2 = tamanho(arvore->direita);
			return tam1+tam2+1;
	}
}
void getHeight(Arvore *arvore){
	printf("Altura da arvore %d\n", altura(arvore));
}
int altura(Arvore*arvore){
	if(arvore==NULL){
		return 0;
	}
	else{
		int he = altura(arvore->esquerda);
		int hd = altura(arvore->direita);
		if(he<hd)
			return hd+1;
		else
			return he+1;	
	}
}
void printInOrder(Arvore *arvore){
	if(arvore==NULL){		
        	return;
	}
	printInOrder(arvore->esquerda);
	printf("%d\n", arvore->valor);
	printInOrder(arvore->direita);

}
void printPreOrder(Arvore *arvore){
	if(arvore==NULL){		
        	return;
	}
	printf("%d\n", arvore->valor);
	printPreOrder(arvore->esquerda);
	printPreOrder(arvore->direita);
}
void printPostOrder(Arvore *arvore){
	if(arvore==NULL){		
        	return;
	}
	printPostOrder(arvore->esquerda);
	printPostOrder(arvore->direita);
	printf("%d\n", arvore->valor);
}
