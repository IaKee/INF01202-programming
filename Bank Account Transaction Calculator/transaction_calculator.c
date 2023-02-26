/* Programa que fornece o saldo atualizado de uma conta bancaria */

#include <stdio.h>

float saldoatual, saldoinicial, valoropera1, valoropera2, valoropera3;

int main(){
printf("Calculador de saldo bancario \n");

printf("Por favor, entre com o saldo inicial (em reais): R$");
scanf("% .2f", &saldoinicial);

if (saldoatual < 0){
    printf("\nCuidado! Saldo negativo! \n"); }

printf("\nEntre com o valor da primeira operação (em reais): R$");
scanf("% .2f", valoropera1);
saldoatual = saldoinicial + valoropera1;
printf("\nO saldo parcial eh de: R$ %.2f", saldoatual, "\n");

if (saldoatual < 0){
    printf("\nCuidado! Saldo negativo! \n"); }

printf("\nEntre com o valor da segunda operação (em reais): R$");
scanf("% .2f", valoropera2);
saldoatual = saldoinicial + valoropera1 + valoropera2;
printf("\nO saldo parcial eh de: R$ %.2f", saldoatual, "\n");

if (saldoatual < 0){
    printf("\nCuidado! Saldo negativo! \n"); }

printf("\nEntre com o valor da terceira operação (em reais): R$");
scanf("% .2f", valoropera3);
saldoatual = saldoinicial + valoropera1 + valoropera2 + valoropera3;
printf("\nO saldo parcial eh de: R$ %.2f", saldoatual, "\n"); }
