/*  Calculador de soma e media de N valores */
#include <stdio.h>

int valor_n; //Armazena o valor n que o usuario deseja calcular
int contador; //Contador para o for
float valor_x;
float media, soma; //Media entre os valores informados e a soma


int main(){
    printf("Calculador de soma e media de N valores\n\n");

    printf("Informe a quantidade de valores que deseja calcular: ");
    scanf("%d", &valor_n);
    printf("\n");

    if(valor_n <= 0){
    printf("\n\nValor invalido!");
    printf("\nOs valores a serem informados a seguir devem ser positivos!\n\n");
    return 0; }

    for(contador=1; contador<= valor_n; contador++){ //Executa valor_n vezes
            printf("Informe o valor %d", contador);
            printf(": ");
            scanf("%f", &valor_x);
            soma = (soma + valor_x);    } //fim do for

    media = (soma/valor_n);
    printf("\nSoma dos valores: %f", soma);
    printf("\nMedia dos valores: %f", media);
    printf("\n\n");
return 0; } //Fim do programa
