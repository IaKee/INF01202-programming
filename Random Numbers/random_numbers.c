//Aula pratica 6
#include <stdio.h>
#include <time.h>
#define NUM_VALORES 10

float aleatorios[NUM_VALORES]; //Declara e inicia como nula uma string
float x, teste, valor_distante, diferenca;
int i; //Incrementador do for

int main()
{
    srand(time(NULL));
    printf("Aula pratica 6 - Numeros aleatorios e sequencia");

    printf("\n\nValores aleatorios do arranjo:");
    i=0;
    for(i=0; i<NUM_VALORES; i++){
        x = (rand()%100); //Numero random bem alto, de 10k a 100k
        aleatorios[i] = x;
        printf(" %.f", aleatorios[i]);
    }

    printf("\nInforme um valor teste: ");
    scanf("%f", &teste);

    valor_distante = aleatorios[0];

    for(i=1; i<NUM_VALORES; i++){
        if(fabs(aleatorios[i]-teste) > fabs(valor_distante-teste)){
            valor_distante = aleatorios[i];
        }
    }

    printf("O valor mais distante do valor teste eh: %.f", valor_distante);

    return 0;

} //Fim do programa
