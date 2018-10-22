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
void busca_contato(contato *contatos, char *busca);

int main () {

	contato *contatos;
	contato *novo;
	contatos = lista_contatos_vazia();

	char busca[101];
	char *ponto;

	//leitura_inicial();

	printf("********** Seja bem-vindo a sua lista de contatos **********\n\n");
	
	int opcao;
	do{
		printf("1. Inserir novo contato\n");
		printf("2. Remover contatos\n");
		printf("3. Realizar busca de usuários\n");
		printf("4. Visualizar todos os contatos\n");
		printf("5. Fechar a lista de contatos\n");
		printf("Indique o número de uma das opções acima: ");
		scanf ("%d", &opcao);

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

				printf("\n\n");
				//free (novo);
			break;
			case 2:

			break;
			case 3:

				printf("Insira o nome do cotato(s) que você deseja buscar\n");
				scanf(" %[^\n]", busca);

				ponto = busca;

				busca_contato(contatos, busca);
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
		printf("Problema na Leitura dos arquivos\n");
		exit(1);
	}
	char linha[500];
	contato aux;
	int i=0;
	while(fscanf(arquivo,"%[^\n]s", linha)!=EOF){
		fscanf(arquivo,"%*c");

		if(linha[0]=='$'){
			printf("==============================================================\n");
			i=0;
			continue;
		}
		if(i==0 && linha[0]==' ')
			return;

		switch(i){
			case 0:
				strcpy(aux.nome,linha);
				printf("%s\n", aux.nome);
			break;

			case 1:
				strcpy(aux.telefone,linha);
				printf("%s\n", aux.telefone);
			break;

			case 2:
				strcpy(aux.endereco,linha);
				printf("%s\n", aux.endereco);
			break;

			case 3:
				strcpy(aux.cep,linha);
				printf("%s\n", aux.cep);
			break;

			case 4:
				strcpy(aux.nascimento,linha);
				printf("%s\n", aux.nascimento);
			break;

			case 5:
			break;
		}
		i++;
	}
	fclose(arquivo);
}


contato *novo_contato(contato *contatos, contato *novo) {
	if (contatos == NULL){
		novo->anterior = NULL;
		novo->proximo = NULL;

		return novo;
	}
	else {
		contato *atual;

		for (atual = contatos; atual->proximo != NULL; atual = atual->proximo){}
		atual->proximo = novo;
		novo->anterior = contatos;
		novo->proximo = NULL;
		return contatos;
	}
}


void imprimi_contatos(contato *contatos){
	contato *atual;

	int i=1;
	for (atual = contatos; atual != NULL; atual = atual->proximo){
		printf("Nome: %s\n", atual->nome);
		printf("Telefone: %s\n", atual->telefone);
		printf("Endereço: %s\n", atual->endereco);
		printf("CEP: %u\n", atual->cep);
		printf("Data de Nascimento: %s\n", atual->nascimento);
		printf("\n");
		i++;
	}
		printf("\n\n\n");

}


void busca_contato(contato *contatos, char *busca){
	contato *atual;

	int cont_loc = 0;
	for(atual = contatos; atual != NULL; atual = atual->proximo){
		int j = 0;
		for(int i=0; atual->nome[i] != '\0'; i++){
			if (*(busca+j)>= 97 && *(busca+j)<=122){
				*(busca+j) = *(busca+j)-32;
			}
			if (*(busca+j) == '\0'){
				if (cont_loc==0){
					printf("\nContato(s) localizados:\n\n");
				}
				printf("Nome: %s\n", atual->nome);
				printf("Telefone: %s\n", atual->telefone);
				printf("Endereço: %s\n", atual->endereco);
				printf("CEP: %u\n", atual->cep);
				printf("Data de Nascimento: %s\n", atual->nascimento);
				printf("\n");
				cont_loc++;
				break;
			}
			else {
				if(atual->nome[i] == *(busca+j) || atual->nome[i] == *(busca+j)+32){
					j++;
				}
				else {
					j=0;
				}
			}
		}
	}
	if (cont_loc==0){
		printf("\nNenhum contato localizado\n");
	}


}
