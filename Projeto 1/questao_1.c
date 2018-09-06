#include <stdio.h>
#define MAX 2

void fneuronio(double* , double* , double,  int, int* );

int main()
{
	double ENTRADA[MAX];
	double PESOS[MAX];
	double T;
	int resultado;
	
	printf("Insira os %d valores do vetor ENTRADA:\n", MAX);
	for(int i=0; i<MAX; i++)
		scanf("%lf", &ENTRADA[i]);
	
	printf("Insira os %d valores do vetor PESOS:\n", MAX);
	for(int i=0; i<MAX; i++)
		scanf("%lf", &PESOS[i]);
		
	printf("Insira o limiar T:\n");
	scanf("%lf", &T);
	
	/*
	for(int i=0; i<MAX; i++)
		printf("ENTRADA[%d]: %lf \t PESOS[%d]: %lf\n", i, ENTRADA[i], i, PESOS[i]);
	printf("T: %lf\n", T);
	
	return 0;
	*/
	fneuronio(ENTRADA, PESOS, T, MAX, &resultado);
	if(resultado==0)
		printf("Neurôno inibido!\n");
	else 
		printf("Neurônio ativado!\n");
	
	
}

void fneuronio(double *ENTRADA, double *PESOS, double T,  int tamanho, int *resultado)
{
	double SOMAP=0;
	for(int i=0; i<tamanho; i++)
	{
		SOMAP+=(*(ENTRADA+i))*(*(PESOS+i));
	}
	if(SOMAP>T)
		*resultado=1;
	else 
		*resultado=0;
		
}
