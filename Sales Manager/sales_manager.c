//Pratica 7 - Exercicio 2
//Nome: Giordano Souza de Paula
//Cartao UFRGS: 00308054

#include <stdio.h>
//Valores padrao de L(lojas) e P(produtos)
#define L 3
#define P 4

int i, j, cod_solicitado, erro, qtd_vendas;
int cod_produto[P];
int vendas[L][P]; //Matriz de lojas x num. vendas

int main()
{
    printf("Pratica 7 - Exercicio 2 - Gestor de vendas\n\n\n");
    for(i=0; i<P; i++) //Incrementa de acordo com a qtd de produtos
    {
    printf("Informe o codigo do produto %d: ", i+1);
    scanf("%d", &cod_produto[i]);
    }
    printf("\n");
    for(j=0; j<L; j++)
    {
        for(i=0; i<P; i++) //Incrementa de acordo com a qtd de produtos
        {
        printf("Informe a quantidade vendida do produto %d na Loja %d: ", cod_produto[i], j+1);
        scanf("%d", &vendas[i][j]);
        }
        printf("\n");
    }

    //VALOR DEFAULT DE VARIAVEL
    erro = 0;

    while(erro==0)
    {
        qtd_vendas = 0;
        printf("\nInforme o codigo do produto desejado: ");
        scanf("%d", &cod_solicitado);
        for(j=0; j<L; j++)
        {
            for(i=0; i<P; i++)
            {
                if(cod_solicitado == cod_produto[i])
                {
                    qtd_vendas += vendas[i][j];
                }

            }
        }

        if(qtd_vendas==0)
                {
                    printf("\n\nVendas nulas ou produto invalido!");
                    erro = 1;
                }

        printf("\nTotal vendido do produto de codigo %d: %d", cod_solicitado, qtd_vendas);
    }

    printf("\nPor favor reinicie o programa...");
    return 0;
} //Fim do programa
