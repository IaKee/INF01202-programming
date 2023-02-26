//Calculador de saldo de conta bancaria

#include <stdio.h>

float saldoinicial, valoropera, saldofinal;
int operacao; //0 se saque, 1 se deposito

int main(){
printf("Calculador de saldo de conta bancaria\n");

printf("\nInforme o saldo inicial da conta: R$");
scanf("%f", &saldoinicial);

if(saldoinicial < 0){
    printf("\nCuidado! Saldo negativo!\n"); }

if(saldoinicial == 0){
    printf("\nCuidado! Saldo zero!\n"); }

printf("\nQual operacao voce deseja realizar (0 - saque | 1- deposito): ");
scanf("%d", &operacao);

if(operacao == 0){
    printf("\nDigite o valor que voce deseja sacar: R$");
    scanf("%f", &valoropera);
    valoropera = (valoropera*(-1)); }

if(operacao == 1){
    printf("\nDigite o valor que voce deseja depositar: R$");
    scanf("%f", &valoropera); }

saldofinal = saldoinicial + valoropera;

printf("\nSeu saldo final eh: R$%.2f", saldofinal);

if(saldofinal < 0){
    printf("\nCuidado! Saldo negativo!\n"); }

if(saldofinal == 0){
    printf("\nCuidado! Saldo zero!\n"); } } //Fim do programa
