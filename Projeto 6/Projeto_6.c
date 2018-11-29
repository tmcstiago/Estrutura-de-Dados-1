#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#define IMAGES_PATH "imagem_estabilizada.txt"

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
void generate_random_numbers(int * vector, int start, int end); // Gera 50 valores distintos dentro do intervalo e armazena em vector
double tan_h(double value);

void transferencia(Camada *u, Lista *v);
void ativacao(Camada *saida, Camada *u);

int main(int argc, char *argv[]){
	//Comando usado para que números gerados dentro do programa sejam aleatórios 
	srand(time(NULL));
	if(argv[1] == NULL){
		printf("É preciso passar o número de neurônios\nex.: $ %s 10\n", argv[0]);
		exit(-1);
	}
	int n_neuronios = atoi(argv[1]); //Pega o primeiro argumento ao rodar o código

	//Criação dos vetores para sortear as imagens
	int n_grama[50],  n_asfalto[50];
	generate_random_numbers(n_grama, 1, 50);
	generate_random_numbers(n_asfalto, 51, 100);

	//Armazenamento das imagens
	Lista * grama[50], * asfalto[50];
	for(int i=0; i<50; i++){
		grama[i]=ler_imagem(IMAGES_PATH, n_grama[i]);
		asfalto[i]=ler_imagem(IMAGES_PATH, n_asfalto[i]);
	}

	//Criação da camada oculta com valores aleatôrios, e w aleatôrio para cada neurônio
	Camada * camada_oculta = camada_vazia();
	for(int i=0; i<n_neuronios; i++){
		Lista * w = lista_vazia();
		// Criação do vetor W aleatório
		for(int i=0; i<grama[0]->tamanho; i++)
			insere_elemento(w, random_number(-200,200));
		insere_neuronio(camada_oculta, random_number(-200,200) , w);
	}

	
	//Criação da camada de saída com um único neurônio de valor 0
	Camada * camada_saida = camada_vazia();
	Lista * w = lista_vazia();
	for(int i=0; i<camada_oculta->tamanho; i++)
		insere_elemento(w, random_number(-200,200));
	insere_neuronio(camada_saida, 0, w);
	
	//Época com 25 imagens de cada tipo
	double erro[50];
	for(int i=0; i<50; i++)
		erro[i]=0;

	double result;
	for(int i=0; i<25; i++){
		//Procedimento com grama
		transferencia(camada_oculta, grama[i]);
		ativacao(camada_saida, camada_oculta);
		result = camada_saida->inicio->valor;
		erro[i]=1-result;
		printf("Procedimento %d\nValor Obitido para grama:%.2lf\tEsperado:1.00\nErro:%lf\n", i+1 , result, erro[i]);

		//Procedimento com asfalto
		transferencia(camada_oculta, asfalto[i]);
		ativacao(camada_saida, camada_oculta);
		result = camada_saida->inicio->valor;
		erro[i+25]=0-result;
		printf("Valor Obitido para asfalto:%.2lf\tEsperado:0.00\nErro:%lf\n\n", result, erro[i+25]);
	}
	double media=0;
	for(int i=0; i<50; i++)
		media+=erro[i];
	media/=50;
	printf("Média de erro:%lf\n", media);

	free_camada(camada_oculta);
	free_camada(camada_saida);

	for(int i=0; i<50; i++){
		free_lista(grama[i]);
		free_lista(asfalto[i]);
	}
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
	if(lista->tamanho == 0){
		printf("Lista tamanho 0\n");
		free(lista);
		return;
	}
	else if(lista->tamanho == 1){
		printf("Lista tamanho 1\n");
		free(atual);
		free(lista);
		return;
	}
	else{
		Elemento * limpar=atual;
		atual=atual->proximo;
		for(; atual->proximo!=NULL; atual=atual->proximo){
			free(limpar);
			limpar=atual;
		}
		free(atual);
		free(lista);
		return;
	}
}

void free_camada(Camada *camada){
	Neuronio * atual=camada->inicio;
	if(camada->tamanho == 0){
		free(camada);
		return;
	}
	else if(camada->tamanho == 1){
		free_lista(atual->w);
		free(atual);	
		free(camada);
		return;
	}
	else{
		Neuronio * limpar=atual;
		atual=atual->proximo;
		for(; atual->proximo!=NULL ; atual=atual->proximo){
			free_lista(limpar->w);
			free(limpar);
			limpar=atual;
		}
		free_lista(atual->w);
		free(atual);
		free(camada);
		return;
	}
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

void generate_random_numbers(int * vector, int start, int end){
	int memory[50];
	int i, j;
	for(i=start, j=0; i<=end; i++, j++){
		memory[j]=i;
		//printf("%d ", memory[j]);
	}
	//printf("\n");
	for(i=0; i<50; i++){
		int num=random_number(0, (49-i));
		//printf("%d ", num);
		vector[i]=memory[num];
		for(int j=num; j<50-i; j++){
			memory[j]=memory[j+1];
		}
	}
	//printf("\n\n");
}

double tan_h(double value){
	return (pow(M_E, value) - pow(M_E, value*(-1)))/(pow(M_E, value) + pow(M_E, value*(-1)));
}

void transferencia(Camada *u, Lista *v){

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

void ativacao(Camada *saida, Camada *u){
	Neuronio * u_atual=u->inicio;
	Neuronio * n_saida = saida->inicio;
	if(u->tamanho != n_saida->w->tamanho){
		printf("Erro na função de ativacao\n");
		exit(-1);
	}
	double n=saida->b;
	Elemento * w_atual=n_saida->w->inicio;
	for(int i=0 ; i<u->tamanho ; u_atual=u_atual->proximo, w_atual=w_atual->proximo, i++){
		n += u_atual->valor*w_atual->valor;
	}

	n_saida->valor = 1/(1+pow(M_E, (-1)*n));
	
}
