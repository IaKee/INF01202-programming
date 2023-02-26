//Calculadora de populacao media de ate 3 municipios

#include <stdio.h>

int idcity1, idcity2, idcity3;
int popula1, popula2, popula3;
float mediapopula;

int main(){

printf("Calculadora de pupulacao media\n");

printf("Informe o identificador e a populacao do primeiro municipio:");
scanf("%d", &idcity1);
scanf("%d", &popula1);

printf("Informe o identificador e a populacao do segundo municipio:");
scanf("%d", &idcity2);
scanf("%d", &popula2);

printf("Informe o identificador e a populacao do terceiro municipio:");
scanf("%d", &idcity3);
scanf("%d", &popula3);

mediapopula = ((popula1 + popula2 + popula3)/3.0);
printf("\nA media da populacao eh: %f", mediapopula);

printf("\nMunicipios com a populacao maior ou igual a media: ");

if(popula1 >= mediapopula){
    printf(" %d", idcity1); }
if(popula2 >= mediapopula){
    printf(" %d", idcity2); }
if(popula3 >= mediapopula){
    printf(" %d", idcity3); }

printf("\nMunicipios com a populacao menor do que a media: ");

if(popula1 < mediapopula){
    printf(" %d", idcity1); }
if(popula2 < mediapopula){
    printf(" %d", idcity2); }
if(popula3 < mediapopula){
    printf(" %d", idcity3); }

return 0; }//Fim do programa
