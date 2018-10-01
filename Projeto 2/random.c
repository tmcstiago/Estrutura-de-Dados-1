#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define N_LINHAS 1025
#define N_COLUNAS 1025 
#define N_IMAGENS 25

void get_random_file( char * file_path, char * img_type);
int ilbp (int *matriz, int media);

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



	int **treinamento;

	// estrutura para percorrer as 50 imagens de teste
	for (int a=1; a<=25; a++){

		/*
		código para pegar a imagem da grama aqui
		*/

		//alterando o tamanho da matriz que guarda os vetores
		if (a=1){
			treinamento = (int**) malloc(a*sizeof(int *));
		}
		else {
			treinamento = (int **) realloc(treinamento, a*sizeof(int *))
		}
		if (treinamento==NULL){
			printf("A alocação falhou\n");
			exit(1);
		}

		*(treinamento+(a-1)) = (int *) calloc(512, sizeof(int));
		if (*(treinamento + (a-1))==NULL){
			printf("A alocação falhou\n");
			exit(1);
		}

		// estrutura para calcular o resultado das matrizes 3x3
		for (int i=1; i<1024; i++){
			for (int j=1; j=1024; j++){
				int matriz[3][3], media = 0; // matriz a ser enviada pra função

				//passando os valores para a matriz
				for (int m=0; m<3; m++){
					for (int n=0; n<3; n++){
						matriz[m][n] = imagem[i-1+m][i-1+n];
						media += matriz[m][n]; //calculando a media entre os dados
					}
				}
				media = media/9;

				int menor = ilbp(matriz, media);

				//incrementando o valor obtido no resultado
				*(*(treinamento+(a-1))+(treinamento-1)) = *(*(treinamento+(a-1))+(treinamento-1)) + 1;
			}
		}
	}




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


int ilbp (int *matriz, int media){
	int binario[3][3];
	int menor = 0;

	//pegando os valores do vetor para calcular a media
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (*(matriz + (i*3) + j) >= media){
				binario[i][j] = 1;
			}
			else {
				binario[i][j] = 0;
			}
		}
	}

	int p[8]

	p[0] =pow(2;8)*binario[0][0] + pow(2;7)*binario[0][1] + pow(2;6)*binario[0][2] +
		pow(2;5)*binario[1][2] + pow(2;4)*binario[2][2] + pow(2;3)*binario[2][1] +
		pow(2;2)*binario[2][0] + pow(2;1)*binario[1][0] + pow(2;0)*binario[1][1];

	p[1] =pow(2;8)*binario[0][1] + pow(2;7)*binario[0][2] + pow(2;6)*binario[1][2] +
		pow(2;5)*binario[2][2] + pow(2;4)*binario[2][1] + pow(2;3)*binario[2][0] +
		pow(2;2)*binario[1][0] + pow(2;1)*binario[0][0] + pow(2;0)*binario[1][1];

	p[2] =pow(2;8)*binario[0][2] + pow(2;7)*binario[1][2] + pow(2;6)*binario[2][2] +
		pow(2;5)*binario[2][1] + pow(2;4)*binario[2][0] + pow(2;3)*binario[1][0] +
		pow(2;2)*binario[0][0] + pow(2;1)*binario[0][1] + pow(2;0)*binario[1][1];

	p[3] =pow(2;8)*binario[1][2] + pow(2;7)*binario[2][2] + pow(2;6)*binario[2][1] +
		pow(2;5)*binario[2][0] + pow(2;4)*binario[1][0] + pow(2;3)*binario[0][0] +
		pow(2;2)*binario[0][1] + pow(2;1)*binario[0][2] + pow(2;0)*binario[1][1];

	p[4] =pow(2;8)*binario[2][2] + pow(2;7)*binario[2][1] + pow(2;6)*binario[2][0] +
		pow(2;5)*binario[1][0] + pow(2;4)*binario[0][0] + pow(2;3)*binario[0][1] +
		pow(2;2)*binario[0][2] + pow(2;1)*binario[1][2] + pow(2;0)*binario[1][1];

	p[5] =pow(2;8)*binario[2][1] + pow(2;7)*binario[2][0] + pow(2;6)*binario[1][0] +
		pow(2;5)*binario[0][0] + pow(2;4)*binario[0][1] + pow(2;3)*binario[0][2] +
		pow(2;2)*binario[1][2] + pow(2;1)*binario[2][2] + pow(2;0)*binario[1][1];

	p[6] =pow(2;8)*binario[2][0] + pow(2;7)*binario[1][0] + pow(2;6)*binario[0][0] +
		pow(2;5)*binario[0][1] + pow(2;4)*binario[0][2] + pow(2;3)*binario[1][2] +
		pow(2;2)*binario[2][2] + pow(2;1)*binario[2][1] + pow(2;0)*binario[1][1];

	p[7] =pow(2;8)*binario[1][0] + pow(2;7)*binario[0][0] + pow(2;6)*binario[0][1] +
		pow(2;5)*binario[0][2] + pow(2;4)*binario[1][2] + pow(2;3)*binario[2][2] +
		pow(2;2)*binario[2][1] + pow(2;1)*binario[2][0] + pow(2;0)*binario[1][1];

	p[8] =pow(2;8)*binario[1][1] + pow(2;7)*binario[1][0] + pow(2;6)*binario[0][0] +
		pow(2;5)*binario[0][1] + pow(2;4)*binario[0][2] + pow(2;3)*binario[1][2] +
		pow(2;2)*binario[2][2] + pow(2;1)*binario[2][1] + pow(2;0)*binario[2][0];

	for (int i=0; i<9; i++) {
		if (p[i] > menor) {
			menor = p[i];
		}
	}	

	return menor;
}
