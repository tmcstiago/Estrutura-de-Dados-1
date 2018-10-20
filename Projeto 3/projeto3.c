#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pessoa {
	char nome[101];
	char telefone[11];
	char endereco[101];
	char cep[10];
	char nascimento[11];
	struct Pessoa *proximo;
	struct Pessoa *anterior;
};	

typedef struct Pessoa contato;

contato *lista_contatos_vazia();
contato *leitura_inicial();

int main () {

	contato *contatos;
	contatos = lista_contatos_vazia;
	
	leitura_inicial();





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

