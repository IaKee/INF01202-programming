/* Entrevista em porto alegre */

#include <stdio.h>

int n_pessoas, n_POAcityoutrotime, n_gremistas, n_inter;
float m_salariogremio, m_salariointer;
char continua_entrevista;

int hold_time, hold_city;
float hold_salario;

 int main(){
    printf("Entrevista em porto alegre - exercicio\n");

    do { //Comeca a coletar dados
        hold_time = 0; //Reseta a variavel
        hold_salario = 0; //Reseta a variavel
        hold_city = 0; //Reseta a variavel

        printf("\nVoce deseja continuar a entrevista (S - Sim | N - Nao");
        scanf("%c", &continua_entrevista);
        n_pessoas++;

        printf("\nDigite o time do entrevistado: (1-Gremio | 2-Inter | 3-Outros");
        scanf("%d", &hold_time);

        printf("\nDigite a media salarial do entrevistado:");
        scanf("%f", &hold_salario);

        printf("\nDigite a cidade de origem do entrevistado (1-POA | 2- Outras:");
        scanf("%d", &hold_city);

        if(hold_time==1){ //Se o entrevistado for do gremio
            n_gremistas++;
            m_salariogremio = m_salariogremio + hold_salario; }

        if(hold_time==2){ //Se a pessoa for do inter
            n_inter++;
            m_salariointer = m_salariointer + hold_salario; }

        if(hold_city==1 || hold_time==3){
            n_POAcityoutrotime++; }

    } while (continua_entrevista=='s' || continua_entrevista=='S');




 return 0; } //Fim do programa
