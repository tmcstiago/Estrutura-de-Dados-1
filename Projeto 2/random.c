#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N_LINHAS 1025
#define N_COLUNAS 1025 
#define N_IMAGENS 25
void get_random_file( char * file_path, char * img_type);
//Função gera 25 nomes de arquivo aleatório entre os apresentados
int main()
{
	srand(time(0));	// Usado para rand() gerar número aleátorio cada vez que rodado

	//Geração aleatória dos 25 nomes de arquivos
	char asphalt_path[N_IMAGENS][50];
	char grass_path[N_IMAGENS][50];
	for(int i=0; i<N_IMAGENS; i++){
		get_random_file(asphalt_path[i], "asphalt");
		get_random_file(grass_path[i], "grass");
		//printf("%s\n", file_path[i]);
	}

	//Alocação da memória dinamicamente
	int ***asphalt;
	int ***grass;
	asphalt = (int ***) malloc (N_IMAGENS*sizeof(int **));
	grass = (int ***) malloc (N_IMAGENS*sizeof(int **));
	for(int i=0; i<N_IMAGENS; i++){
		asphalt[i] = (int **) malloc (N_LINHAS*sizeof(int *));
		grass[i] = (int **) malloc (N_LINHAS*sizeof(int *));
		for(int j=0; j<N_LINHAS; j++)
		{
			asphalt[i][j]=(int*)malloc(N_COLUNAS*sizeof(int));
			grass[i][j]=(int*)malloc(N_COLUNAS*sizeof(int));
		}
	}

	//Leitura das imagens
	for(int i=0; i<N_IMAGENS; i++){
		FILE *asphalt_arq;
		FILE *grass_arq;
		asphalt_arq = fopen(asphalt_path[i], "r");
		grass_arq = fopen(grass_path[i], "r");
		
		if (asphalt_arq == NULL || grass_arq == NULL){
			printf("Problema na Leitura dos arquivos\n");
			exit(1);
		}
		int j=0;
		while (!feof(asphalt_arq) || !feof(grass_arq))
		{
			int n_linha=j/N_COLUNAS;
			int n_coluna=j%N_LINHAS;
			fscanf(asphalt_arq, "%d;", &asphalt[i][n_linha][n_coluna]);
			fscanf(grass_arq, "%d;", &grass[i][n_linha][n_coluna]);
			j++;	
		}
		fclose(asphalt_arq);
		fclose(grass_arq);
	}


	//Faz o código aqui 



	//Liberação da memória contendo arquivos de imagens
	for(int i=0; i<N_IMAGENS; i++){
		for(int j=0; j<N_LINHAS; j++){
			free(asphalt[i][j]);
			free(grass[i][j]);
		}
	}
	for(int i=0; i<N_IMAGENS; i++){
		free(asphalt[i]);
		free(grass[i]);
	}
	free(asphalt);
	free(grass);
	return 0;

}
void get_random_file(char * file_path, char * img_type){
		
	int random_50 = (rand()%50)+1; //Gera número aleatório de 1 a 50 
	sprintf(file_path ,"./DataSet/%s/%s_%02d.txt", img_type, img_type, random_50);
	
}


