#include <stdio.h>
#include <stdlib.h>


typedef struct lista {
	char codigo[7];
	char modo;
	int combustivel;
	struct lista *proximo;
} Lista;

typedef struct fila {
	Lista *inicio;
	Lista *fim;
} Fila;


Fila iniciar_fila(* Fila);
Lista novo_voo(Fila *voos, Lista *novo);


int main () {

	Fila voos = iniciar_fila();  // criando a cabeça da fila

	// função para gerar os voos e o combustível
	
	// utilize a função novo_voo(*Fila, * Lista) para criar novo voo, sendo Fila = voos e Lista obj criado
		// lembre que voce ja deve mandar o dado definido igual no projeto anterior
			// observação: ao chamar a função, o Lista->proximo já deve ser igual a NULL


	//horario inicial do programa
	int hora = 6;
	int min = 0;


	for (min = 0; 1; ++i) {


	}

	return 0;
}


Fila iniciar_fila(){
	Fila *f;
	f = (* Fila) malloc(sizeof(Fila));

	f->inicio = NULL;
	f->fim = NULL;

	return f;
}


Lista novo_voo(Fila *voos, Lista *novo){
	if (voos->inicio == NULL){
		voos->inicio == novo;
		voos->fim == novo;
	}
	else {
		voos->fim->proximo = novo;
		voos->fim = novo
	}
}
