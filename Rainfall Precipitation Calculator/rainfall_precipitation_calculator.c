/* Calculadora de media de precipitacao de chuvas

Entradas: Identificadores de precipitacao de chuvas (em mm), Codigo dos municipios
Saídas: Precipitacao media nos municipios (calculo), comparacao do valor entrado ao valor esperado (105mm) */

#include <stdio.h>

int precip1, precip2, precip3, precipmedia; //Segura o valor respectivo a precipitacao
int city1, city2, city3; //Segura o codigo dos municipios
int valoresperado;

int main(){

printf("Calculadora de media de precipitacao de chuvas em municipios \n");

printf("Por favor, entre com o codigo dos municipios no seguinte formato - xxx yyy zzz \n");
scanf("%d", &city1);
scanf("%d", &city2);
scanf("%d", &city3);

printf("Agora entre com os valores (em mm) da precipitacao nos municipios no formato \n");
scanf("%d", &precip1);
scanf("%d", &precip2);
scanf("%d", &precip3);

precipmedia = ((precip1+precip2+precip3)/3);
valoresperado = 105;

printf("A precipitacao media nas tres cidades foi de: %d\n", precipmedia);

if(precip1 > valoresperado){
    printf("O municipio de codigo:  %d", city1);
    printf(" teve precipitacao mensal superior ao esperado. \n"); }

if(precip1 > (2*valoresperado)){
    printf("O municipio de codigo:  %d", city1);
    printf(" teve a precipitacao mensal muito alta. \n"); }

if(precip1 == valoresperado){
    printf("O municipio de codigo:  %d", city1);
    printf(" teve precipitacao mensal igual ao esperado. \n"); }

if(precip1 < valoresperado){
    printf("O municipio de codigo:  %d", city1);
    printf(" teve precipitacao mensal abaixo do esperado. \n"); }

if(precip2 > valoresperado){
    printf("O municipio de codigo:  %d", city2);
    printf(" teve precipitacao mensal superior ao esperado. \n"); }

if(precip2 > (2*valoresperado)){
    printf("O municipio de codigo:  %d", city2);
    printf(" teve a precipitacao mensal muito alta. \n"); }

if(precip2 == valoresperado){
    printf("O municipio de codigo:  %d", city2);
    printf(" teve precipitacao mensal igual ao esperado. \n"); }

if(precip2 < valoresperado){
    printf("O municipio de codigo:  %d", city2);
    printf(" teve precipitacao mensal abaixo do esperado. \n"); }

if(precip3 > valoresperado){
    printf("O municipio de codigo:  %d", city3);
    printf(" teve precipitacao mensal superior ao esperado. \n"); }

if(precip3 > (2*valoresperado)){
    printf("O municipio de codigo:  %d", city3);
    printf(" teve a precipitacao mensal muito alta. \n"); }

if(precip3 == valoresperado){
    printf("O municipio de codigo:  %d", city3);
    printf(" teve precipitacao mensal igual ao esperado. \n"); }

if(precip3 < valoresperado){
    printf("O municipio de codigo:  %d", city3);
    printf(" teve precipitacao mensal abaixo do esperado. \n"); }

   return 0; }
