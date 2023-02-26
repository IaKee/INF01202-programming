//Aula pratica 6
#include <stdio.h>
#define N 5

float aleatorios[N]; //Declara e inicia como nula uma string
float x, soma, media;
int i; //Incrementador do for

int main()
{
    printf("Aula pratica 6 - Numeros aleatorios e sequencia");

    soma = 0.0;
    media = 0.0;

    printf("\n\nArranjo aleatoriamente preenchido:\n");
    for(i=0; i<N; i++){
        scanf("%f", &aleatorios[i]);
        soma = soma + aleatorios[i];
    }

    media = soma/i;
    printf("\nA media eh: %f", media);

    printf("\nOs valores menores ou iguais a media sao: ");
    for(i=0; i<N; i++){
        if(aleatorios[i] <= media){
            printf(" %.2f", aleatorios[i]);
            printf(";");
        }
    }
    printf("\nOs valores maiores que a media sao:");
    for(i=0; i<N; i++){
        if(aleatorios[i] > media){
            printf(" %.2f", aleatorios[i]);
            printf(";");
        }
    }
    return 0;
} //Fim do programa
