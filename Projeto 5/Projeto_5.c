#include <stdio.h>
#include <stdlib.h>
#define ESPACO 5

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
void searchValue(Arvore *arvore, int valor);
void getHeight(Arvore *arvore);
void removeValue(Arvore *arvore, int value);
void printInOrder(Arvore *arvore);
void printPreOrder(Arvore *arvore);
void printPostOrder(Arvore *arvore);
//void balanceTree(Arvore *arvore);

//Funções criadas para auxilio no programa
Arvore * busca(Arvore *arvore, int valor, int *aux); //busca valor e retorna nível de seu nó ao aux
int altura(Arvore *arvore);
Arvore * iniciar_arvore(int valor);
void insere_valor(Arvore * item, int valor);
void imprimeLinha(Arvore *arvore, int depth, char *path, int direita);
int tamanho(Arvore *arvore);
void imprimeNo(char c, int b);

int main(){
	Arvore *arvore; 
	arvore = loadTreeFromFile("example.txt");
	showTree(arvore);
	//printPostOrder(arvore);
	getHeight(arvore);
	searchValue(arvore, 23);
	removeValue(arvore, 23);
	showTree(arvore);
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
		//printf("Criando arvore com %d...\n", value);
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
			//printf("%d > %d\n", valor, arvore->valor);
			Arvore *novo_valor;
			novo_valor=iniciar_arvore(valor);
			arvore->direita=novo_valor;
			//printf("Inserindo %d a direita...\n", valor);
		}
		else{
			insere_valor(arvore->direita, valor);
		}
	}
	else{
		if(arvore->esquerda==NULL){
			//printf("%d < %d\n", valor, arvore->valor);
			Arvore *novo_valor;
			novo_valor=iniciar_arvore(valor);
			arvore->esquerda=novo_valor;
			//printf("Inserindo %d a esquerda...\n", valor);
		}
		else{
			insere_valor(arvore->esquerda, valor);
		}
	}
}
void removeValue(Arvore *arvore, int value){
	int i=1;
	Arvore * delete = busca(arvore, value, &i);
	if(delete==NULL){
		printf("O valor não foi encontrado para o excluir\n");
		return;
	}
	if(i==1){
		printf("Cabeça da árvore\n");
		return;
	}
	else{
		//printf("Elemento\n");
		Arvore *aux;
		if(delete->esquerda->valor == value){
			//printf("Elemento da esquerda\n");
			aux=delete->esquerda;
			if(aux->direita == NULL && aux->esquerda == NULL){
				delete->esquerda=NULL;
				free(aux);
				return;
			}
			else if(aux->direita == NULL && aux->esquerda != NULL){
				printf("passou 1");
				delete->esquerda=aux->esquerda;
				free(aux);
				return;
			}
			else if(aux->direita != NULL && aux->esquerda == NULL){
				printf("passou 2");
				delete->esquerda=aux->direita;
				free(aux);
				return;
			}
			else{

			}
		}
		else{
			//printf("Elemento da direita\n");
			aux=delete->direita;
			if(aux->direita == NULL && aux->esquerda == NULL){
				delete->direita=NULL;
				free(aux);
				return;
			}
			else if(aux->direita == NULL && aux->esquerda != NULL){
				printf("passou 3");
				delete->direita=aux->esquerda;
				free(aux);
				return;
			}
			else if(aux->direita != NULL && aux->esquerda == NULL){
				printf("passou 4");
				delete->direita=aux->direita;
				free(aux);
				return;
			}
			else{
				
			}
		}
	}

}
void searchValue(Arvore *arvore, int valor){
	int i=1;
	Arvore * aux = busca(arvore, valor, &i);
	if(aux!=NULL){
		if(arvore == aux && i==1){
			printf("Valor encontrado\n");
			printf("O valor é a raiz da árvora, portanto não tem pai nem irmãos\n");
		}
		else{
			printf("Valor encontrado\n");
			printf("Valor do pai %d\n", aux->valor);
			if(aux->direita != NULL && aux->direita->valor != valor){
				printf("Valor do irmão %d\n", aux->direita->valor);
			}
			else if(aux->esquerda != NULL && aux->esquerda->valor != valor){
				printf("Valor do irmão %d\n", aux->esquerda->valor);
			}
			printf("Nível do seu nó:%d\n", i);
		}
	}
	else{
		printf("O valor não foi encontrado\n");
	}

}
Arvore * busca(Arvore *arvore, int valor, int *aux){
	(*aux)++;
	if(valor<arvore->valor){
		if(arvore->esquerda != NULL){
			if(arvore->esquerda->valor==valor)
				return arvore;
			
			else
				busca(arvore->esquerda, valor, aux);
			
		}
		else
			return NULL;
	}
	else if(valor>arvore->valor){
		if(arvore->direita != NULL){
			if(arvore->direita->valor==valor)
				return arvore;
			else
				busca(arvore->direita, valor, aux);
		}
		else
			return NULL;
	}
	else
		return arvore;
}
void showTree(Arvore *arvore){
	int tam = tamanho(arvore);
	int h = altura(arvore);
	char path[255] = {};
	imprimeLinha(arvore, 0, path, 0);
	printf("\n");
}
void imprimeLinha(Arvore *arvore, int depth, char *path, int direita){
	if(arvore==NULL){			
		return;
	}

	depth++;

	imprimeLinha(arvore->direita, depth, path, 1);
	// set | draw map
	path[depth-2] = 0;

	if(direita)
		path[depth-2] = 1;

	if(arvore->esquerda)
		path[depth-1] = 1;

	// print root after spacing
	printf("\n");

	for(int i=0; i<depth-1; i++)
	{
		if(i == depth-2)
		  printf("+");
		else if(path[i])
		  printf("|");
		else
		  printf(" ");

		for(int j=1; j<ESPACO; j++){
			if(i < depth-2)
			  printf(" ");
			else
			  printf("-");
		}
	}

	printf("%d\n", arvore->valor);

	// vertical espacors below
	for(int i=0; i<depth; i++)
	{
		if(path[i])
		  printf("|");
		else
		  printf(" ");

		for(int j=1; j<ESPACO; j++)
		  printf(" ");
	}
	imprimeLinha(arvore->esquerda, depth, path, 0);		
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