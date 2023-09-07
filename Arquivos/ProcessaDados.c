/*****************************
*
*       AINDA TRABALHANDO
*
******************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_VET 1000
#define MAX_STR 15
typedef struct _Cliente CLIENTE;


struct _Cliente
{
    int conta;
    char primNome[MAX_STR];
    char ultNome[MAX_STR];
    float saldo;
};


void inicializa_clientes(CLIENTE[], int);
char menu();



int main()
{
    CLIENTE usuario[MAX_VET];
    char opcao;
    //char ctrl;
    inicializa_clientes(usuario, MAX_VET);

    do
    {
        opcao = menu();
        printf("\nOpcao escolhida: %c", opcao);



    }while(opcao != 'e');




    /*--só pra testar o loop-----
    for(int i=0; i<MAX_VET; i++)
    {
        printf("\n%d: %d", usuario[i].conta, i+1);
    }
    */

    return 0;
}

void inicializa_clientes(CLIENTE usuario[], int tamanho)
{
    for(int i=0; i<tamanho; i++)
    {
        usuario[i].conta = 0;
        memset(usuario[i].primNome, '\0', MAX_STR);
        memset(usuario[i].ultNome, '\0', MAX_STR);
        usuario[i].saldo = 0.0;
    }
}

char menu()
{
    char op;
    char buffer[80];
    int cond = 1;

    do
    {
            memset(buffer, '\0', 80);
            printf("\n----------REGISTROS---------");
            printf("\n%-15s%-15s\n%-15s%-15s\n%-15s", "(+)Adicionar", "(-)Excluir", "(a)Atualizar", "(i)Imprimir", "(e)Encerrar");
            printf("Opcao: ( )\b\b");
            //fgets(buffer, 80, stdin); Por alguma razão que eu não sei(erro meu, talvez??), o código não funciona com fgets() nesse cenário.
            scanf(" %[^\n]", buffer);
            printf("%s", buffer);
            if(strlen(buffer) == 1)
            {
                if(buffer[0] >= 'A' && buffer[0] <= 'Z')
                    buffer[0] = tolower(buffer[0]);
                
                if(buffer[0] == 'a' || buffer[0] == 'e' || buffer[0] == 'i' || buffer[0] == '+' || buffer[0] == '-')
                {
                    op = buffer[0];
                    cond = 0;
                }
            }
    } while(cond);
    
    return op;
}