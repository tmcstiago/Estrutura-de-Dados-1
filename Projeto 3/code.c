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
void imprimi_contatos(contato *contatos);

int main () {
	leitura_inicial();
	contato *contatos;
	contato *novo;
	contatos = lista_contatos_vazia();

	//leitura_inicial();

	int opcao;
	do{
		printf("********** Seja bem-vindo a sua lista de contatos **********\n\n");
		printf("1. Inserir novo contato\n");
		printf("2. Remover contatos\n");
		printf("3. Realizar busca de usuários\n");
		printf("4. Visualizar todos os contatos\n");
		printf("5. Fechar a lista de contatos\n");
		printf("Indique o número de uma das opções acima: ");
		scanf ("%d", &opcao);
		char lixo;
		//scanf("%c", &lixo);

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

				contatos = novo_contato(contatos, novo);

				//free (novo);
			break;
			case 2:

			break;
			case 3:

			break;
			case 4:
				imprimi_contatos(contatos);

			break;
			case 5:
			break;
		}

	} while (opcao != 5);



	return 0;
}


contato *lista_contatos_vazia(){
	return NULL;
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
	while(fscanf(arquivo,"%[^\n]s", linha)!=EOF){
		fscanf(arquivo,"%*c");
		if (novo == NULL)
			exit (1);
		if(linha[0]=='$'){
			i=0;
			printf("Nome: %s\n", novo->nome);
			contatos = novo_contato(contatos, novo);
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
	free(novo);
	imprimi_contatos(contatos);
	return contatos;
}

contato *novo_contato(contato *contatos, contato *novo) {
	contato *new;
	new = (contato *) malloc(sizeof(contato));
	if(new == NULL)
		exit(-1);
	strcpy(new->nome,novo->nome);
	strcpy(new->telefone,novo->telefone);
	strcpy(new->endereco,novo->endereco);
	new->cep=novo->cep;
	strcpy(new->nascimento,novo->nascimento);
	if (contatos == NULL){
		new->anterior = NULL;
		new->proximo = NULL;
		return new;
	}
	else {
		new->anterior = NULL;
		new->proximo = contatos;
		return new;
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
