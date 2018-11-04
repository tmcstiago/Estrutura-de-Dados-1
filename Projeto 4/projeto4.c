#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define UNIDADE_TEMPO 5
#define APROXIMACAO 1
#define POUSO 3
#define DECOLAGEM 2

typedef struct lista {
	char codigo[10];
	char modo;
	int combustivel;
	struct lista *proximo;
} Lista;

typedef struct fila {
	Lista *inicio;
	Lista *fim;
} Fila;

typedef struct pista {
	char modo;
	int tempo_apx;
	int tempo_pouso;
	int tempo_decolagem;
	int is_free;
} Pista;

//Lista *aux;

Fila *iniciar_fila();
void novo_voo(Fila *voos, Lista *novo);
//Retorna um voo da fila
Lista * pop(Fila *);
//Retorna da fila um voo de decolagem
Lista * pop_d(Fila *voos);

void mensagem_inicial(int n_voos ,int n_aproximacoes, int n_decolagens, int tempo);
void mensagem_voo(int tempo, int pista, Lista *voo);
void verificando_pistas(Pista *pista1, Pista *pista2, Pista *pista3);
void voos_prioritarios(Fila *voos, Pista *pista1, Pista *pista2, Pista *pista3, int ut);
void voos_sequencia(Fila *voos, Pista *pista1, Pista *pista2, Pista *pista3, int ut);
void altecao_combustivel(Fila *voos);
int random_number(int start, int end);
void data_generate(Fila *voos, int * n_voos,int * n_aproximacoes, int *n_decolagens);

int main () {
	//Comando usado para que números gerados dentro do programa sejam aleatórios 
	srand(time(NULL)); 

	Fila *voos = iniciar_fila();  // criando a cabeça da fila
	int n_voos;
	int n_aproximacoes;
	int n_decolagens;

	data_generate(voos, &n_voos, &n_aproximacoes, &n_decolagens);

	Pista *pista1, *pista2, *pista3;
	pista1 = (Pista *) malloc(sizeof(Pista));
	if(pista1 == NULL){
		printf("Alocação falhou");
		exit(-1);
	}
	pista1->is_free=1;
	pista2 = (Pista *) malloc(sizeof(Pista));
	if(pista2 == NULL){
		printf("Alocação falhou");
		exit(-1);
	}
	pista2->is_free=1;
	pista3 = (Pista *) malloc(sizeof(Pista));
	if(pista3 == NULL){
		printf("Alocação falhou");
		exit(-1);
	}
	pista3->is_free=1;
	//Tempo atual em minutos
	int tempo = random_number(0,24*60);

	mensagem_inicial(n_voos,n_aproximacoes, n_decolagens, tempo);
	
	for (int t=0;; ++t, tempo+=UNIDADE_TEMPO) { // t = unidade de tempo = 5 min
		//printf("t:%d\n", t);
		getchar();
		// verificando se pode liberar alguma pista
		verificando_pistas(pista1, pista2, pista3);
		Lista *aeronave;
		//printf("1\n");
		if(pista1->is_free){
			aeronave=pop(voos);
			if(aeronave==NULL){
				free(voos);
				free(pista1);
				free(pista2);
				free(pista3);
				return 0;
			}

			pista1->modo=aeronave->modo;
			pista1->tempo_apx=APROXIMACAO;
			pista1->tempo_pouso=POUSO;
			pista1->tempo_decolagem=DECOLAGEM;
			pista1->is_free=0;

			mensagem_voo(tempo, 1, aeronave);
			free(aeronave);
		}
		if(pista2->is_free){
			aeronave=pop(voos);
			if(aeronave==NULL){
				free(pista1);
				free(pista2);
				free(pista3);
				free (voos);
				return 0;
			}

			pista2->modo=aeronave->modo;
			pista2->tempo_apx=APROXIMACAO;
			pista2->tempo_pouso=POUSO;
			pista2->tempo_decolagem=DECOLAGEM;
			pista2->is_free=0;

			mensagem_voo(tempo, 2, aeronave);
			free(aeronave);
		}
		if(pista3->is_free){
			aeronave=pop_d(voos);
			if(aeronave==NULL){
				free (voos);
				free(pista1);
				free(pista2);
				free(pista3);
				return 0;
			}
			pista3 = (Pista *) malloc(sizeof(Pista));
			if(pista3 == NULL){
				printf("Alocação falhou");
				exit(-1);
			}
			pista3->modo=aeronave->modo;
			pista3->tempo_apx=APROXIMACAO;
			pista3->tempo_pouso=POUSO;
			pista3->tempo_decolagem=DECOLAGEM;
			pista3->is_free=0;

			mensagem_voo(tempo, 3, aeronave);
			free(aeronave);
		}
		if (t%10==0 && t!=0) {
			
			altecao_combustivel(voos);
		}
	}
}
//Gera número aleatório dentro do intervalo indicado, incluindo intervalo
int random_number(int start, int end){
	int number, diff;
	diff = end-start;
	number = rand()%(diff+1)+start;
	return number;
}
void data_generate(Fila *voos, int *n_voos, int *n_aproximacoes, int *n_decolagens){

	(*n_voos) = random_number(20, 64);
	(*n_aproximacoes) = random_number(10, (*n_voos)-10);
	(*n_decolagens) = (*n_voos) - (*n_aproximacoes);

	//(*n_voos) = 42;
	//(*n_aproximacoes) = 12;
	//(*n_decolagens) = 40;
	//printf("n_voos:%d,\nn_aproximacoes:%d,\nn_decolagens:%d\n", (*n_voos), (*n_aproximacoes), (*n_decolagens));

	char *codigos[] = {
		"VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008", 
		"AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012", "TT4544", 
		"TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002", "AZ1007", "GL7604", 
		"AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001", "LN7003", "AZ1004", "TG1504", 
		"AZ1005", "TG1502", "GL7601", "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", 
		"VV3390", "VV3392", "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", 
		"AZ1065", "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510", 
		"TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609", "KL5610", "KL5611",
	};
	
	Lista *f;

	for(int i=0; i<=(*n_aproximacoes); i++){
		f = (Lista *) malloc(sizeof(Lista));
		if(f==NULL){
			printf("Alocação falhou");
			exit(-1);
		}
		strcpy(f->codigo, codigos[i]);
		f->modo='A';
		f->combustivel=random_number(0,12);
		//f->combustivel=0;
		//printf("Vôo %02d\nCódigo:%s\nModo:%c\nCombustível:%d\n", i+1, f->codigo, f->modo, f->combustivel);
		novo_voo(voos, f);
	}
	for(int i=(*n_aproximacoes)+1; i<(*n_voos); i++){
		f = (Lista *) malloc(sizeof(Lista));
		if(f==NULL){
			printf("Alocação falhou");
			exit(-1);
		}
		strcpy(f->codigo, codigos[i]);
		f->modo='D';
		//printf("Vôo %02d\nCódigo:%s\nModo:%c\n", i+1, f->codigo, f->modo);
		novo_voo(voos, f);
	}
	//printf("Fim da função generate\n");
}

Fila *iniciar_fila(){
	Fila *f;
	f = (Fila *) malloc(sizeof(Fila));
	if(f==NULL){
		printf("Alocação falhou");
		exit(-1);
	}

	f->inicio = NULL;
	f->fim = NULL;

	return f;
}
Lista * pop_d(Fila *voos){
	Lista * aux;
	//Caso o primeiro da fila seja do tipo D
	if(voos->inicio->modo=='D'){
		return pop(voos);
	}
	if(voos->inicio->modo=='A' && voos->inicio->combustivel==0){
		printf("\nALERTA GERAL DE DESVIO DE AERONAVE\n");
		return pop(voos);
	}
	//Fila não vazia que contem pelo menos 1 voo do tipo 'D'
	if(voos->fim != NULL && voos->fim->modo=='D'){
		//printf("voos->fim->modo:%c\n", voos->fim->modo);
		Lista * atual;
		Lista * aux;
		atual=voos->inicio;	
		//Percorre fila até encontrar um voo tipo D
		for(;atual->proximo->modo!='D'; atual=atual->proximo);
		aux=atual->proximo;
		atual->proximo=aux->proximo;
		aux->proximo=NULL;
		//Caso esteja retirando o único elemento da fila
		if(aux==voos->fim && aux==voos->inicio){
			voos->fim=NULL;
			voos->inicio=NULL;
		}
		//Caso esteja retirando o último da fila
		else if(aux==voos->fim){
			voos->fim=atual;
		}
		return aux;		
	}
	//Fila vazia ou não contem voos de decolagem 
	else{
		return NULL;
	}
}
Lista * pop(Fila *voos){
	Lista * aux;
	//Fila não vazia
	if(voos->inicio != NULL){
		aux = voos->inicio;
		//Fila com 2 ou mais elementos
		if(voos->inicio != voos->fim){
			voos->inicio=voos->inicio->proximo;
		}
		//Fila com 1 elementro
		else{
			voos->inicio=NULL;
			voos->fim=NULL;
		}
		return aux;	
	}
	//Fila vazia
	else{
		return NULL;
	}	
}

void novo_voo(Fila *voos, Lista *novo){
	novo->proximo=NULL;
	if (voos->inicio == NULL){
		//printf("Nenhum voo, Adicionando voo %s\n\n", novo->codigo);
		voos->inicio = novo;
		voos->fim = novo;
	}
	else {
		//printf("Já possui voos, Adicionando voo %s\n", novo->codigo);
		//Voo com prioridade
		if(novo->modo == 'A'){
			//printf("Voo com prioridade, ");
				
			//Caso o novo tenha menos prioridade que toda a fila
			if(voos->fim->modo == 'A' && (voos->fim->combustivel)<=(novo->combustivel)){
				//printf("Menos prioridade que toda a fila");
				voos->fim->proximo=novo;
				voos->fim = novo;
			}
			//Caso o novo tenha mais prioridade que o primeiro voo
			else if((voos->inicio->modo!='A') || (voos->inicio->combustivel)>=(novo->combustivel)){
				//printf("Mais prioridade que toda fila");
				novo->proximo=voos->inicio;
				voos->inicio=novo;
			}
			//Caso contrário
			else{
				//printf("Encaixando no meio da fila");	
				Lista * atual;
				atual=voos->inicio;	
				//Percorre fila até encontrar lugar certo
				for(;atual->proximo->modo=='A' && (novo->combustivel)>(atual->proximo->combustivel); 
					atual=atual->proximo);
		
				novo->proximo=atual->proximo;
				atual->proximo=novo;	
			}	
			//printf("\n\n");
				
		}
		//Voo sem prioridade
		else{
			//printf("Voo sem prioridade\n\n");
			voos->fim->proximo = novo;
			voos->fim = novo;
		}


		
	}
}


void mensagem_inicial(int n_voos ,int n_aproximacoes, int n_decolagens, int tempo) {
	printf("---------------------------------------------------------------------------------\n");
	printf("“Aeroporto Internacional de Brasília”\n");
	int hora=(tempo/60)%24;
	int min=tempo%60;
	printf("Hora Inicial: %02d:%02d\n", hora, min);
	printf("Fila de Pedidos:\n"); //verificar qual texto complementar deve ser colocado
	printf("NVoos: %d\n", n_voos);
	printf("NAproximações: %d\n", n_aproximacoes);
	printf("NDecolagens: %d\n", n_decolagens);
	printf("---------------------------------------------------------------------------------\n");
}


void mensagem_voo(int tempo, int pista, Lista *voo){
	int hora=(tempo/60)%24;
	int min=tempo%60;

	printf("\nCódigo do voo: %s\n", voo->codigo);
	if (voo->modo == 'A')
		printf("Status: Aeronave Pousou\n");
	else
		printf("Status: Aeronave Decolou\n");
	printf("Horário do início do procedimento: %02d:%02d\n", hora, min);
	printf("Numero da Pista: %d\n", pista);
}


void verificando_pistas(Pista *pista1, Pista *pista2, Pista *pista3){
	//printf("VERIFICANDO PISTAS...");
	//verificando a pista 1
	if(!pista1->is_free){
		//printf("Pista 1...\n");
		if (pista1->modo == 'A'){

			if (pista1->tempo_apx > 0){
				pista1->tempo_apx --;
			}
			else{
				pista1->tempo_pouso --;

				if(pista1->tempo_pouso <= 0){
					pista1->is_free=1;
				}
			}
		}
		else{

			pista1->tempo_decolagem--;

			if(pista1->tempo_decolagem <= 0){
				pista1->is_free=1;
			}
		}
	}
	// verificando a pista 2
	if(!pista2->is_free){
		//printf("Pista 2...");
		if (pista2->modo == 'A'){

			if (pista2->tempo_apx > 0){
				pista2->tempo_apx --;
			}
			else{
				pista2->tempo_pouso --;

				if(pista2->tempo_pouso == 0){
					pista2->is_free=1;
				}
			}
		}
		else{
			pista2->tempo_decolagem--;

			if(pista2->tempo_decolagem == 0){		
				pista2->is_free=1;
			}
		}
	}
	//verificando a pista 3
	if(!pista3->is_free){
		if (pista3->modo == 'A'){
			if (pista3->tempo_apx > 0){
				pista3->tempo_apx --;
			}
			else{
				pista3->tempo_pouso --;

				if(pista3->tempo_pouso == 0){				
					pista3->is_free=1;
				}
			}
		}
		else{
			pista3->tempo_decolagem--;

			if(pista3->tempo_decolagem == 0){		
				pista3->is_free=1;
			}
		}
	}
}

void altecao_combustivel(Fila *voos) {
	Lista *atual;	
	for (atual = voos->inicio; atual != NULL && atual->modo=='A'; atual = atual->proximo){
		atual->combustivel --;

		if (atual->combustivel < 0) {
			Lista *excluir;
			Lista *aux;
			excluir = atual;

			if (atual == voos->inicio){
				excluir=voos->inicio;
				voos->inicio = atual->proximo;
			}
			else {
				for (aux = voos->inicio; aux->proximo != excluir; aux = aux->proximo);
				aux->proximo = excluir->proximo;
				if(excluir==voos->fim)
					voos->fim=atual;

			}

			printf("\nALERTA CRÍTICO, AERONAVE %s IRÁ CAIR\n", excluir->codigo);
			free(excluir);
		}
	}
}
