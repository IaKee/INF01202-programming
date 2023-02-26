//Calculadora de medias

int valor1, valor2, valor3, quantosiguais;
float media;

int main(){
quantosiguais = 0; //valordefault

printf("Calculadora de medias\n");

printf("Entre com tres numeros inteiros: ");
scanf("%d", &valor1);
scanf("%d", &valor2);
scanf("%d", &valor3);

media = ((valor1+valor2+valor3)/3);

if(valor1 >= media){
    quantosiguais++; }

if(valor2 >= media){
    quantosiguais++; }

if(valor3 >= media){
    quantosiguais++; }

printf("Foram encontrados %d", quantosiguais);
printf(" valores acima do valor medio.\n");

return 0; }
