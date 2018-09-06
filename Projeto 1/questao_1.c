#include <stdio.h>
#define MAX 10

int fneuronio(double* , double* , double,  int);

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
	resultado=fneuronio(ENTRADA, PESOS, T, MAX);
	if(resultado==0)
		printf("Neurôno inibido!\n");
	else 
		printf("Neurônio ativado!\n");
	
	
}

int fneuronio(double* ENTRADA, double* PESOS, double T,  int tamanho)
{
	double resultado=0;
	for(int i=0; i<tamanho; i++)
	{
		resultado+=(*(ENTRADA+i))*(*(PESOS+i));
	}
	if(resultado>T)
		return 1;
	else 
		return 0;
		
}
