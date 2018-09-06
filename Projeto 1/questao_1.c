#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int fneuronio(float *entradas, float *pesos, float t, int n);

int main(int argc, char const *argv[]) {
    float entradas[MAX], pesos[MAX], t;

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

    int checa_neuronio = fneuronio(entradas, pesos, t, MAX);

    if(checa_neuronio == 1) printf("Neurônio Ativado!");
    else if(checa_neuronio == 0) printf("Neurônio Inibido!");
    else printf("Erro na execução! :/");

    return 0;
}

int fneuronio(float *entradas, float *pesos, float t, int n) {
    float SOMAP = 0;
    int resultado = 0;
    int *result = &resultado;
    for(int i = 0; i < n; i++) {
        SOMAP += *(entradas + i) * *(pesos + i);
    }
    if(SOMAP > t) *result = 1;
    else *result = 0;

    return resultado;
}