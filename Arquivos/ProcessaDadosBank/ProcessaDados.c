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
    int ativo;
};

char menu();
void adicionar_registro(FILE*);


int main(int argc, char* argv[])
{
    CLIENTE usuario[MAX_VET];
    char opcao;
    char* arquivOrigem;
    FILE* arqPtr;

    if(argc != 2)
    {
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Entrada correta: [%s] [ARQUIVO.dat]");
        exit(1);
    }
    
    arquivOrigem = argv[1];
    arqPtr = fopen(arquivOrigem, "rb+");
    if(arqPtr == NULL)
    {
        fprintf(stderr, "Arquivo [%s] nao pode ser aberto para leitura.\n", arquivOrigem);
        fprintf(stderr, "Certifique-se de fornecer o caminho correto para o diretorio. EX: C:Users\\MyDocuments\\MyLocalPath\\Myfile.dat");
        exit(1);
    }
    
    do
    {
        opcao = menu();
        switch(opcao)
        {
            case '+': adicionar_registro(arqPtr);
            break;
            /*
            ----> A adicionar as novas opções <----
            */
        }

        rewind(arqPtr);

    }while(opcao != 'e');

    fclose(arqPtr);

    return 0;
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
            scanf(" %[^\n]", buffer);
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

void adicionar_registro(FILE* arqPtr)
{
    int numConta=0, cond=1, i, is_int=0, ctrl;
    CLIENTE clienteBuscado;
    char buffer[80];
    
    if(arqPtr == NULL)
    {
        fprintf(stderr,"\nAbertura do Arquivo \"[registros.dat]\" falhou!");
        fprintf(stderr,"\nPrograma encerrado.");
        exit(1);
    }

    while(cond)
    {
        do
        {
            printf("\nNumero da Conta (1-1000): ");
            scanf("%d", &numConta);
        }while(numConta < 0 || numConta > MAX_VET);
        printf("\nConta digitada: %d", numConta);
        
        fseek(arqPtr, (numConta-1)*sizeof(CLIENTE), SEEK_SET);
        int lido = fread(&clienteBuscado, sizeof(CLIENTE), 1, arqPtr);
        if(lido == 0)
        {
            fprintf(stderr, "Erro ao realizar leitura.");
            continue;
        }
        printf("\n%04d %s %s R$%.2f status: %d", clienteBuscado.conta, clienteBuscado.primNome, clienteBuscado.ultNome, clienteBuscado.saldo, clienteBuscado.ativo);
        printf("\nLido: %d", lido);

        if(clienteBuscado.ativo == 0)
        {
            int loopCtrl = 1, check;
            while(loopCtrl)
            {
                clienteBuscado.conta = numConta;
                printf("\nPrimeiro Nome: ");
                scanf(" %[^\n]", clienteBuscado.primNome);
                check = 1;
                
                for(int i=0; clienteBuscado.primNome[i]; i++)
                {
                    if(!(clienteBuscado.primNome[i] >= 'a' && clienteBuscado.primNome[i] <= 'z') && !(clienteBuscado.primNome[i] >= 'A' && clienteBuscado.primNome[i] <= 'Z'))
                    {
                        printf("\nSomente letras sao permitidas para este campo!");
                        memset(clienteBuscado.primNome, '\0', MAX_STR);
                        check = 0;
                        break;
                    }
                }
                if(check)
                    loopCtrl = 0;
            }
            char c = getchar(); //Tirar o '\n' do buffer
            
            loopCtrl = 1;
            while(loopCtrl)
            {
                printf("\nUltimo Nome: ");
                scanf(" %[^\n]", clienteBuscado.ultNome);
                check = 1;

                for(int i=0; clienteBuscado.ultNome[i]; i++)
                {
                    if(!(clienteBuscado.ultNome[i] >= 'a' && clienteBuscado.ultNome[i] <= 'z') && !(clienteBuscado.ultNome[i] >= 'A' && clienteBuscado.ultNome[i] <= 'Z'))
                    {
                        printf("\nSomente letras sao permitidas para este campo!");
                        memset(clienteBuscado.primNome, '\0', MAX_STR);
                        check = 0;
                        break;
                    }
                }
                if(check)
                    loopCtrl = 0;
            }


            memset(buffer, '\0', 80);
            loopCtrl = 1;
            int is_int;
            while(loopCtrl)
            {
                printf("\nSaldo: ");
                scanf(" %[^\n]", buffer);
                is_int = 1;
                for(i=0; buffer[i]; i++)
                {
                    if(!(buffer[i] >= '0' && buffer[i] <= '9') && (buffer[i] != '.'))
                    {
                        memset(buffer, '\0', 80);
                        printf("\nSomente numeros sao aceitos neste campo!");
                        is_int = 0;
                        break;
                    }
                }
                if(is_int)
                    loopCtrl = 0;
            }

            clienteBuscado.saldo = atof(buffer);
            clienteBuscado.ativo = 1;
        
            fseek(arqPtr, (numConta-1)*sizeof(CLIENTE), SEEK_SET);
            fwrite(&clienteBuscado, sizeof(CLIENTE), 1, arqPtr);
            printf("\nRegistro Adicionado com Sucesso!");
            cond = 0;
        }
        else
        {
            printf("\nRegistro ja existente!");
        }
        rewind(arqPtr);
    }

}