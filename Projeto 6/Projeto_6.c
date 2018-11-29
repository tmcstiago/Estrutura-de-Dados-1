#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

typedef struct neuronio {
	double valor;
	struct neuronio *proximo;
	struct lista * w;
} Neuronio;

typedef struct camada {
	double b;
	int tamanho;
	struct neuronio *inicio;
	struct neuronio *fim;
} Camada;

typedef struct lista {
	int tamanho;
	struct elemento *inicio;
	struct elemento *fim;
} Lista;

typedef struct elemento {
	double valor;
	struct elemento *proximo;
} Elemento;

int random_number(int start, int end); //Gera número aleatório dentro do intervalo indicado, incluindo intervalo
Camada * camada_vazia();
Lista * lista_vazia();
void insere_neuronio(Camada * camada, double valor, Lista * w);
void insere_elemento(Lista * lista, double valor);
void free_lista(Lista *lista);
void free_camada(Camada *camada);

Lista * ler_imagem(char *path, int linha);
double tan_h(double value);

void transferencia(Camada *u, Lista *v);
//double funcao_ativacao(Camada *p, Camada *w, int b);

int main(int argc, char *argv[]){
	//Comando usado para que números gerados dentro do programa sejam aleatórios 
	srand(time(NULL));
	if(argv[1] == NULL){
		printf("É preciso passar o número de neurônios\nex.: $ %s 10\n", argv[0]);
		exit(-1);
	}
	int n_neuronios = atoi(argv[1]); //Pega o primeiro argumento ao rodar o código
	Lista * imagem = ler_imagem("a1.txt", 2); //Lê imagem e passa para Lista

	// Criação do vetor W [0, 1, 2, 3, 4, 5]
	

	//Criação da camada oculta com valores crescentes, e w criado acima para cada neurônio
	Camada * camada_oculta = camada_vazia();
	for(int i=0; i<n_neuronios; i++){
		Lista * w = lista_vazia();
		for(int i=0; i<6; i++)
			insere_elemento(w, random_number(-200,200));
		insere_neuronio(camada_oculta, i, w);
	}

	transferencia(camada_oculta, imagem);

	printf("Vetor entrada:\n");
	Elemento * atual=imagem->inicio;
	for(int i=0; i<imagem->tamanho; i++, atual=atual->proximo){
		printf("%.2lf ", atual->valor);
	}
	printf("\n");

	printf("Camada Oculta:\n");
	printf("b=%.2lf\n", camada_oculta->b);
	Neuronio * n_atual=camada_oculta->inicio;
	for(int i=0; i<camada_oculta->tamanho; i++, n_atual=n_atual->proximo){
		printf("%.2lf ", n_atual->valor);
	}
	printf("\n");
	
	free_lista(imagem);
	free_camada(camada_oculta);
	return 0;
}

int random_number(int start, int end){
	int number, diff;
	diff = end-start;
	number = rand()%(diff+1)+start;
	return number;
}

Camada * camada_vazia(){

	Camada * camada;
	camada = (Camada *) malloc(sizeof(Camada));
	if(camada==NULL){
		printf("Alocação falhou");
		exit(-1);
	}
	camada->inicio=NULL;
	camada->fim=NULL;
	camada->tamanho=0;
	camada->b=0;
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

void insere_neuronio(Camada * camada, double valor, Lista * w){
	Neuronio * novo_neuronio;
	novo_neuronio = (Neuronio *) malloc(sizeof(Neuronio));
	if(novo_neuronio==NULL){
		printf("Alocação falhou");
		exit(-1);
	}
	novo_neuronio->valor=valor;
	novo_neuronio->proximo=NULL;
	novo_neuronio->w=w;

	if(camada->tamanho==0){
		camada->inicio=novo_neuronio;
		camada->fim=novo_neuronio;
		camada->tamanho++;
	}
	else{
		camada->fim->proximo=novo_neuronio;
		camada->fim=novo_neuronio;
		camada->tamanho++;
	}
}

void insere_elemento(Lista * lista, double valor){
	Elemento * novo_valor;
	novo_valor = (Elemento *) malloc(sizeof(Elemento));
	if(novo_valor==NULL){
		printf("Alocação falhou");
		exit(-1);
	}
	novo_valor->valor=valor;
	novo_valor->proximo=NULL;

	if(lista->tamanho==0){
		lista->inicio=novo_valor;
		lista->fim=novo_valor;
		lista->tamanho++;
	}
	else{
		lista->fim->proximo=novo_valor;
		lista->fim=novo_valor;
		lista->tamanho++;
	}
}

void free_lista(Lista *lista){
	Elemento * atual=lista->inicio;
	Elemento * limpar=atual->proximo;
	for(int i=0; i<lista->tamanho; i++, atual=atual->proximo){
		free(limpar);
	}
	free(atual);
	free(lista);
}

void free_camada(Camada *camada){
	Neuronio * atual=camada->inicio;
	Neuronio * limpar=atual->proximo;
	for(int i=0; i<camada->tamanho; i++, atual=atual->proximo){
		free(limpar->w);
		free(limpar);
	}
	free(atual);
	free(camada);

}

Lista * ler_imagem(char *path, int linha){
	FILE *arquivo;
	arquivo = fopen(path, "r");
	if (arquivo == NULL){
		printf("Erro na leitura do arquivo\n");
		return NULL;
	}
	char aux;
	for(int i=1; i<linha; ){
		if(fscanf(arquivo,"%c", &aux)!=EOF){
			if(aux=='\n')
				i++;
		}
		else{
			printf("Erro na leitura do arquivo\n");
			return NULL;
		}
	}
	Lista * imagem = lista_vazia();
	double value;
	while(fscanf(arquivo,"%lf%c", &value, &aux)!=EOF){
		insere_elemento(imagem, value);
		if(aux=='\n'){
			return imagem;
		}
	}
	return imagem;
}

void transferencia(Camada *u, Lista *v){
	//Criação do vetor de transferência v
	Neuronio * u_atual=u->inicio;
	if(u_atual->w->tamanho != v->tamanho){
		printf("Erro na função de transferencia\n");
		exit(-1);
	}
	for(int i=0 ; i<u->tamanho ; u_atual=u_atual->proximo, i++){
		Elemento *w_atual=u_atual->w->inicio;
		Elemento *v_atual=v->inicio;
		u_atual->valor=0;
		for(int j=0; j<v->tamanho; j++, w_atual=w_atual->proximo, v_atual=v_atual->proximo){
			if(i==0){
				u_atual->valor=u->b;
				break;
			}
			u_atual->valor+=(w_atual->valor)*(v_atual->valor);
		}
	}

}
double tan_h(double value){
	return (pow(M_E, value) - pow(M_E, value*(-1)))/(pow(M_E, value) + pow(M_E, value*(-1)));
}

/*
double funcao_ativacao(Camada *p, Camada *w, int b){
	if(p->tamanho != w->tamanho){
		printf("Erro na função de ativação\n");
		exit(-1);
	}
	
	Neuronio * p_atual=p->inicio;
	Neuronio * w_atual=w->inicio;
	double n=b;
	for(int i=0 ; i<p->tamanho ; p_atual=p_atual->proximo, w_atual=w_atual->proximo, i++){
		n += p_atual->valor*w_atual->valor;
	}

	double s;
	s=1/(1+pow(M_E, (-1)*n));
	
	return s;
}
*/
