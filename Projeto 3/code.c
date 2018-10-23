#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pessoa {
	char nome[101];
	char telefone[11];
	char endereco[101];
	unsigned int cep;
	char nascimento[11];
	struct Pessoa *proximo;
	struct Pessoa *anterior;
};	

typedef struct Pessoa contato;

contato *lista_contatos_vazia();
contato *leitura_inicial();
contato *novo_contato(contato *contatos, contato *novo);
void libera_contatos(contato *contatos);
void imprimi_contatos(contato *contatos);
void salvar_arquivo(contato *contatos);
void copy(contato* A, contato* B);
contato * insertion_sort(contato *contatos);

int main () {
	contato *contatos;
	contato *novo;
	contatos = lista_contatos_vazia();
	contatos = leitura_inicial();
	contatos = insertion_sort(contatos);
	//imprimi_contatos(contatos);
	int opcao;
	do{
		system("clear");
		printf("********** Seja bem-vindo a sua lista de contatos **********\n\n");
		printf("1. Inserir novo contato\n");
		printf("2. Remover contatos\n");
		printf("3. Realizar busca de usuários\n");
		printf("4. Visualizar todos os contatos\n");
		printf("5. Fechar a lista de contatos\n");
		printf("Indique o número de uma das opções acima: ");
		scanf ("%d", &opcao);
		getchar();
		char lixo;
		//scanf("%c", &lixo);
		system("clear");
		switch (opcao){
			case 1:
				novo = lista_contatos_vazia();

				novo = (contato *) malloc(sizeof(contato));
				if (novo == NULL)
					exit (1);

				printf("Insira o nome do contato: ");
				scanf(" %[^\n]", novo->nome);

				char t[11];
				printf("Insira o Telefone: ");
				scanf(" %[^\n]", t);

				//verificador do telefone
				int i;
				int j;
				for(i=0, j=0; i<10; i++, j++) {
					if (j==5){
						if(t[i] == '-'){
							novo->telefone[j] = '-';
							j++;
						}
					}
					novo->telefone[i] = t[j];
				}
			

				printf("Insira o endereço: ");
				scanf(" %[^\n]", novo->endereco);

				printf("Insira o CEP (padrão EUA): ");
				scanf(" %u", &novo->cep);

				printf("Insira a data de nascimento: ");
				scanf(" %[^\n]", novo->nascimento);

				printf("Nome: %s\n", novo->nome);
				printf("Telefone: %s\n", novo->telefone);
				printf("Endereço: %s\n", novo->endereco);
				printf("CEP: %u\n", novo->cep);
				printf("Data de Nascimento: %s\n", novo->nascimento);
				getchar();
				contatos = novo_contato(contatos, novo);
				insertion_sort(contatos);
				printf("Cadastro realizado com sucesso!\n");
				printf("Aperte enter para continuar:");
				getchar();
				//free (novo);
			break;
			case 2:

			break;
			case 3:

			break;
			case 4:
				contatos = insertion_sort(contatos);
				imprimi_contatos(contatos);
				printf("Aperte enter para continuar:");
				getchar();

			break;
			case 5:
			break;
		}

	} while (opcao != 5);
	insertion_sort(contatos);
	salvar_arquivo(contatos);
	libera_contatos(contatos);


	return 0;
}


contato *lista_contatos_vazia(){
	return NULL;
}
void libera_contatos(contato *contatos){
	contato *atual;
	for (atual = contatos; atual != NULL; contatos = atual){
		//printf("liberando: %s\n", contatos->nome);
		atual=atual->proximo;
		free(contatos);
		contatos = NULL;
	}
	//if(contatos == NULL)
		//printf("LIBERADO\n");
}
contato * insertion_sort(contato *contatos){
	contato *escolhido;
	contato *temp;
	//temp = (contato *) malloc(sizeof(contato));
	if(temp==NULL) exit(-1);
	int i=1;
	for (;;i++){
		//imprimi_contatos(contatos);
		int need_swap=0; //determina se é necessário ou nao trocar elementos
		int j = i - 1;
		int k=i;
		for(escolhido=contatos; k ; k--, escolhido = escolhido->proximo){
			if(escolhido->proximo == NULL){
				return contatos;
			}
		};	
		temp=escolhido->anterior;
		if(escolhido->proximo!=NULL){
			escolhido->proximo->anterior=temp;
			temp->proximo=escolhido->proximo;
		}
		else{
			temp->proximo=NULL;
		}
		//imprimi_contatos(contatos);
		while ((j >= 0) && (strcmp(temp->nome, escolhido->nome))>=0){
			temp=temp->anterior;
			j--;
		}
		if(temp==NULL){
			escolhido->proximo=contatos;
			escolhido->anterior=NULL;
			contatos->anterior=escolhido;
			contatos=escolhido;
			
		}
		else if(temp->proximo==NULL){
			escolhido->proximo=NULL;
			escolhido->anterior=temp;
			temp->proximo=escolhido;
		}
		else{
			escolhido->proximo=temp->proximo;
			escolhido->anterior=temp;
			escolhido->proximo->anterior=escolhido;
			temp->proximo=escolhido;
			
		}
		//imprimi_contatos(contatos);
		//getchar();
	}
}
void copy(contato* A, contato* B){
	contato* temp;
	temp = (contato *) malloc(sizeof(contato));
	if(temp==NULL) exit(-1);

	//strcpy(temp->nome,A->nome);
	strcpy(A->nome,B->nome);
	//strcpy(B->nome,temp->nome);
	
	//strcpy(temp->telefone,A->telefone);
	strcpy(A->telefone,B->telefone);
	//strcpy(B->telefone,temp->telefone);

	//strcpy(temp->endereco,A->endereco);
	strcpy(A->endereco,B->endereco);
	//strcpy(B->endereco,temp->endereco);

	//temp->cep=A->cep;
	A->cep=B->cep;
	//B->cep=temp->cep;

	//strcpy(temp->nascimento,A->nascimento);
	strcpy(A->nascimento,B->nascimento);
	A->anterior=B->anterior;
	A->proximo=B->proximo;
	//strcpy(B->nascimento,temp->nascimento);
	free(temp);
}	
void salvar_arquivo(contato *contatos){
	FILE *arquivo;
	arquivo = fopen("contatos.txt", "w");
	if (arquivo == NULL){
		printf("Erro na abertura do arquivo!");
		exit(-1);
	}
	contato *atual;
	for (atual = contatos; atual != NULL; atual = atual->proximo){
		fprintf(arquivo, "%s\n", atual->nome);
		fprintf(arquivo, "%s\n", atual->telefone);
		fprintf(arquivo, "%s\n", atual->endereco);
		fprintf(arquivo, "%u\n", atual->cep);
		fprintf(arquivo, "%s\n", atual->nascimento);
		fprintf(arquivo, "$\n");
	}	
}
contato * leitura_inicial(){
	FILE *arquivo;
	arquivo = fopen("contatos.txt", "r");
	if (arquivo == NULL){
		return NULL;
	}
	char linha[500];
	int i=0;
	contato *contatos;
	contatos = lista_contatos_vazia();
	contato *novo;
	novo = (contato *) malloc(sizeof(contato));
	if(novo==NULL) exit(-1);

	while(fscanf(arquivo,"%[^\n]s", linha)!=EOF){
		fscanf(arquivo,"%*c");
		if (novo == NULL)
			exit (1);
		if(linha[0]=='$'){
			i=0;
			contatos = novo_contato(contatos, novo);
			novo = (contato *) malloc( sizeof(contato));
			if(novo==NULL) exit(-1);
			continue;
		}
		if(i==0 && linha[0]==' ')
			break;

		switch(i){
			case 0:
				strcpy(novo->nome,linha);
			break;

			case 1:
				strcpy(novo->telefone,linha);
			break;

			case 2:
				strcpy(novo->endereco,linha);
			break;

			case 3:
				sscanf(linha, "%u", &novo->cep);
			break;

			case 4:
				strcpy(novo->nascimento,linha);
			break;
		}
		i++;
	}
	fclose(arquivo);
	return contatos;
}

contato *novo_contato(contato *contatos, contato *novo) {
	if (contatos == NULL){
		contatos = (contato *) malloc(sizeof(contato));
		if(contatos==NULL) exit(-1);
		novo->anterior = NULL;
		novo->proximo = NULL;

		return novo;
	}
	else {
		contato *atual;

		for (atual = contatos; atual->proximo != NULL; atual = atual->proximo);
		atual->proximo = novo;
		novo->anterior = contatos;
		novo->proximo = NULL;
		//printf("Nome: %s\n", contatos->nome);
		return contatos;
	}
}

void imprimi_contatos(contato *contatos){
	contato *atual;
	int i=1;
	for (atual = contatos; atual != NULL; atual = atual->proximo){
		printf("Nome: %s\n", atual->nome);
		printf("Contato %d\n", i);
		printf("Telefone: %s\n", atual->telefone);
		printf("Endereço: %s\n", atual->endereco);
		printf("CEP: %u\n", atual->cep);
		printf("Data de Nascimento: %s\n", atual->nascimento);
		printf("\n\n\n");
		i++;
	}

}

