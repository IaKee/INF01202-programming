/* Sequencia de Fibonacci */
#include <stdio.h>

int solicitacao; //Quantos numeros da sequencia o usuario deseja ver
int i; //Incrementador do for
int n_atual, n_prox, n_ant;

int main ( ){

 printf("Sequencia de fibonacci");

 printf("\n\nQuantos termos deseja ver: ");
 scanf("%d", &solicitacao); // de termos a serem gerados – deveria ser consistido
 if (solicitacao < 1){
     printf("Numero informado deve ser inteiro positivo e nao nulo"); }
     else{
            n_prox=1; // inicializa termos
            n_ant=1;

 for (i=1 ; i <= solicitacao; i++){ // apenas 1 comando: sem { }
    if (i == 1 || i == 2){ // 2 primeiros termos da série são iguais
        printf("1 "); } // ou n_ant, tanto faz
        else {
            n_atual = n_prox + n_ant; // calcula termo atual;
            printf("%d ", n_atual); // imprime termo calculado e
            n_ant = n_prox; //atualiza conteúdos anteriores, já
            n_prox = n_atual; // preparando para o calculo do próximo termo
 } } }
  if (solicitacao >= 10000){
    printf("\n\n\nEita cussao '-'\n\n\n"); }
 return 0;}

