#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VET 1000
#define MAX_STR 15
typedef struct _Cliente CLIENTE;


struct _Cliente
{
    int conta;
    char primNome[MAX_STR];
    char ultNome[MAX_STR];
    float saldo;
    int ativo;
};


int main(int argc, char* argv[])
{
    CLIENTE usuario[MAX_VET];
    FILE* arqPtr = fopen(argv[1], "wb");
    if(argc != 2)
    {
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Entrada correta: [%s] [ARQUIVO.dat]");
        exit(1);
    }

    void inicializa_clientes(CLIENTE[], int);
    inicializa_clientes(usuario, MAX_VET);
    
    fwrite(usuario, sizeof(CLIENTE), MAX_VET, arqPtr);

    printf("\nO arquivo [%s] foi inicializado com sucesso!", argv[1]);
    printf("\nAgora voce pode compilar e executar o codigo do arquivo [ProcessaDados.c] :)\n\n");

    fclose(arqPtr);
    
    return 0;
}

void inicializa_clientes(CLIENTE usuario[], int tamanho)
{
    for(int i=0; i<tamanho; i++)
    {
        usuario[i].conta = i+1;
        memset(usuario[i].primNome, '\0', MAX_STR);
        memset(usuario[i].ultNome, '\0', MAX_STR);
        usuario[i].saldo = 0.0;
        usuario[i].ativo = 0;
    }
}