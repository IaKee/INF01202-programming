// Calculador de logaritmo natural de (x+1) para x entre -1 a 1
// Aluno: Giordano Souza de Paula
// Matricula: 00308045
// Aula Pratica 5 - Exercicio 1

#include <stdio.h>
#include <math.h>

float valor_x, logaritmando, logaritmo, termo_prox, termo_ant; //Variaveis usadas no calculo do logaritmo
int n_aproximacao, termo_atual; //Variavel que armazena o numero de termos usados na aproximacao

int main(){
    printf("Calculador de ln(x+1) para valores x entre -1 e 1");

    do{ //Enquanto o valor de X digitado nao estiver no intervalo...
        printf("\n\nEntre com um valor para X no intervalo (-1, 1]: ");
        scanf("%f", &valor_x);
        if(valor_x > 1 || valor_x <= -1){
            printf("Valor invalido! Por favor digite novamente..."); }
    } while (valor_x > 1 || valor_x <= -1); //O programa pede um novo valor X

    logaritmando = (valor_x + 1.0);

    do{
        termo_ant = termo_prox;
        termo_prox = (pow(valor_x, termo_atual)/termo_atual);
        if(termo_atual%2 != 0 ){ //Se for impar
            termo_prox= (termo_prox * (1));
            termo_atual++; }
        if(termo_atual%2 == 0 ){ //Se for par
            termo_prox= (termo_prox * (-1));
            termo_atual++; }
    } while ();

    printf("O valor aproximado de ln(%1.4f", logaritmando);
    printf(") eh %f", logaritmo);
    printf("\nForam usados %d", termo_atual);
    printf(" termos na aproximacao.");

return 0; } //Fim do programa
