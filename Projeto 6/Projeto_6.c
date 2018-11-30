#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#define IMAGES_PATH "imagem_estabilizada.txt"
#define GRAMA 1
#define ASFALTO 0

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
	int tipo; //Usado apenas nas listas de imagens
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

Lista * ler_imagem(char *path, int linha, int tipo);
void generate_random_numbers(int * vector, int start, int tam); // Gera 50 valores distintos dentro do intervalo e armazena em vector
double funcao_logistica(double value);
double d_dx_funcao_logistica(double value);

void transferencia(Camada *u, Lista *v); // Realiza a transferência de um vetor V para uma camada U e retorna vetor V da camada que recebe transferência
void ativacao(Camada *saida, Camada *u);
void backprogramation(Camada * camada_saida, Camada * camada_oculta, double erro);

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
	generate_random_numbers(n_asfalto, 51, 50);

	//Armazenamento das imagens
	Lista * imagem_treinamento[50];
	for(int i=0; i<50; i+=2){
		imagem_treinamento[i]=ler_imagem(IMAGES_PATH, n_grama[i], GRAMA);
		imagem_treinamento[i+1]=ler_imagem(IMAGES_PATH, n_asfalto[i], ASFALTO);
	}
	Lista * imagem_teste[50];
	for(int i=0; i<50; i+=2){
		imagem_teste[i]=ler_imagem(IMAGES_PATH, n_grama[i], GRAMA);
		imagem_teste[i+1]=ler_imagem(IMAGES_PATH, n_asfalto[i], ASFALTO);
	}

	//Criação da camada oculta com valores aleatôrios, e w aleatôrio para cada neurônio
	Camada * camada_oculta = camada_vazia();
	for(int i=0; i<n_neuronios; i++){
		Lista * w = lista_vazia();
		// Criação do vetor W aleatório
		for(int i=0; i<imagem_treinamento[0]->tamanho; i++)
			insere_elemento(w, rand());
		insere_neuronio(camada_oculta, rand() , w);
	}
	
	// Criação da camada de saída com um único neurônio de valor 0
	Camada * camada_saida = camada_vazia();
	Lista * w = lista_vazia();
	for(int i=0; i<camada_oculta->tamanho; i++)
		insere_elemento(w, rand());
	insere_neuronio(camada_saida, 0, w);
	
	//Época com 25 imagens de cada tipo
	int epoca=0; // Número da época
	double erro_medio;
	do{
		printf("Época: %d\n", epoca+1);
		double erro[50];
		for(int i=0; i<50; i++)
			erro[i]=0;

		double result;
		int valor_imagem[50]; // Armazena valores aleatórios para serem escolhidos no treinamento
		generate_random_numbers(valor_imagem, 0, 50);
		for(int i=0; i<50; i++){
			//Procedimento com grama
			transferencia(camada_oculta, imagem_treinamento[valor_imagem[i]]);
			ativacao(camada_saida, camada_oculta);
			result = camada_saida->inicio->valor;
			double valor_esperado = imagem_treinamento[valor_imagem[i]]->tipo;
			erro[i]=valor_esperado-result;
			backprogramation(camada_saida, camada_oculta, erro[i]);
			printf("Procedimento %d\nValor obitido:%.2lf\tValor esperado:%.2lf\nErro:%lf\n\n", i+1 , result, valor_esperado, erro[i]);

		}
		erro_medio=0;
		for(int i=0; i<50; i++)
			erro_medio+=erro[i];
		erro_medio/=50;
		if(erro_medio<0)
			erro_medio*=-1;
		printf("Módulo da média de erro:%lf\n", erro_medio);

		float acerto = 0;
		float falsa_aceitacao = 0;
		float falsa_rejeicao = 0;
		printf ("Taxa de acerto = %.2f %%\n", acerto*100);
		printf ("Taxa de falsa aceitacao = %.2f %%\n", falsa_aceitacao*100);
		printf ("Taxa de falsa rejeicao = %.2f %%\n", falsa_rejeicao*100);
		epoca++;
	}while(epoca<1000 && erro_medio>0.2);

	free_camada(camada_oculta);
	free_camada(camada_saida);

	for(int i=0; i<50; i++){
		free_lista(imagem_treinamento[i]);
		free_lista(imagem_teste[i]);
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

Lista * ler_imagem(char *path, int linha, int tipo){
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
	imagem->tipo=tipo;
	double value;
	while(fscanf(arquivo,"%lf%c", &value, &aux)!=EOF){
		insere_elemento(imagem, value);
		if(aux=='\n'){
			return imagem;
		}
	}
	return imagem;
}

void generate_random_numbers(int * vector, int start, int tam){
	int * memory;
	memory = (int *) malloc(tam*sizeof(int));
	if(memory==NULL){
		printf("Alocação falhou");
		exit(-1);
	}
	int i, j;
	for(i=start, j=0; j<tam; i++, j++){
		memory[j]=i;
		//printf("%d ", memory[j]);
	}
	//printf("\n");
	for(i=0; i<tam; i++){
		int num=random_number(0, (tam-1-i));
		//printf("%d ", num);
		vector[i]=memory[num];
		for(int j=num; j<tam-i; j++){
			memory[j]=memory[j+1];
		}
	}
	free(memory);
	//printf("\n\n");
}

double funcao_logistica(double value){
	return 1/(1+pow(M_E, (-1)*value));
}

double d_dx_funcao_logistica(double value){
	return (pow(M_E, value))/pow((1+pow(M_E, value)), 2);
}

void transferencia(Camada *u, Lista *v){
	Lista * new_v = lista_vazia();
	Neuronio * u_atual=u->inicio;
	if(u_atual->w->tamanho != v->tamanho){
		printf("Erro na função de transferencia\n");
		exit(-1);
	}
	
	for(int i=0 ; i<u->tamanho ; u_atual=u_atual->proximo, i++){
		Elemento *w_atual=u_atual->w->inicio;
		Elemento *v_atual=v->inicio;
		u_atual->valor=u->b;
		for(int j=0; j<v->tamanho; j++, w_atual=w_atual->proximo, v_atual=v_atual->proximo){
			u_atual->valor+=(w_atual->valor)*(v_atual->valor);
			u_atual->valor= funcao_logistica(u_atual->valor);
		}
	}
}

void ativacao(Camada *saida, Camada *v){
	Neuronio * v_atual=v->inicio;
	Neuronio * n_saida = saida->inicio;
	if(v->tamanho != n_saida->w->tamanho){
		printf("Erro na função de ativacao\n");
		exit(-1);
	}
	double n=saida->b;
	Elemento * w_atual=n_saida->w->inicio;
	for(int i=0 ; i<v->tamanho ; v_atual=v_atual->proximo, w_atual=w_atual->proximo, i++){
		n += v_atual->valor*w_atual->valor;
	}

	n_saida->valor = funcao_logistica(n);
	
}
void backprogramation(Camada * camada_saida, Camada * camada_oculta, double erro){
	//Cálculo das derivadas
	double derivada_saida = d_dx_funcao_logistica(camada_saida->inicio->valor);
	//printf("Derivada saída:%lf\n", derivada_saida);
	Lista * v_dx = lista_vazia(); 
	for(Neuronio *atual = camada_oculta->inicio; atual->proximo!=NULL; atual=atual->proximo){
		insere_elemento(v_dx, d_dx_funcao_logistica(atual->valor)); //Derivadas da camada oculta
		//printf("Derivada:%lf\n", d_dx_funcao_logistica(atual->valor));
	}

	//Cálculo dos gradientes
	double gradiente_saida = derivada_saida*erro;
	Lista * gradiente_u = lista_vazia();
	Elemento * v_dx_atual=v_dx->inicio;
	Elemento * w_atual=camada_saida->inicio->w->inicio;
	printf("gradiente_saida:%.2lf\n", gradiente_saida);
	for(;v_dx_atual != NULL ; v_dx_atual=v_dx_atual->proximo, w_atual=w_atual->proximo){
		double gradiente = v_dx_atual->valor*(gradiente_saida*w_atual->valor);
		insere_elemento(gradiente_u, gradiente); //Lista de gradientes da camada oculta
		//printf("Gradiente:%.2lf\n", gradiente);
	}
	
	free_lista(gradiente_u);
	free_lista(v_dx);
}
