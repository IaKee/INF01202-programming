/* Teste com barra de progresso */
#include <stdio.h>

int progresso_inteiro, n_caracteres, contador, n_hash, n_minus;
float progresso;

int main(){
    printf("Teste com barra de progresso\n\n");

    printf("Informe o tamanho da barra (em caracteres): ");
    scanf("%d", &n_caracteres);

    printf("\nAgora informe o passo de progresso nessa (de 0.0 a 1.0): ");
    scanf("%f", &progresso);

    printf("\n\nBarra de progresso: <");

    n_hash =(progresso * n_caracteres);
    n_minus = (n_caracteres - n_hash);

    for(contador = 0; contador < n_hash; contador++){
     printf("#"); }

    for(contador = 0; contador < n_minus; contador++){
     printf("-"); }

     printf(">");

return 0; } //Fim do programa
