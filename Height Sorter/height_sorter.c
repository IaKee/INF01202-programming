//Ordenador de alturas de pessoas

#include <stdio.h>

int altura1, altura2, altura3;

void main(){
printf("Ordenador de altura das pessoas\n");

printf("Entre com o valores das 3 alturas: ");
scanf("%d", &altura1);
scanf("%d", &altura2);
scanf("%d", &altura3);

printf("\n\nAlturas em ordem crescente: ");

//Primeira altura em primeiro
if (altura1 > altura2 && altura2 > altura3){
    printf(" %d", altura3); }
if (altura1 > altura3 && altura3 > altura2){
    printf(" %d", altura2); }

if (altura2 > altura3 && altura3 > altura1){
    printf(" %d", altura1); }
if (altura2 > altura1 && altura1 > altura3){
    printf(" %d", altura3); }

if (altura3 > altura2 && altura2 > altura1){
    printf(" %d", altura1); }
if (altura3 > altura1 && altura1 > altura2){
    printf(" %d", altura2); }

//Segunda altura em segundo
if (altura1 > altura2 && altura2 > altura3){
    printf(" %d", altura2); }
if (altura1 > altura3 && altura3 > altura2){
    printf(" %d", altura3); }

if (altura2 > altura3 && altura3 > altura1){
    printf(" %d", altura3); }
if (altura2 > altura1 && altura1 > altura3){
    printf(" %d", altura1); }

if (altura3 > altura2 && altura2 > altura1){
    printf(" %d", altura2); }
if (altura3 > altura1 && altura1 > altura2){
    printf(" %d", altura1); }


//Maior altura por ultimo
if (altura1 > altura2 && altura2 > altura3){
    printf(" %d", altura1); }
if (altura1 > altura3 && altura3 > altura2){
    printf(" %d", altura1); }

if (altura2 > altura3 && altura3 > altura1){
    printf(" %d", altura2); }
if (altura2 > altura1 && altura1 > altura3){
    printf(" %d", altura2); }

if (altura3 > altura2 && altura2 > altura1){
    printf(" %d", altura3); }
if (altura3 > altura1 && altura1 > altura2){
    printf(" %d", altura3); }
return 0; }
