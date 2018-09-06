#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void fneuronio(float *entradas, float *pesos, float t, int n, int *resultado);

int main(int argc, char const *argv[]) {
    float entradas[MAX], pesos[MAX], t;
	int resultado;

    printf("Entre com 10 valores para as entradas: ");
    for(int i = 0; i < MAX; i++) {
        scanf("%f", &entradas[i]);
    }
    
    printf("Entre com 10 valores para os pesos: ");
    for(int i = 0; i < MAX; i++) {
        scanf("%f", &pesos[i]);
    }

    printf("Entre com o valor da limiar: ");
    scanf("%f", &t);

    fneuronio(entradas, pesos, t, MAX, &resultado);

    if(resultado == 1) printf("Neurônio Ativado!");
    else if(resultado == 0) printf("Neurônio Inibido!");
    else printf("Erro na execução! :/");

    return 0;
}

void fneuronio(float *entradas, float *pesos, float t, int n, int *resultado) {
    float SOMAP = 0;
    for(int i = 0; i < n; i++) {
        SOMAP += *(entradas + i) * *(pesos + i);
    }
    if(SOMAP > t) *resultado = 1;
    else *resultado = 0;
}