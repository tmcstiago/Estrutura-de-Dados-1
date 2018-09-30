#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void get_random_file( char * file_path);
//Função gera 25 nomes de arquivo aleatório entre os apresentados
int main()
{
	srand(time(0));	// Usado para rand() gerar número aleátorio cada vez que rodado

	//Geração aleatória dos 25 nomes de arquivos
	char file_path[25][50];
	for(int i=0; i<25; i++){
		get_random_file(file_path[i]);
		//printf("%s\n", file_path[i]);
	}

	int *imagens[25]; // Vetor com informaçoes das 25 imagens
	//Leitura dos 25 arquivos gerados aleatoriamente	
	for(int i=0; i<25; i++){
		FILE *arquivo;
		arquivo = fopen(file_path[i], "r");

		if (arquivo == NULL){
			printf("Problema na Leitura do arquivo\n");
			exit(1);
		}
		
		imagens[i] = (int *) malloc (sizeof(int));
		long int j=0;
		while (!feof(arquivo))
		{	
			fscanf(arquivo, "%d;", &imagens[i][j]);
			//printf("imagens[%d]= %d\n", i, imagens[i][j]);		
			imagens[i] = (int *) realloc(imagens[i], (j+2)*sizeof(int));

			if (imagens[i] == NULL){
				printf("Alocacao falhou. Finalizado.\n");
				exit(1);
			}
			j++;
			
		}
		fclose(arquivo);
	}




	//Liberação da memória contendo arquivos de imagens
	for(int i=0; i<25; i++){
		free(imagens[i]);
	}
	return 0;

}
void get_random_file(char * file_path){
	
	
	char data_type[50]; 
	int random_2 = (rand()%2)+1; //Gera número aleatório de 1 a 2 
	//O número gerado determina o tipo de arquivo
	if(random_2==1){
		strcpy(data_type, "asphalt");
	}
	else{
		strcpy(data_type, "grass");
	}
	int random_50 = (rand()%50)+1; //Gera número aleatório de 1 a 50 
	char file_name[50];
	sprintf(file_name ,"%s_%02d.txt", data_type, random_50);
	sprintf(file_path ,"./DataSet/%s/%s", data_type, file_name);
	
}


