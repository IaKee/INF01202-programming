//Pratica 7 - Desafio

#include <stdio.h>
#include <string.h>

char cripto_in[27];
char cripto_out[27];
char holder[101];
char frase[101];
int i, j, k;

int main()
{
    printf("Pratica 7 - Teste de criptografia por substituicao\n\n\n");

    printf("Informe os caracteres que devem ser trocados: ");
    gets(cripto_in);
    printf("Informe os caracteres substituidos: ");
    gets(cripto_out);
    printf("Informe a frase que deve ser cifrada: ");
    gets(frase);

    j = strlen(frase);

    for(i=0; i<j; i++) //Roda o numero de caracteres da frase
    {
        for(k=0; k<27; k++)
        {
            if(frase[i] != cripto_in[k])
            {
                holder[i] = frase[i];
            }
            if(frase[i] == cripto_in[k])
            {
                holder[i] = cripto_out[k];
            }


        }
    }

    printf("A frase cifrada eh: ");
    puts(holder);
    printf("O comprimento da frase eh: %d", j);

    return 0;
}
