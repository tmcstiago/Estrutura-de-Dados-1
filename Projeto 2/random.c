#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define N_IMAGENS 25



void get_random_file( char * file_path, char * img_type);
int ilbp (int *imagem, int media);

int main()
{
	srand(time(0));	// Usado para rand() gerar número aleátorio cada vez que rodado

	//Geração aleatória dos 25 nomes de arquivos aleatórios e distintos
	char asphalt_path[N_IMAGENS][50];
	char grass_path[N_IMAGENS][50];
	for(int i=0; i<N_IMAGENS; i++){
		get_random_file(asphalt_path[i], "asphalt");
		for(int j=0; j<i; j++){
			if(!strcmp(asphalt_path[i], asphalt_path[j])){
				get_random_file(asphalt_path[i], "asphalt");
				j=-1;
			}	
		}
		get_random_file(grass_path[i], "grass");
		for(int j=0; j<i; j++){
			if(!strcmp(grass_path[i], grass_path[j])){
				get_random_file(grass_path[i], "grass");
				j=-1;
			}	
		}
		//printf("%s\n", asphalt_path[i]);
		//printf("%s\n", grass_path[i]);
	}
		
	//Leitura dos arquivos	
	for(int i=0; i<N_IMAGENS*2; i++){
		int nlin, ncol;
		int **imagem;
		FILE *arquivo;
		char path[50];
		if(i%2==0){
			strcpy(path, grass_path[i/2]);
		}
		else{
			strcpy(path, asphalt_path[i/2]);
		}
		arquivo = fopen(path, "r");

		printf("Lendo.. %s\n", path);

		if (arquivo == NULL){
			printf("Problema na Leitura dos arquivos\n");
			exit(1);
		}
		imagem = (int **) malloc (sizeof(int *));
		imagem[0] = (int *) malloc (sizeof(int));
		if (imagem == NULL || imagem[0] == NULL){
			printf("Realocacao falhou. Finalizado.\n");

			exit(1);
		}
		int i=0, j=0;
		char aux;
		while(fscanf(arquivo, "%d%c", &imagem[i][j], &aux)!=EOF){
			imagem[i] = (int *) realloc(imagem[i], (j+2)*sizeof(int));
			if (imagem[i] == NULL){
				printf("Realocacao falhou. Finalizado.\n");
				exit(1);
			}
			if(aux=='\n'){
				//printf("imagem[%d][%d]= %d\n", i, j, imagem[i][j]);
				imagem = (int **) realloc(imagem, (i+2)*sizeof(int *));
				imagem[i+1] = (int *) malloc(sizeof(int));
				if (imagem == NULL || imagem[i+1] == NULL){
					printf("Realocacao falhou. Finalizado.\n");
					exit(1);
				}
				ncol=j+1;	
				i++;
				j=-1;
			}
			j++;	
		}
		nlin=i;
		fclose(arquivo);


		printf("nlin= %d, ncol= %d\n", nlin, ncol);
		

		for(int i=0; i<ncol; i++)
			free(imagem[i]);
		free(imagem);
	}
	return 0;

}
void get_random_file(char * file_path, char * img_type){
		
	int random_50 = (rand()%50)+1; //Gera número aleatório de 1 a 50 
	sprintf(file_path ,"./DataSet/%s/%s_%02d.txt", img_type, img_type, random_50);
	
}



