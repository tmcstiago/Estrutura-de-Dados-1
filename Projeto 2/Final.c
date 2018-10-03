#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define N_IMAGENS 25



//função para calcular as metricas da imagem
//parametros ==> matriz para armazenar o vetor da imagem, matriz da imagem, qnt de linhas,
//				 qnt de colunas, linha da matriz para armazenar o vetor
void ilbp_glcm (int **treinamento, int **imagem,int nlin, int ncol, int a);
void get_random_file( char * file_path, char * img_type);
int ilbp (int *matriz, float media);
<<<<<<< HEAD:Projeto 2/Final.c
void bubbleSort(int *vetor, int tamanho);
float distancia_euclidiana(float *treinamento, float *teste, int tamanho);
=======
void normaliza_dados(float *vetor, float *vetor_normalizado);
>>>>>>> 2e6f68c716fef532196c181b8cb7e151b227b80f:Projeto 2/Projeto2.c

int main()
{

	int **treinamento; //armazenando os veetores das imagens de treinamento

	srand(time(0));	// Usado para rand() gerar número aleátorio cada vez que rodado

	//Geração aleatória dos 25 nomes de arquivos aleatórios e distintos
	//Arquivos de índice 0 até 24 serão usados no treinamento 
	//Arquivos do índice 25 até 49 serão usados na outra parte do código
	char asphalt_path[N_IMAGENS*2][50];
	char grass_path[N_IMAGENS*2][50];
	for(int i=0; i<N_IMAGENS*2; i++){
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
	}
		
	//Leitura dos arquivos	
	for(int a=0; a<50; a++){
		int nlin, ncol;
		int **imagem;
		FILE *arquivo;
		char path[50];
		if(a%2==0){
			strcpy(path, grass_path[a/2]);
		}
		else{
			strcpy(path, asphalt_path[a/2]);
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
		printf("Calculado...\n");

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


		ilbp_glcm (treinamento, imagem, nlin, ncol, a); //calculando as metricas da imagem
		

		
		bubbleSort(treinamento[a] , 536);

		//for (int j=0; j<536; j++){
		//	printf("%d ", *(*(treinamento+a)+j));
		//}
		//printf("\n");

		// Normalização do vetor
		double normalize[536];
		for (int j=0; j<536; j++){
			normalize[j]= (double)(treinamento[a][j]-treinamento[a][0])/(treinamento[a][535]-treinamento[a][0]);
		}
		for (int j=0; j<536; j++){
			//printf("%lf ", normalize[j]);
		}
	
		//Liberação da memória alocada para imagem[]
		for(int i=0; i<ncol; i++)
			free(imagem[i]);
		free(imagem);
	}
	float *grama, *asfalto;
	
	grama=(float *)calloc(536, sizeof(float));
	asfalto=(float *)calloc(536, sizeof(float));

	if (grama == NULL || asfalto == NULL){
		printf("Alocação falhou, Finalizado.\n");
		exit(1);
	}
	for(int i=0; i<50; i++){
		for(int j=0; j<536; j++){
			if(i%2==0){
				grama[j]+=treinamento[i][j];			
			}
			else{
				asfalto[j]+=treinamento[i][j];
			}	
		}
	}
	for(int i=0; i<536; i++){
		grama[i]/=25;
		asfalto[i]/=25;
	}
	double grama_normalize[536];
	double asfalto_normalize[536];
	bubbleSort(grama , 536);
	bubbleSort(asfalto , 536);
	for (int j=0; j<536; j++){
		grama_normalize[j]= (double)(grama[j]-grama[0])/(grama[535]-grama[0]);
		asfalto_normalize[j]= (double)(asfalto[j]-asfalto[0])/(asfalto[535]-asfalto[0]);
	}
	int erro_grama=0; int acerto_grama=0;
	int erro_asfalto=0; int acerto_asfalto=0;
	int **teste;

	for(int a=0; a<50; a++){
		int nlin, ncol;
		int **imagem;
		FILE *arquivo;
		char path[50];
		if(a%2==0){
			strcpy(path, grass_path[a/2+25]);
		}
		else{
			strcpy(path, asphalt_path[a/2+25]);
		}
		arquivo = fopen(path, "r");

<<<<<<< HEAD:Projeto 2/Final.c
		printf("Lendo.. %s\n", path);
=======
	float **treinamento_normalizado;

	int i=0;
	for(i = 0; i < 50; i++) {
		normaliza_dados(*(treinamento+i), *(treinamento_normalizado + i));
	}
>>>>>>> 2e6f68c716fef532196c181b8cb7e151b227b80f:Projeto 2/Projeto2.c

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
		printf("Calculado...\n");

		
		if (a==0){
			teste = (int**) malloc(1*sizeof(int *));
		}
		else {
			teste = (int **) realloc(teste, (a+1)*sizeof(int *));
		}
		if (teste==NULL){
			printf("A alocação falhou\n");
			exit(1);
		}

		//espaço para armazenar o vetor ilbp
		*(teste+a) = (int *) calloc(512, sizeof(int));
		if (*(teste + (a-1))==NULL){
			printf("A alocação falhou\n");
			exit(1);
		}

		ilbp_glcm (teste, imagem, nlin, ncol, a); //calculando as metricas da imagem
		
		float normalize[536];
		bubbleSort (teste[a] , 536);
		for (int j=0; j<536; j++){
			normalize[j]= (double)(teste[a][j]-teste[a][0])/(teste[a][535]-teste[a][0]);
		}
		float d_euclidiana_grama, d_euclidiana_asfalto;

		d_euclidiana_grama=distancia_euclidiana(grama_normalize, normalize, 536);		
		d_euclidiana_asfalto=distancia_euclidiana(asfalto_normalize, normalize, 536);
		//Grama
		if(a%2==0){
			if(d_euclidiana_grama<d_euclidiana_asfalto)
				acerto_grama++;
			else
				erro_grama++;
		}
		//Asfalto
		else{
			if(d_euclidiana_grama>d_euclidiana_asfalto)
				acerto_asfalto++;
			else
				erro_asfalto++;

		}
		for(int i=0; i<ncol; i++)
			free(imagem[i]);
		free(imagem);
	}
	
	float acerto = (float)(acerto_grama+acerto_asfalto)/(erro_grama+erro_asfalto+acerto_grama+acerto_asfalto);
	float falsa_aceitacao = (float)acerto_asfalto/(acerto_asfalto+erro_asfalto);
	float falsa_rejeicao = (float)acerto_asfalto/(acerto_asfalto+erro_asfalto);
	printf ("Taxa de acerto = %.2f %\n", acerto*100);
	printf ("Taxa de falsa aceitacao = %.2f %\n", falsa_aceitacao*100);
	printf ("Taxa de falsa rejeicao = %.2f %\n", falsa_rejeicao*100);
	
	//liberando a memoria dos valores de grama
	for (int i=0; i<50; i++) {
		free (* (treinamento + i));
	}
	free (treinamento);

<<<<<<< HEAD:Projeto 2/Final.c

	free(grama);
	free(asfalto);

	for (int i=0; i<50; i++) {
		free (* (teste + i));
	}
	free (teste);

	return 0;
}
float distancia_euclidiana(float *treinamento, float *teste, int tamanho){
	float distancia=0;
	for(int i=0; i<tamanho; i++){
		float x = 0;
		x = treinamento[i]-teste[i];
		distancia+= pow(x,2);
	}
	distancia = sqrt(distancia);
	return distancia;

}
void bubbleSort(int *vetor, int n){
	int k, j, aux;
    for (k = 1; k < n; k++) {
        for (j = 0; j < n - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}
=======
	free(treinamento);

	return 0;
}
>>>>>>> 2e6f68c716fef532196c181b8cb7e151b227b80f:Projeto 2/Projeto2.c

void get_random_file(char * file_path, char * img_type){
		
	int random_50 = (rand()%50)+1; //Gera número aleatório de 1 a 50 
	sprintf(file_path ,"./DataSet/%s/%s_%02d.txt", img_type, img_type, random_50);
	
}


void ilbp_glcm (int **treinamento, int **imagem,int nlin, int ncol, int a) {
	

	// estrutura para calcular o resultado das matrizes 3x3
	for (int i=1; i<(nlin-1); i++){
		for (int j=1; j<(ncol-1); j++){
			int matriz[3][3]; // matriz a ser enviada pra função
			int *p = matriz;
			float media = 0.0;

			//passando os valores para a matriz
			for (int m=0; m<3; m++){
				for (int n=0; n<3; n++){
					matriz[m][n] = *(*(imagem+i+m-1)+n+j+1);
					media += matriz[m][n]; //calculando a media entre os dados
				}
			}

			media = (float) media/9;
			int menor = ilbp(matriz, media);

			//incrementando o valor obtido no resultado
			*(*(treinamento+a)+menor) += 1;
		}
	}
																		

	int **glcm;

	glcm = (int **) malloc(256*sizeof(int*));

	if (glcm==NULL){
		printf("A locação falhou\n");
		exit(1);
	}

	for (int i=0; i<256; i++){
		*(glcm + i) = (int *) calloc(256, sizeof(int));

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
			*(*(glcm + linha)+coluna) = *(*(glcm + linha)+coluna)+1;
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
				homogeneidade += campo/ (1+(j-i));
			}
			else{
				homogeneidade += campo/(1+(i-j));
			}
		}
	}

	*(treinamento+a) = (int *) realloc(*(treinamento+a), 515*sizeof(int)); //declarando os novo tamanho dos dados da imagem

	*(*(treinamento+a)+512) = contraste;
	*(*(treinamento+a)+513) = energia;
	*(*(treinamento+a)+514) = homogeneidade;

	//limpando a matriz glcm
	for (int i=0; i<256; i++) {
		free (*(glcm+i));
	}
	free (glcm);



	//fazendo o glcm da segunda direção
	glcm = (int **) malloc(256*sizeof(int*));

	if (glcm==NULL){
		printf("A locação falhou\n");
		exit(1);
	}

	for (int i=0; i<256; i++){
		*(glcm + i) = (int *) calloc(256, sizeof(int));

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
			*(*(glcm + linha)+coluna) = *(*(glcm + linha)+coluna)+1;
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
				homogeneidade += campo/ (1+(j-i));
			}
			else{
				homogeneidade += campo/(1+(i-j));
			}
		}
	}

	*(treinamento+a) = (int *) realloc(*(treinamento+a), 518*sizeof(int)); //declarando os novo tamanho dos dados da imagem

	*(*(treinamento+a)+515) = contraste;
	*(*(treinamento+a)+516) = energia;
	*(*(treinamento+a)+517) = homogeneidade;

	//limpando a matriz glcm
	for (int i=0; i<256; i++) {
		free (*(glcm+i));
	}
	free (glcm);



	//fazendo o glcm da terceira direção
	glcm = (int **) malloc(256*sizeof(int*));

	if (glcm==NULL){
		printf("A locação falhou\n");
		exit(1);
	}

	for (int i=0; i<256; i++){
		*(glcm + i) = (int *) calloc(256, sizeof(int));

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
			*(*(glcm + linha)+coluna) = *(*(glcm + linha)+coluna)+1;
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
				homogeneidade += campo/ (1+(j-i));
			}
			else{
				homogeneidade += campo/(1+(i-j));
			}
		}
	}

	*(treinamento+a) = (int *) realloc(*(treinamento+a), 521*sizeof(int)); //declarando os novo tamanho dos dados da imagem

	*(*(treinamento+a)+518) = contraste;
	*(*(treinamento+a)+519) = energia;
	*(*(treinamento+a)+520) = homogeneidade;

	//limpando a matriz glcm
	for (int i=0; i<256; i++) {
		free (*(glcm+i));
	}
	free (glcm);



	//fazendo o glcm da quarta direção
	glcm = (int **) malloc(256*sizeof(int*));

	if (glcm==NULL){
		printf("A locação falhou\n");
		exit(1);
	}

	for (int i=0; i<256; i++){
		*(glcm + i) = (int *) calloc(256, sizeof(int));

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
			*(*(glcm + linha)+coluna) = *(*(glcm + linha)+coluna)+1;
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
				homogeneidade += campo/ (1+(j-i));
			}
			else{
				homogeneidade += campo/(1+(i-j));
			}
		}
	}

	*(treinamento+a) = (int *) realloc(*(treinamento+a), 524*sizeof(int)); //declarando os novo tamanho dos dados da imagem

	*(*(treinamento+a)+521) = contraste;
	*(*(treinamento+a)+522) = energia;
	*(*(treinamento+a)+523) = homogeneidade;

	//limpando a matriz glcm
	for (int i=0; i<256; i++) {
		free (*(glcm+i));
	}
	free (glcm);



	//fazendo o glcm da quinta direção
	glcm = (int **) malloc(256*sizeof(int*));

	if (glcm==NULL){
		printf("A locação falhou\n");
		exit(1);
	}

	for (int i=0; i<256; i++){
		*(glcm + i) = (int *) calloc(256, sizeof(int));

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
			int coluna = *(*(imagem+i)+j-1);
			*(*(glcm + linha)+coluna) = *(*(glcm + linha)+coluna)+1;
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
				homogeneidade += campo/ (1+(j-i));
			}
			else{
				homogeneidade += campo/(1+(i-j));
			}
		}
	}

	*(treinamento+a) = (int *) realloc(*(treinamento+a), 527*sizeof(int)); //declarando os novo tamanho dos dados da imagem

	*(*(treinamento+a)+524) = contraste;
	*(*(treinamento+a)+525) = energia;
	*(*(treinamento+a)+526) = homogeneidade;

	//limpando a matriz glcm
	for (int i=0; i<256; i++) {
		free (*(glcm+i));
	}
	free (glcm);



	//fazendo o glcm da sexta direção
	glcm = (int **) malloc(256*sizeof(int*));

	if (glcm==NULL){
		printf("A locação falhou\n");
		exit(1);
	}

	for (int i=0; i<256; i++){
		*(glcm + i) = (int *) calloc(256, sizeof(int));

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
			*(*(glcm + linha)+coluna) = *(*(glcm + linha)+coluna)+1;
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
				homogeneidade += campo/ (1+(j-i));
			}
			else{
				homogeneidade += campo/(1+(i-j));
			}
		}
	}

	*(treinamento+a) = (int *) realloc(*(treinamento+a), 530*sizeof(int)); //declarando os novo tamanho dos dados da imagem

	*(*(treinamento+a)+527) = contraste;
	*(*(treinamento+a)+528) = energia;
	*(*(treinamento+a)+529) = homogeneidade;

	//limpando a matriz glcm
	for (int i=0; i<256; i++) {
		free (*(glcm+i));
	}
	free (glcm);



	//fazendo o glcm da setima direção
	glcm = (int **) malloc(256*sizeof(int*));

	if (glcm==NULL){
		printf("A locação falhou\n");
		exit(1);
	}

	for (int i=0; i<256; i++){
		*(glcm + i) = (int *) calloc(256, sizeof(int));

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
			*(*(glcm + linha)+coluna) = *(*(glcm + linha)+coluna)+1;
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
				homogeneidade += campo/ (1+(j-i));
			}
			else{
				homogeneidade += campo/(1+(i-j));
			}
		}
	}

	*(treinamento+a) = (int *) realloc(*(treinamento+a), 533*sizeof(int)); //declarando os novo tamanho dos dados da imagem

	*(*(treinamento+a)+530) = contraste;
	*(*(treinamento+a)+531) = energia;
	*(*(treinamento+a)+532) = homogeneidade;

	//limpando a matriz glcm
	for (int i=0; i<256; i++) {
		free (*(glcm+i));
	}
	free (glcm);



	//fazendo o glcm da oitava direção
	glcm = (int **) malloc(256*sizeof(int*));

	if (glcm==NULL){
		printf("A locação falhou\n");
		exit(1);
	}

	for (int i=0; i<256; i++){
		*(glcm + i) = (int *) calloc(256, sizeof(int));

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
			*(*(glcm + linha)+coluna) = *(*(glcm + linha)+coluna)+1;
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
				homogeneidade += campo/ (1+(j-i));
			}
			else{
				homogeneidade += campo/(1+(i-j));
			}
		}
	}

	*(treinamento+a) = (int *) realloc(*(treinamento+a), 536*sizeof(int)); //declarando os novo tamanho dos dados da imagem

	*(*(treinamento+a)+533) = contraste;
	*(*(treinamento+a)+534) = energia;
	*(*(treinamento+a)+535) = homogeneidade;


	//limpando a matriz glcm
	for (int i=0; i<256; i++) {
		free (*(glcm+i));
	}
	free (glcm);
}

int ilbp (int *matriz, float media){
	int binario[3][3];
	int menor = 512;
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
		if (p[i] < menor) {
			menor = p[i];
		}
	}

	return menor;
}

void normaliza_dados(float *vetor, float *vetor_normalizado) {

  int i;
  float menor = 0, maior = 9999999;

  // Define os valores menor e maior dentro do vetor
  for (i = 0; i < 536; i++) {
    if (*(vetor + i) > maior) {
      maior = *(vetor + i);
    }
    if (menor > *(vetor + i)) {
      menor = *(vetor + i);
    }
  }

  // Vetor normalizado usando o cálculo definido no projeto
  for (i = 0; i < 536; i++) {
    *(vetor_normalizado + i) = (*(vetor_normalizado + i) - menor) / (maior - menor);
  }
}


/**
 * 
 * 
 */
// float distancia_euclidiana(float *referencia, float **comparador, int contador) {

//   // Declaração de variáveis locais.
//   int i, j;
//   float resultado = 0.0, elemento_vetor_referencia, elemento_vetor_comparador, diferenca;

//   // faz a distância euclidiana entre os vetores.
//   for (j = 0; j < 536; j++) {
//     elemento_vetor_referencia = *(referencia + j);
//     elemento_vetor_comparador = *(*(comparador+posicao)+j);
//     diferenca = elemento_vetor_referencia - elemento_vetor_comparador;
//     resultado += pow(diferenca, 2);
//   }
//   resultado = sqrt(resultado);

//   return resultado;
// }