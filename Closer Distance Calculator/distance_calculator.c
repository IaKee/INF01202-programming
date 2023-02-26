//PRATICA 7 - Exercicio 1
//Nome: Giordano Souza de Paula
//Cartao UFRGS: 00308054
#include <stdio.h>
#include <math.h>
#define N 3

int ponto_interessex, ponto_interessey, n_ponto, i, distx, disty; //Array 3x3 para armazenar as ponto_interesses
int coordenadas[2][N];
float menor_dist;

int main()
    {
    printf("Pratica 7 - Exercicio 1");
    printf("\nMenor distancia de um ponto definido, dentre tres pontos informados\n\n");

    printf("Informe a coordenada x do ponto de interesse: ");
    scanf("%d", &ponto_interessex);
    printf("Informe a coordenada y do ponto de interesse: ");
    scanf("%d", &ponto_interessey);

    /*VALORES DEFAULT*/
    n_ponto = 1;

    for(i=0; i < N; i++) //Pergunta pelas coordenadas N vezes
        {
        printf("\nInforme a coordenada x do ponto %d: ", n_ponto);
        scanf("%d", &coordenadas[i][0]);
        printf("Informe a coordenada y do ponto %d: ", n_ponto);
        scanf("%d", &coordenadas[i][1]);
        n_ponto++;
        /*CALCULA A DISTANCIA EM X e Y DO PONTO SIGNIFICATIVO*/
        distx = fabs(ponto_interessex - coordenadas[i][0]);
        disty = fabs(ponto_interessey - coordenadas[i][1]);

        if(i==0)
            {
            menor_dist = sqrt(pow(distx, 2) + pow(disty, 2));
            }
        if((sqrt(pow(distx, 2) + pow(disty, 2))) < menor_dist)
            {
            menor_dist = sqrt(pow(distx, 2) + pow(disty, 2)); //Atualiza o valor da menor distancia
            }
            }

    printf("\n\nA menor distancia encontrada entre pontos e o ponto definido foi de: \n%.2f unidades", menor_dist);

    return 0;
    } //Fim do programa
