/* Calculador da soma dos numeros pares em um intervalo N */

#include <stdio.h>

int valor_n1, valor_n2, menorval, maiorval;
int soma;
int contador; //Utilizado no for

int main (){
    printf("Calculador da soma dos numeros pares em um intervalo N\n\n");

    printf("Entre com dois valores inteiros (intervalo da soma entre pares): ");
    scanf("%d", &valor_n1);
    scanf("%d", &valor_n2);

    if(valor_n1 > valor_n2){
        maiorval = valor_n1;
        menorval = valor_n2; }

    if(valor_n1 < valor_n2){
        maiorval = valor_n2;
        menorval = valor_n1; }

    for(contador = menorval; contador <= maiorval; contador++) {
        if(contador%2==0){ //Se o resto da divisao por 2 for zero, o numero e par
            soma = soma + contador; } } //Fim do for

            printf("\n\nO resultado da soma eh: %d", soma);

return 0; } //Fim do programa
