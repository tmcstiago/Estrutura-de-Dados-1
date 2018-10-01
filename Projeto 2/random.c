#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

void get_random_file( char * file_path); //Função gera 25 nomes de arquivo aleatório entre os apresentados
int ilbp (int *matriz, int media);


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




	int **grama;

	// estrutura para percorrer as 25 imagens de grama
	for (int a=1; a<=25; a++){

		/*
		código para pegar a imagem da grama aqui
		*/

		//alterando o tamanho da matriz que guarda os vetores
		if (a=1){
			grama = (int**) malloc(a*sizeof(int *));
		}
		else {
			grama = (int **) realloc(grama, a*sizeof(int *))
		}
		if (grama==NULL){
			printf("A alocação falhou\n");
			exit(1);
		}

		*(grama+(a-1)) = (int *) calloc(512, sizeof(int));
		if (*(grama + (a-1))==NULL){
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
				*(*(grama+(a-1))+(grama-1)) = *(*(grama+(a-1))+(grama-1)) + 1;
			}
		}
	}




	//Liberação da memória contendo arquivos de imagens
	for(int i=0; i<25; i++){
		free(imagens[i]);
	}

	//liberando a memoria dos valores de grama
	for (i=0; i<a; i++) {
		free (* (grama + 1));
	}
	free (grama);

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