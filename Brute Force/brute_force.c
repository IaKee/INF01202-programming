/* Forca bruta em uma senha de ate 8 caracteres */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char caractere;
int n_char, n_chars, linha, aut;
char senha_desej[9], senha_encontrada[9]; //String que armazena a senha

static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "0123456789" "!@#$%¨&*()";
static const int alphabetSize = sizeof(alphabet) - 1;

void bruteImpl(char* str, int index, int maxDepth){
    for (int i = 0; i < alphabetSize; ++i){
        str[index] = alphabet[i];
        if (index == maxDepth - 1){
            senha_encontrada[9] = str;
            printf("%s\n", str); }
        else bruteImpl(str, index + 1, maxDepth); }}

void bruteSequential(int maxLen){
    char* buf = malloc(maxLen + 1);

    for (int i = 1; i <= maxLen; ++i){
        memset(buf, 0, maxLen + 1);
        bruteImpl(buf, 0, i);   }

    free(buf); }


int main(){
    printf("Faz forca bruta em uma senha de ate 8 caracteres\n\n");

    printf("Digite a senha de 8 digitos que voce deseja encontrar: ");
    scanf("%s", senha_desej);

    printf("\n\nA senha requerida eh: %s", senha_desej);
    printf("\nIniciar putaria (1-SIM | x - NOPE): ");
    scanf("%d", &aut);

    if(aut != 1){
        return 0; } //Finaliza o programa

    do { //Fica repetindo...
        bruteSequential(8);
        n_chars++;
    }while(senha_desej != senha_encontrada);

    printf("A senha solcitada foi encontrada depois desse n de passos: %d", n_chars);
return 0;}

//de 41 a 176
