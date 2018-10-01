#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

	int p[8];

	p[0] =pow(2,8)*binario[0][0] + pow(2,7)*binario[0][1] + pow(2,6)*binario[0][2] +
		pow(2,5)*binario[1][2] + pow(2,4)*binario[2][2] + pow(2,3)*binario[2][1] +
		pow(2,2)*binario[2][0] + pow(2,1)*binario[1][0] + pow(2,0)*binario[1][1];

	p[1] =pow(2,8)*binario[0][1] + pow(2,7)*binario[0][2] + pow(2,6)*binario[1][2] +
		pow(2,5)*binario[2][2] + pow(2,4)*binario[2][1] + pow(2,3)*binario[2][0] +
		pow(2,2)*binario[1][0] + pow(2,1)*binario[0][0] + pow(2,0)*binario[1][1];

	p[2] =pow(2,8)*binario[0][2] + pow(2,7)*binario[1][2] + pow(2,6)*binario[2][2] +
		pow(2,5)*binario[2][1] + pow(2,4)*binario[2][0] + pow(2,3)*binario[1][0] +
		pow(2,2)*binario[0][0] + pow(2,1)*binario[0][1] + pow(2,0)*binario[1][1];

	p[3] =pow(2,8)*binario[1][2] + pow(2,7)*binario[2][2] + pow(2,6)*binario[2][1] +
		pow(2,5)*binario[2][0] + pow(2,4)*binario[1][0] + pow(2,3)*binario[0][0] +
		pow(2,2)*binario[0][1] + pow(2,1)*binario[0][2] + pow(2,0)*binario[1][1];

	p[4] =pow(2,8)*binario[2][2] + pow(2,7)*binario[2][1] + pow(2,6)*binario[2][0] +
		pow(2,5)*binario[1][0] + pow(2,4)*binario[0][0] + pow(2,3)*binario[0][1] +
		pow(2,2)*binario[0][2] + pow(2,1)*binario[1][2] + pow(2,0)*binario[1][1];

	p[5] =pow(2,8)*binario[2][1] + pow(2,7)*binario[2][0] + pow(2,6)*binario[1][0] +
		pow(2,5)*binario[0][0] + pow(2,4)*binario[0][1] + pow(2,3)*binario[0][2] +
		pow(2,2)*binario[1][2] + pow(2,1)*binario[2][2] + pow(2,0)*binario[1][1];

	p[6] =pow(2,8)*binario[2][0] + pow(2,7)*binario[1][0] + pow(2,6)*binario[0][0] +
		pow(2,5)*binario[0][1] + pow(2,4)*binario[0][2] + pow(2,3)*binario[1][2] +
		pow(2,2)*binario[2][2] + pow(2,1)*binario[2][1] + pow(2,0)*binario[1][1];

	p[7] =pow(2,8)*binario[1][0] + pow(2,7)*binario[0][0] + pow(2,6)*binario[0][1] +
		pow(2,5)*binario[0][2] + pow(2,4)*binario[1][2] + pow(2,3)*binario[2][2] +
		pow(2,2)*binario[2][1] + pow(2,1)*binario[2][0] + pow(2,0)*binario[1][1];

	p[8] =pow(2,8)*binario[1][1] + pow(2,7)*binario[1][0] + pow(2,6)*binario[0][0] +
		pow(2,5)*binario[0][1] + pow(2,4)*binario[0][2] + pow(2,3)*binario[1][2] +
		pow(2,2)*binario[2][2] + pow(2,1)*binario[2][1] + pow(2,0)*binario[2][0];

	for (int i=0; i<9; i++) {
		if (p[i] > menor) {
			menor = p[i];
		}
	}	

	return menor;
}


int main()
{

	int **treinamento;

	//vetor utilizado para armazenar o treinamento em grama e asfalto
	for (int a=0; a<25; a++){

		/*
		código para pegar a imagem da grama aqui
		*/

		//alterando o tamanho da matriz que guarda os vetores
		if (a==0){
			treinamento = (int**) malloc(1*sizeof(int *));
		}
		else {
			treinamento = (int **) realloc(treinamento, (a+1)*sizeof(int *));
		}
		if (treinamento==NULL){
			printf("A alocação falhou\n");
			exit(1);
		}

		//espaço para armazenar o vetor ilbp
		*(treinamento+a) = (int *) calloc(512, sizeof(int));
		if (*(treinamento + (a-1))==NULL){
			printf("A alocação falhou\n");
			exit(1);
		}

		// estrutura para calcular o resultado das matrizes 3x3
		for (int i=1; i<(nlin-1); i++){
			for (int j=1; j<(ncol-1); j++){
				int matriz[3][3], media = 0; // matriz a ser enviada pra função
				int *p = matriz;

				//passando os valores para a matriz
				for (int m=0; m<3; m++){
					for (int n=0; n<3; n++){
						matriz[m][n] = *(*(imagem+i)+j);
						media += matriz[m][n]; //calculando a media entre os dados
					}
				}
				media = media/9;

				int menor = ilbp(matriz, media);

				//incrementando o valor obtido no resultado
				*(*(treinamento+a)+menor) += 1;
			}
		}


		int **glcm;

		glcm = (int **) malloc(256*sizeof(int));

		if (glcm==NULL){
			printf("A locação falhou\n");
			exit(1);
		}

		for (int i=0; i<256; i++){
			*(glcm + i) = (int *) calloc(256, sizeof(int))

			if (*(glcm + i) == NULL){
				printf("A locação falhou\n");
				exit(1);
			}
		}

		//calculando o glcm   256x256
		//vizinho da direita
		for (int i=0; i<nlin; i++){
			for (int j=0; j<(ncol-1); j++){
				int linha = *(*(imagem+i)+j);
				int coluna = *(*(imagem+i)+j+1);
				*(*(glcm + linha)+coluna) += 1
			}
		}

		int contraste = 0;

		//calculando o contraste
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				contraste += pow((i-j),2) * *(*(glcm+i)+j);
			}
		}

		int energia = 0;

		//calculando a energia
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				energia += pow(campo, 2);
			}
		}

		int homogeneidade = 0;

		//calculando a homogeneidade
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				if (i<=j) {
					homogeneidade += campo/ (1+(i-j));
				}
				else{
					homogeneidade += campo/(1+(j-i));
				}
			}
		}

		*(treinamento+a) = (int *) realloc(515, sizeof(int)); //declarando os novo tamanho dos dados da imagem

		*(*(treinamento+a)+512) = contraste;
		*(*(treinamento+a)+513) = energia;
		*(*(treinamento+a)+514) = homogeneidade;

		//limpando a matriz glcm
		for (int i=0; i<256; i++) {
			free (*(glcm+i));
		}
		free (glcm);


		//fazendo o glcm da segunda direção
		**glcm;

		glcm = (int **) malloc(256*sizeof(int));

		if (glcm==NULL){
			printf("A locação falhou\n");
			exit(1);
		}

		for (int i=0; i<256; i++){
			*(glcm + i) = (int *) calloc(256, sizeof(int))

			if (*(glcm + i) == NULL){
				printf("A locação falhou\n");
				exit(1);
			}
		}

		//calculando o glcm   256x256
		//vizinho da direita -- baixo
		for (int i=0; i<(nlin-1); i++){
			for (int j=0; j<(ncol-1); j++){
				int linha = *(*(imagem+i)+j);
				int coluna = *(*(imagem+i+1)+j+1);
				*(*(glcm + linha)+coluna) += 1
			}
		}

		contraste = 0;

		//calculando o contraste
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				contraste += pow((i-j),2) * *(*(glcm+i)+j);
			}
		}

		energia = 0;

		//calculando a energia
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				energia += pow(campo, 2);
			}
		}

		homogeneidade = 0;

		//calculando a homogeneidade
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				if (i<=j) {
					homogeneidade += campo/ (1+(i-j));
				}
				else{
					homogeneidade += campo/(1+(j-i));
				}
			}
		}

		*(treinamento+a) = (int *) realloc(518, sizeof(int)); //declarando os novo tamanho dos dados da imagem

		*(*(treinamento+a)+515) = contraste;
		*(*(treinamento+a)+516) = energia;
		*(*(treinamento+a)+517) = homogeneidade;

		//limpando a matriz glcm
		for (int i=0; i<256; i++) {
			free (*(glcm+i));
		}
		free (glcm);



		//fazendo o glcm da terceira direção
		**glcm;

		glcm = (int **) malloc(256*sizeof(int));

		if (glcm==NULL){
			printf("A locação falhou\n");
			exit(1);
		}

		for (int i=0; i<256; i++){
			*(glcm + i) = (int *) calloc(256, sizeof(int))

			if (*(glcm + i) == NULL){
				printf("A locação falhou\n");
				exit(1);
			}
		}

		//calculando o glcm   256x256
		//vizinho de baixo
		for (int i=0; i<(nlin-1); i++){
			for (int j=0; j<(ncol); j++){
				int linha = *(*(imagem+i)+j);
				int coluna = *(*(imagem+i+1)+j);
				*(*(glcm + linha)+coluna) += 1
			}
		}

		contraste = 0;

		//calculando o contraste
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				contraste += pow((i-j),2) * *(*(glcm+i)+j);
			}
		}

		energia = 0;

		//calculando a energia
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				energia += pow(campo, 2);
			}
		}

		homogeneidade = 0;

		//calculando a homogeneidade
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				if (i<=j) {
					homogeneidade += campo/ (1+(i-j));
				}
				else{
					homogeneidade += campo/(1+(j-i));
				}
			}
		}

		*(treinamento+a) = (int *) realloc(521, sizeof(int)); //declarando os novo tamanho dos dados da imagem

		*(*(treinamento+a)+518) = contraste;
		*(*(treinamento+a)+519) = energia;
		*(*(treinamento+a)+520) = homogeneidade;

		//limpando a matriz glcm
		for (int i=0; i<256; i++) {
			free (*(glcm+i));
		}
		free (glcm);



		//fazendo o glcm da quarta direção
		**glcm;

		glcm = (int **) malloc(256*sizeof(int));

		if (glcm==NULL){
			printf("A locação falhou\n");
			exit(1);
		}

		for (int i=0; i<256; i++){
			*(glcm + i) = (int *) calloc(256, sizeof(int))

			if (*(glcm + i) == NULL){
				printf("A locação falhou\n");
				exit(1);
			}
		}

		//calculando o glcm   256x256
		//vizinho de inferior esquerdo
		for (int i=0; i<(nlin-1); i++){
			for (int j=1; j<(ncol); j++){
				int linha = *(*(imagem+i)+j);
				int coluna = *(*(imagem+i+1)+j-1);
				*(*(glcm + linha)+coluna) += 1
			}
		}

		contraste = 0;

		//calculando o contraste
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				contraste += pow((i-j),2) * *(*(glcm+i)+j);
			}
		}

		energia = 0;

		//calculando a energia
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				energia += pow(campo, 2);
			}
		}

		homogeneidade = 0;

		//calculando a homogeneidade
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				if (i<=j) {
					homogeneidade += campo/ (1+(i-j));
				}
				else{
					homogeneidade += campo/(1+(j-i));
				}
			}
		}

		*(treinamento+a) = (int *) realloc(524, sizeof(int)); //declarando os novo tamanho dos dados da imagem

		*(*(treinamento+a)+521) = contraste;
		*(*(treinamento+a)+522) = energia;
		*(*(treinamento+a)+523) = homogeneidade;

		//limpando a matriz glcm
		for (int i=0; i<256; i++) {
			free (*(glcm+i));
		}
		free (glcm);




		//fazendo o glcm da quinta direção
		**glcm;

		glcm = (int **) malloc(256*sizeof(int));

		if (glcm==NULL){
			printf("A locação falhou\n");
			exit(1);
		}

		for (int i=0; i<256; i++){
			*(glcm + i) = (int *) calloc(256, sizeof(int))

			if (*(glcm + i) == NULL){
				printf("A locação falhou\n");
				exit(1);
			}
		}

		//calculando o glcm   256x256
		//vizinho de esquerdo
		for (int i=0; i<(nlin); i++){
			for (int j=1; j<(ncol); j++){
				int linha = *(*(imagem+i)+j);
				int coluna = *(*(imagem+i+1)+j-1);
				*(*(glcm + linha)+coluna) += 1
			}
		}

		contraste = 0;

		//calculando o contraste
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				contraste += pow((i-j),2) * *(*(glcm+i)+j);
			}
		}

		energia = 0;

		//calculando a energia
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				energia += pow(campo, 2);
			}
		}

		homogeneidade = 0;

		//calculando a homogeneidade
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				if (i<=j) {
					homogeneidade += campo/ (1+(i-j));
				}
				else{
					homogeneidade += campo/(1+(j-i));
				}
			}
		}

		*(treinamento+a) = (int *) realloc(527, sizeof(int)); //declarando os novo tamanho dos dados da imagem

		*(*(treinamento+a)+524) = contraste;
		*(*(treinamento+a)+525) = energia;
		*(*(treinamento+a)+526) = homogeneidade;

		//limpando a matriz glcm
		for (int i=0; i<256; i++) {
			free (*(glcm+i));
		}
		free (glcm);



		//fazendo o glcm da sexta direção
		**glcm;

		glcm = (int **) malloc(256*sizeof(int));

		if (glcm==NULL){
			printf("A locação falhou\n");
			exit(1);
		}

		for (int i=0; i<256; i++){
			*(glcm + i) = (int *) calloc(256, sizeof(int))

			if (*(glcm + i) == NULL){
				printf("A locação falhou\n");
				exit(1);
			}
		}

		//calculando o glcm   256x256
		//vizinho de superior esquerdo
		for (int i=1; i<(nlin); i++){
			for (int j=1; j<(ncol); j++){
				int linha = *(*(imagem+i)+j);
				int coluna = *(*(imagem+i-1)+j-1);
				*(*(glcm + linha)+coluna) += 1
			}
		}

		contraste = 0;

		//calculando o contraste
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				contraste += pow((i-j),2) * *(*(glcm+i)+j);
			}
		}

		energia = 0;

		//calculando a energia
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				energia += pow(campo, 2);
			}
		}

		homogeneidade = 0;

		//calculando a homogeneidade
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				if (i<=j) {
					homogeneidade += campo/ (1+(i-j));
				}
				else{
					homogeneidade += campo/(1+(j-i));
				}
			}
		}

		*(treinamento+a) = (int *) realloc(530, sizeof(int)); //declarando os novo tamanho dos dados da imagem

		*(*(treinamento+a)+527) = contraste;
		*(*(treinamento+a)+528) = energia;
		*(*(treinamento+a)+529) = homogeneidade;

		//limpando a matriz glcm
		for (int i=0; i<256; i++) {
			free (*(glcm+i));
		}
		free (glcm);



		//fazendo o glcm da setima direção
		**glcm;

		glcm = (int **) malloc(256*sizeof(int));

		if (glcm==NULL){
			printf("A locação falhou\n");
			exit(1);
		}

		for (int i=0; i<256; i++){
			*(glcm + i) = (int *) calloc(256, sizeof(int))

			if (*(glcm + i) == NULL){
				printf("A locação falhou\n");
				exit(1);
			}
		}

		//calculando o glcm   256x256
		//vizinho superior
		for (int i=1; i<(nlin); i++){
			for (int j=0; j<(ncol); j++){
				int linha = *(*(imagem+i)+j);
				int coluna = *(*(imagem+i-1)+j);
				*(*(glcm + linha)+coluna) += 1
			}
		}

		contraste = 0;

		//calculando o contraste
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				contraste += pow((i-j),2) * *(*(glcm+i)+j);
			}
		}

		energia = 0;

		//calculando a energia
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				energia += pow(campo, 2);
			}
		}

		homogeneidade = 0;

		//calculando a homogeneidade
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				if (i<=j) {
					homogeneidade += campo/ (1+(i-j));
				}
				else{
					homogeneidade += campo/(1+(j-i));
				}
			}
		}

		*(treinamento+a) = (int *) realloc(533, sizeof(int)); //declarando os novo tamanho dos dados da imagem

		*(*(treinamento+a)+530) = contraste;
		*(*(treinamento+a)+531) = energia;
		*(*(treinamento+a)+532) = homogeneidade;

		//limpando a matriz glcm
		for (int i=0; i<256; i++) {
			free (*(glcm+i));
		}
		free (glcm);



		//fazendo o glcm da oitava direção
		**glcm;

		glcm = (int **) malloc(256*sizeof(int));

		if (glcm==NULL){
			printf("A locação falhou\n");
			exit(1);
		}

		for (int i=0; i<256; i++){
			*(glcm + i) = (int *) calloc(256, sizeof(int))

			if (*(glcm + i) == NULL){
				printf("A locação falhou\n");
				exit(1);
			}
		}

		//calculando o glcm   256x256
		//vizinho superior direito
		for (int i=1; i<(nlin); i++){
			for (int j=0; j<(ncol-1); j++){
				int linha = *(*(imagem+i)+j);
				int coluna = *(*(imagem+i-1)+j+1);
				*(*(glcm + linha)+coluna) += 1
			}
		}

		contraste = 0;

		//calculando o contraste
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				contraste += pow((i-j),2) * *(*(glcm+i)+j);
			}
		}

		energia = 0;

		//calculando a energia
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				energia += pow(campo, 2);
			}
		}

		homogeneidade = 0;

		//calculando a homogeneidade
		for (int i=0; i<256; i++){
			for (int j=0; j<256; j++){
				int campo = *(*(glcm+i)+j);
				if (i<=j) {
					homogeneidade += campo/ (1+(i-j));
				}
				else{
					homogeneidade += campo/(1+(j-i));
				}
			}
		}

		*(treinamento+a) = (int *) realloc(536, sizeof(int)); //declarando os novo tamanho dos dados da imagem

		*(*(treinamento+a)+533) = contraste;
		*(*(treinamento+a)+534) = energia;
		*(*(treinamento+a)+535) = homogeneidade;

		//limpando a matriz glcm
		for (int i=0; i<256; i++) {
			free (*(glcm+i));
		}
		free (glcm);

	}


	//liberando a memoria dos valores de grama
	for (int i=0; i<50; i++) {
		free (* (treinamento + i));
	}
	free (treinamento);

	return 0;
}