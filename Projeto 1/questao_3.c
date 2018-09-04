#include <stdio.h>

void torreDeHanoi(char torre_inicial, char torre_auxiliar, char torre_final, unsigned int num_discos);
void imprimirMensagem(char torre_1, char torre_2);

int main()
{
	int num_discos;
	printf("Insira a quantidade de discos presentes na torre A:");
	scanf("%d", &num_discos);
	printf("Siga os passos em ordem:\n");
	torreDeHanoi('A','B','C', num_discos);
	return 0;
}

//Resolve a torre de Hanoi para N discos, 3 para torres em ordem 
void torreDeHanoi(char torre_inicial, char torre_auxiliar, char torre_final, unsigned int num_discos)
{
	if(num_discos==1)
	{
		imprimirMensagem(torre_inicial, torre_final);
	}
	else if(num_discos==2)
	{
		imprimirMensagem(torre_inicial, torre_auxiliar);
		imprimirMensagem(torre_inicial, torre_final);
		imprimirMensagem(torre_auxiliar, torre_final);
	}
	else
	{
		torreDeHanoi(torre_inicial,torre_final,torre_auxiliar,num_discos-1);
		imprimirMensagem(torre_inicial, torre_final);
		torreDeHanoi(torre_auxiliar, torre_inicial, torre_final,num_discos-1);
	}
}

void imprimirMensagem(char torre_1, char torre_2)
{
	printf("Passe o disco da torre %c para a torre %c\n", torre_1, torre_2);
}


