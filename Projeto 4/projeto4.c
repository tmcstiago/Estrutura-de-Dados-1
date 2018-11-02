#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
	char codigo[7];
	char modo;
	int combustivel;
	struct lista *proximo;
} Lista;

typedef struct fila {
	Lista *inicio;
	Lista *fim;
} Fila;

typedef struct pista {
	char codigo[7];
	char modo;
	int combustivel;
	int tempo_apx;
	int tempo_pouso;
	int tempo_decolagem;
} Pista;


Fila *iniciar_fila();
void novo_voo(Fila *voos, Lista *novo);

void mensagem_inicial(int hora, int min, int Naproximacoes, int Ndecolagens);
void verificando_pistas(Pista *pista1, Pista *pista2, Pista *pista3);
void voos_prioritarios(Fila *voos, Pista *pista1, Pista *pista2, Pista *pista3);
void altecao_combustivel(Fila *voos, Pista *pista1, Pista *pista2, Pista *pista3);



int main () {

	Fila *voos = iniciar_fila();  // criando a cabeça da fila
	
	// estas variaveis devem ser globais
	int Naproximacoes;
	int Ndecolagens;

	// função para gerar os voos e o combustível
	
	// utilize a função novo_voo(*Fila, * Lista) para criar novo voo, sendo Fila = voos e Lista obj criado
		// lembre que voce ja deve mandar o dado definido igual no projeto anterior
			// observação: ao chamar a função, o Lista ->proximo já deve ser igual a NULL



	//horario inicial do programa
	int hora = 6;
	int min = 0;

	// pistas de pouso e decolagem
	Pista *pista1 = NULL;
	Pista *pista2 = NULL;
	Pista *pista3 = NULL;

	mensagem_inicial(hora, min, Naproximacoes, Ndecolagens);

	for (int ut = 1; 1; ++ut) { // ut = unidade de tempo = 5 min
		scanf("%d", &min);
		// verificando se pode liberar alguma pista
		verificando_pistas(pista1, pista2, pista3);

		//verificando se tem algum voo com combustivel=0
		voos_prioritarios(voos, pista1, pista2, pista3);

		//diminuindo o combustivel dos avioes
		if (min%10 == 0) {
			altecao_combustivel(voos, pista1, pista2, pista3);
		}

	}

	return 0;
}


Fila *iniciar_fila(){
	Fila *f;
	f = (Fila *) malloc(sizeof(Fila));

	f->inicio = NULL;
	f->fim = NULL;

	return f;
}


void novo_voo(Fila *voos, Lista *novo){
	if (voos->inicio == NULL){
		voos->inicio == novo;
		voos->fim == novo;
	}
	else {
		voos->fim->proximo = novo;
		voos->fim = novo;
	}
}


void mensagem_inicial(int hora, int min, int Naproximacoes, int Ndecolagens) {
	printf("---------------------------------------------------------------------------------\n");
	printf("“Aeroporto Internacional de Brasília”\n");
	printf("Hora Inicial: %02d:%02d\n", hora, min);
	printf("Fila de Pedidos:\n"); //verificar qual texto complementar deve ser colocado
	printf("NVoos: %d\n", Naproximacoes + Ndecolagens);
	printf("NAproximações: %d\n", Naproximacoes);
	printf("NDecolagens: %d\n", Ndecolagens);
	printf("---------------------------------------------------------------------------------\n");
	printf("Listagem de eventos:\n\n");
}


void verificando_pistas(Pista *pista1, Pista *pista2, Pista *pista3){
	//verificando a pista 1
	if (pista1->modo == 'A'){
		if (pista1->tempo_apx > 0){
			pista1->tempo_apx --;
		}
		else{
			pista1->tempo_pouso --;

			if(pista1->tempo_pouso == 0){
				free (pista1);
				pista1 == NULL;
			}
		}
	}
	else{
		pista1->tempo_decolagem--;

		if(pista1->tempo_decolagem == 0){
			free (pista1);
			pista1 == NULL;
		}
	}

	// verificando a pista 2
	if (pista2->modo == 'A'){
		if (pista2->tempo_apx > 0){
			pista2->tempo_apx --;
		}
		else{
			pista2->tempo_pouso --;

			if(pista2->tempo_pouso == 0){
				free (pista2);
				pista2 == NULL;
			}
		}
	}
	else{
		pista2->tempo_decolagem--;

		if(pista2->tempo_decolagem == 0){
			free (pista2);
			pista2 == NULL;
		}
	}

	//verificando a pista 3
	if (pista3->modo == 'A'){
		if (pista3->tempo_apx > 0){
			pista3->tempo_apx --;
		}
		else{
			pista3->tempo_pouso --;

			if(pista3->tempo_pouso == 0){
				free (pista3);
				pista3 == NULL;
			}
		}
	}
	else{
		pista1->tempo_decolagem--;

		if(pista3->tempo_decolagem == 0){
			free (pista3);
			pista3 == NULL;
		}
	}
}


void voos_prioritarios(Fila *voos, Pista *pista1, Pista *pista2, Pista *pista3){
	Lista *atual;
	int comb0 = 0; //quantidade de pista com combustivel = 0;

	for(atual = voos->inicio; atual != NULL; atual = atual->proximo){
		if (atual->modo == 'A' && atual->combustivel == 0){
			comb0++;

			if (pista1 == NULL) {
				pista1 = (Pista *) malloc(sizeof(Pista));

				strcpy(pista1->codigo, atual->codigo);
				pista1->modo = atual->modo;
				pista1->combustivel = atual->combustivel;
				pista1->tempo_apx = 1;
				pista1->tempo_pouso = 2;
			}
			else if (pista2 == NULL) {
				pista2 = (Pista *) malloc(sizeof(Pista));
				
				strcpy(pista2->codigo, atual->codigo);
				pista2->modo = atual->modo;
				pista2->combustivel = atual->combustivel;
				pista2->tempo_apx = 1;
				pista2->tempo_pouso = 2;
			}
			else if (pista3 == NULL && comb0>=3) {
				pista3 = (Pista *) malloc(sizeof(Pista));
				
				strcpy(pista3->codigo, atual->codigo);
				pista3->modo = atual->modo;
				pista3->combustivel = atual->combustivel;
				pista3->tempo_apx = 1;
				pista3->tempo_pouso = 2;
			}
		}
	}

}


void altecao_combustivel(Fila *voos, Pista *pista1, Pista *pista2, Pista *pista3) {
	Lista *atual;

	for (atual = voos->inicio; atual != NULL; atual = atual->proximo) {
		atual->combustivel --;

		if (atual->combustivel < 0) {
			Lista *excluir;
			excluir = atual;

			if (atual == voos->inicio){
				voos->inicio = atual->proximo;
			}
			else {
				for (atual = voos->inicio; atual->proximo != excluir; atual = atual->proximo){}

				atual->proximo = excluir->proximo;

				if (voos->fim == excluir){
					voos->fim = atual;
				}
			}

			printf("ALERTA CRÍTICO, AERONAVE %s IRÁ CAIR”\n", excluir->codigo);
			free(excluir);
		}
	}

	if (pista1 != NULL && pista1->modo == 'A') {
		pista1->combustivel --;

		if (pista1->combustivel < 0){
			printf("ALERTA CRÍTICO, AERONAVE %s IRÁ CAIR”\n", pista1->codigo);

			free(pista1);
			pista1 = NULL;
		}
	}
	if (pista2 != NULL && pista2->modo == 'A') {
		pista2->combustivel --;

		if (pista2->combustivel < 0){
			printf("ALERTA CRÍTICO, AERONAVE %s IRÁ CAIR”\n", pista2->codigo);

			free(pista2);
			pista2 = NULL;
		}
	}
	if (pista3 != NULL && pista3->modo == 'A') {
		pista3->combustivel --;

		if (pista3->combustivel < 0){
			printf("ALERTA CRÍTICO, AERONAVE %s IRÁ CAIR”\n", pista3->codigo);

			free(pista3);
			pista3 = NULL;
		}
	}
}