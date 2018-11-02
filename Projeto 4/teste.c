#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
	char codigo[7];
	char modo;
	int combustivel;
	struct lista *proximo;
} Lista;

int main () {
	Lista *a = NULL;

	a = (Lista *) malloc (sizeof(Lista));

	strcpy (a->codigo, "tiago");

	printf("%s\n", a->codigo);

	free(a);

	a = NULL;

	if (a==NULL){
		printf("a esta nullo\n");
	}
	else{
		printf("a não esta nulo\n");
	}

}