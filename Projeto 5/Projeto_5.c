#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
void isFull(Arvore *arvore);
void searchValue(Arvore *arvore, int valor);
void getHeight(Arvore *arvore);
Arvore * removeValue(Arvore *arvore, int value);
void printInOrder(Arvore *arvore);
void printPreOrder(Arvore *arvore);
void printPostOrder(Arvore *arvore);
Arvore * balanceTree(Arvore *arvore);

//Funções criadas para auxilio no programa
Arvore * busca(Arvore *arvore, int valor, int *aux); //busca valor e retorna nível de seu nó ao aux
int altura(Arvore *arvore);
Arvore * iniciar_arvore(int valor);
void insere_valor(Arvore * item, int valor);
void imprimeLinha(Arvore *arvore, int depth, char *path, int direita);
int tamanho(Arvore *arvore);
void imprimeNo(char c, int b);
bool isFullBool(Arvore *arvore, int index, int nodes);
int contaNos(Arvore *arvore);
void freeTree(Arvore * arvore);
bool isBalanced(Arvore *arvore);
void rotacionaDireita(Arvore *avo, Arvore *pai, Arvore *filho);
void rotacionaEsquerda(Arvore *avo, Arvore *pai, Arvore *filho);
Arvore * makeBackbone(Arvore *arvore, Arvore *avo, Arvore *pai, Arvore *filho);
void imprimiArvore(Arvore *arvore, int altura, int nivel);
void imprimi_elementos(Arvore *arvore, int altura, int nivel, int nivel_atual);
int espacos_esquerda(int atura, int nivel);
int espacos_entre_elementos(int atura, int nivel);
void imprimi_barras(Arvore *arvore, int altura, int nivel, int nivel_atual);

int main(){
	Arvore *arvore = NULL;
	arvore = loadTreeFromFile("example.txt");
	int opcao;
	do{
		printf("\n\n\n");
		printf("1. Carrega arvore a partir de arquivo\n");
		printf("2. Mostra árvore carregada\n");
		printf("3. Verifica se árvore é cheia ou não\n");
		printf("4. Procura valor na árvore (É mostrado valor pai, nível, e irmão caso possua)\n");
		printf("5. Mostra altura da árvore\n");
		printf("6. Remove valor da árvore\n");
		printf("7. Printa valores usando algorítimo in order\n");
		printf("8. Printa valores usando algorítimo pre order\n");
		printf("9. Printa valores usando algorítimo post order\n");
		printf("10. Realiza balanceamento da ávore carregada\n");
		printf("0. Fecha programa\n");
		scanf("%d", &opcao);
		printf("\n\n\n");
		switch(opcao){
			case 1:
			{
				char path[500];
				printf("Escreva o nome do arquivo: ./");
				scanf("%s", path);
				arvore = loadTreeFromFile(path);
				break;
			}					
			case 2:
				showTree(arvore);
				break;
			case 3:
				isFull(arvore);
				break;
			case 4:
			{
				int value;
				printf("Escreva o valor que será buscado:");
				scanf("%d", &value);
				searchValue(arvore, value);
				break;
			}				
			case 5:
				getHeight(arvore);
				break;
			case 6:
			{
				int value;
				printf("Escreva o valor que será removido:");
				scanf("%d", &value);
				arvore = removeValue(arvore, value);
				break;
			}			
			case 7:
				printInOrder(arvore);
				break;
			case 8:
				printPreOrder(arvore);
				break;
			case 9:
				printPostOrder(arvore);
				break;
			case 10:
			{
				arvore = balanceTree(arvore);
				printf("END 3\n");
			}
		}	
	}while(opcao!=0);
	freeTree(arvore);
	return 0;
}
void rotacionaDireita(Arvore *avo, Arvore *pai, Arvore *filho){
	printf("1");
	if(avo != NULL){
		printf("2");
		if(avo->esquerda == pai)
			avo->esquerda = filho;
		else
			avo->direita = filho;
	}	
	printf("3");
	pai->esquerda = filho->direita;
	filho->direita = pai;
	printf("4\n");

}
void rotacionaEsquerda(Arvore *avo, Arvore *pai, Arvore *filho){
	if(avo != NULL){
		if(avo->esquerda == pai)
			avo->esquerda = filho;
		else
			avo->direita = filho;
	}
	pai->direita = filho->esquerda;
	filho->esquerda = pai;

}
Arvore * makeBackbone(Arvore *arvore, Arvore *avo, Arvore *pai, Arvore *filho){
	if(arvore==NULL)
		return NULL;
	if(filho==NULL){
		arvore = makeBackbone(arvore, avo, pai, arvore);
	}
	//Tem filho a esquerda?
	if(filho->esquerda != NULL){
		printf("1");
		//É raiz?
		if(filho==arvore){
			printf(".1\n");
			pai=filho;
			filho=filho->esquerda;
			rotacionaDireita(avo, pai, filho);
			showTree(filho);
			arvore = makeBackbone(filho, avo, pai, filho);
			
		}	
		else{
			printf(".2\n");
			pai=filho;
			filho=filho->esquerda;
			rotacionaDireita(avo, pai, filho);
			showTree(arvore);
			arvore = makeBackbone(arvore, avo, pai, filho);
		}
	}
	else{
		printf("2");
		if(avo==filho){
			printf(".1");
			//Tem filho a direita?
			if(filho->direita != NULL){
				printf(".1\n");
				filho=filho->direita;
				arvore = makeBackbone(arvore, avo, pai, filho);
			}
			else{
				printf(".2\n");
				return arvore;
			}
		}
		else{
			printf(".2\n");
			avo=filho;
			arvore = makeBackbone(arvore, avo, pai, filho);
		}	
	}
	return arvore;
}
Arvore * balanceTree(Arvore *arvore){
	if(isBalanced(arvore))
		return arvore;
	else{
		Arvore *aux;
		printf("balanceTree\n");
		aux = makeBackbone(arvore, NULL, NULL, NULL);
		printf("END 2\n");
		return aux;
	}
}
bool isBalanced(Arvore *arvore){ 
  
	if(arvore == NULL) 
		return true;  
  
	int lh = altura(arvore->esquerda); 
	int rh = altura(arvore->direita); 

	if(abs(lh-rh) <= 1 && 
	   isBalanced(arvore->esquerda) && 
	   isBalanced(arvore->direita)
	) 
		return true; 

	return false; 
}
void freeTree(Arvore * arvore){
	if(arvore==NULL){		
        	return;
	}
	freeTree(arvore->esquerda);
	freeTree(arvore->direita);
	free(arvore);
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
bool isFullBool(Arvore *arvore, int index, int nodes){
	if (arvore == NULL) 
        	return true;
	
	if (index >= nodes) 
        	return false;

	return (isFullBool(arvore->esquerda, 2*index + 1, nodes) && 
                 isFullBool(arvore->direita, 2*index + 2, nodes)
		);
}
void isFull(Arvore *arvore){
	int nodes = contaNos(arvore);
	if(isFullBool(arvore, 0, nodes))
		printf("A arvore é cheia\n");
	else 
		printf("A arvore não é cheia\n");


}
int contaNos(Arvore *arvore){
	if (arvore == NULL) 
       		return 0; 
    	return (1 + contaNos(arvore->esquerda) + contaNos(arvore->direita));

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
Arvore * removeValue(Arvore *arvore, int value){
	int i=1;
	Arvore * delete = busca(arvore, value, &i);
	if(delete==NULL){
		printf("O valor não foi encontrado para o excluir\n");
		return arvore;
	}
	if(delete==arvore){
		if(arvore->direita==NULL && arvore->esquerda==NULL){
			free(arvore);			
			return NULL;
		}
		else if(arvore->direita==NULL && arvore->esquerda!=NULL){
			free(delete);			
			return arvore->esquerda;
		}
		else if(arvore->direita!=NULL && arvore->esquerda==NULL){
			free(delete);			
			return arvore->direita;
		}
		else{
			Arvore *i=arvore->direita;
			if(i->esquerda == NULL){
				i->esquerda=arvore->esquerda;
				free(arvore);
				return i;
			}
			else{
				for(; i->esquerda->esquerda != NULL; i=i->esquerda);
				arvore->valor=i->esquerda->valor;
				Arvore *aux=i->esquerda;;
				i->esquerda=NULL;
				free(aux);
			}		
		}
	}
	else{	
		//printf("Elemento\n");
		Arvore *aux;
		if(delete->esquerda != NULL && delete->esquerda->valor == value){
			//printf("Elemento da esquerda\n");
			aux=delete->esquerda;
			if(aux->direita == NULL && aux->esquerda == NULL){
				delete->esquerda=NULL;
				free(aux);
			}
			else if(aux->direita == NULL && aux->esquerda != NULL){
				delete->esquerda=aux->esquerda;
				free(aux);
			}
			else if(aux->direita != NULL && aux->esquerda == NULL){
				delete->esquerda=aux->direita;
				free(aux);
			}
			else{
				Arvore *i;
				for(i=aux->direita; i->esquerda->esquerda != NULL; i=i->esquerda);
				aux->valor=i->esquerda->valor;
				aux=i->esquerda;
				i->esquerda=NULL;
				free(aux);
			}
		}
		else{
			//printf("Elemento da direita\n");
			aux=delete->direita;
			if(aux->direita == NULL && aux->esquerda == NULL){
				delete->direita=NULL;
				free(aux);
			}
			else if(aux->direita == NULL && aux->esquerda != NULL){
				delete->direita=aux->esquerda;
				free(aux);
			}
			else if(aux->direita != NULL && aux->esquerda == NULL){
				delete->direita=aux->direita;
				free(aux);
			}
			else{
				Arvore *i;
				for(i=aux->direita; i->esquerda->esquerda != NULL; i=i->esquerda);
				aux->valor=i->esquerda->valor;
				aux=i->esquerda;
				i->esquerda=NULL;
				free(aux);
			}
		}
	}
	return arvore;
}
void searchValue(Arvore *arvore, int valor){
	int i=1;
	Arvore * aux = busca(arvore, valor, &i);
	if(aux!=NULL){
		if(arvore == aux){
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
	//int tam = tamanho(arvore);
	int h = altura(arvore);
	int nivel = 1;
	//char path[255] = {};
//	imprimeLinha(arvore, 0, path, 0); // função de imprimir a arvore na horizontal
	imprimiArvore (arvore, h, nivel);
	printf("\n");
}


void imprimiArvore(Arvore *arvore, int altura, int nivel){
	int qnt_espacos_esqueda = espacos_esquerda(altura, nivel)+1;

	for (int i=0; i<qnt_espacos_esqueda; i++)
		printf(" ");

	imprimi_elementos(arvore, altura, nivel, 1);

	if (altura == nivel)
		return;
	printf("\n");
																			
	int espacos = espacos_esquerda(altura, nivel)/2;

	for (int i=0; i<espacos; i++){
			printf(" ");
	}
	
	imprimi_barras (arvore, altura, nivel, 1);
	printf("\n");
	
	return imprimiArvore (arvore, altura, nivel+1);
}


void imprimi_elementos(Arvore *arvore, int altura, int nivel, int nivel_atual){
	if (nivel == 1){
		printf("%d", arvore->valor);
		return;
	}
	if (arvore == NULL){
		// if (nivel == nivel_atual)
			printf(" ");
		for (int i=nivel_atual; i<=nivel; i++){
			int espacos = espacos_entre_elementos(altura, nivel)+1; //imprimi os espaços entre os dois elementos
			for (int i=0; i<espacos; i++){
				printf(" ");
			}
		}
		return;
	}
	if (nivel == nivel_atual){
		printf("%d", arvore->valor);

		int espacos = espacos_entre_elementos(altura, nivel)+1; //imprimi os espaços entre os dois elementos
		for (int i=0; i<espacos; i++){
			printf(" ");
		}

		return;
	}
	else {
		imprimi_elementos(arvore->esquerda, altura, nivel, nivel_atual+1);
		// if (nivel == nivel_atual+1){
		// 	int espacos = espacos_entre_elementos(altura, nivel); //imprimi os espaços entre os dois elementos

		// 	for (int i=0; i<espacos; i++){
		// 		printf(" ");
		// 	}
		// }
		imprimi_elementos(arvore->direita, altura, nivel, nivel_atual+1);
		// if (nivel == nivel_atual+1){
		// 	int espacos = espacos_entre_elementos(altura, nivel)+2; //imprimi os espaços entre dois nos

		// 	for (int i=0; i<espacos; i++){
		// 		printf(" ");
		// 	}
		// }
		return;
	}

}


int espacos_esquerda(int altura, int nivel){
	if (altura == nivel)
		return 0;
	return (espacos_esquerda(altura, nivel+1)+1)*2;
}


int espacos_entre_elementos(int altura, int nivel){
	if (altura == nivel)
		return 2;
	return (espacos_entre_elementos(altura, nivel+1)+1)*2;
}


void imprimi_barras(Arvore *arvore, int altura, int nivel, int nivel_atual){
	if (nivel == 1){

		if (arvore->esquerda != NULL)
			printf("/");
		else
			printf(" ");

		int espaco = espacos_entre_elementos (altura, nivel+1); // calculando o espaço entre as barras
																			// printf("teste16\n");

		for (int i = 0; i<espaco; ++i)
			printf(" ");

		if (arvore->direita != NULL)
			printf("\\");
		else
			printf(" ");

		return;
	}

	if (arvore == NULL){
		// if (nivel == nivel_atual)
			printf(" ");  // representando o espaço da primeira barra
			int espaco = espacos_entre_elementos (altura, nivel+1); // calculando o espaço entre as barras
			for (int i = 0; i<espaco; ++i)
				printf(" ");

			printf(" ");  // representando o espaço da segunda barra

			espaco = espacos_entre_elementos(altura, nivel+1)+2; //calculando o espaço entre um conjunto de barras
			for (int i = 0; i<espaco; ++i)
				printf(" ");
		return;
	}
	if (nivel == nivel_atual){

		if (arvore->esquerda != NULL)
			printf("/");
		else
			printf(" ");

		int espaco = espacos_entre_elementos (altura, nivel+1); // calculando o espaço entre as barras
		for (int i = 0; i<espaco; ++i)
			printf(" ");

		if (arvore->direita != NULL)
			printf("\\");
		else
			printf(" ");
		// printf("a");

		espaco = espacos_entre_elementos(altura, nivel+1)+2; //calculando o espaço entre um conjunto de barras
			for (int i = 0; i<espaco; ++i)
				printf(" ");
		return;
	}
	else {

		imprimi_barras(arvore->esquerda, altura, nivel, nivel_atual+1);
		// if (nivel == nivel_atual+1){
		// 	int espaco = espacos_entre_elementos(altura, nivel+1)+2; //calculando o espaço entre um conjunto de barras
		// 	for (int i = 0; i<espaco; ++i)
		// 		printf(" ");
		// }
		imprimi_barras(arvore->direita, altura, nivel, nivel_atual+1);
	}
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
