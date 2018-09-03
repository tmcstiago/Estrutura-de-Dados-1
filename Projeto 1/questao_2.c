#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int *recebe_notas (int *, int*, int);
int *conta_notas (int *, int* ,int);
int *percentual_notas (int *, float* ,int);

int main () {

	int opcao, *p;
	int NOTAS[MAX];
	int APR[MAX], qnt_apr_rep[2];
	float perc_apr_rep[2];

	printf("Insira a nota dos %d alunos:\n", MAX);

	for (int i=0; i<MAX; i++){
		scanf ("%d", &NOTAS[i]);
	}

	//chama as funçoes para calcular os valores e evitar erros para o usuario
	recebe_notas(NOTAS, APR, MAX);
	conta_notas(APR, qnt_apr_rep, MAX);

	do {
		printf("\n");
		printf("\n");

		printf ("Selecione a opção desejada:\n1. Quantidade de Aprovados\n2. Quantidade de Reprovados\n3. Percentual de Aprovados\n4. Percentual de Reprovados\n5. Mais da da metade da turma foi aprovada?\n6. Sair\n");
		scanf ("%d", &opcao);
		printf("\n");

		switch (opcao){
			case 1:
				p = conta_notas(APR, qnt_apr_rep, MAX);
				printf("Quantidade de alunos aprovados: %d\n", *(p));
			break;
			case 2:
				p = conta_notas(APR, qnt_apr_rep, MAX);
				printf("Quantidade de alunos reprovados:%d\n",*(p+1));
			break;
			case 3:
				percentual_notas(qnt_apr_rep, perc_apr_rep, MAX);
				printf("Percentual de alunos aprovados:%.2f%\n",*(perc_apr_rep));
			break;
			case 4:
				percentual_notas(qnt_apr_rep, perc_apr_rep, MAX);
				printf("Percentual de alunos reprovados:%.2f%\n",*(perc_apr_rep+1));
			break;
			case 5:
				if(percentual_notas(qnt_apr_rep, perc_apr_rep, MAX))
					printf("Mais da metade da turma aprovada!!\n");
				else
					printf("A turma obteve um pessimo aproveitamento :(\n");

			break;
		}
		
	} while (opcao != 6);

	return 0;
}

//função recebe a referencia do vetor de notas, a referencia do vetor que os valores serao quardados e a qnt maxima de alunos
int *recebe_notas(int *notas, int *apr, int x) {
	for (int i=0; i<x; i++){
		if (*(notas+i)>=6)
			*(apr+i) = 1;
		else
			*(apr+i) = 0;
	}	
	return apr;
}

//função recebe a referencia do vetor aprovados, a referencia do vetor que os valores serao quardados e a qnt maxima de alunos
int *conta_notas (int *apr, int*qnt ,int x){ 
	for (int i=0; i<2; i++)	
		*(qnt+i) = 0;

	for (int i=0; i<x; i++) {
		if (*(apr+i)==1)
			*(qnt) = *(qnt)+1;
		else
			*(qnt+1) = *(qnt+1)+1;
	}
	return qnt;
}

//função recebe a referencia do vetor qnt_aprovados, a referencia do vetor que os valores serao quardados e a qnt maxima de alunos
int *percentual_notas (int *qnt, float*perc ,int x){

	float aprovados = *qnt;
	*perc = aprovados*100/(float)x;
	*(perc+1) = (x-aprovados)*100/x;

	if (*perc>50){
		return 1;
	}
	else
		return 0;
}