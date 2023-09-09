#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTAS 5

struct Contas
{
    char nome[100];
    int num;
    float saldo;
};

int menu()
{
    int op;
    system("cls");
    printf("\n1)Adicionar nova conta");
    printf("\n2)Ler alguma conta");
    printf("\n3)Ordenar as contas");
    printf("\n4)Sair");
    printf("\nEscolha uma operacao: ");
    scanf("%d", &op);
    getchar();
    return op;
}

void criarArquivo(FILE *CONTAS)
{
    CONTAS = fopen("contas.txt", "w");
    if (CONTAS == NULL)
    {
        printf("\nNao foi possivel criar o arquivo");
    }
    else
        fclose(CONTAS);
}

int contaLinhas(FILE *CONTAS)
{
    if (CONTAS == NULL)
    {
        printf("\nArquivo nao existe!");
    }
    else
    {
        char c;
        int ct = 0;

        while (c != EOF)
        {
            c = fgetc(CONTAS);
            if (c == '\n')
                ct = ct + 1;
        }
        return ct;
    }
}

void adicionarConta(FILE *CONTAS, struct Contas conta[100], int i)
{
    int qtdContas = 0;

    CONTAS = fopen("contas.txt", "a+");

    if (CONTAS == NULL)
    {
        criarArquivo(CONTAS);
        CONTAS = fopen("contas.txt", "a+");
        if (CONTAS == NULL)
        {
            printf("\nNao foi possivel abrir o arquivo");
        }
    }

    qtdContas = contaLinhas(CONTAS) / 3;

    if (qtdContas < MAX_CONTAS)
    {
        printf("Digite o Nome: ");
        fgets(conta[i].nome, 99, stdin);

        printf("Digite o Numero(5 digitos): ");
        scanf("%5d", &conta[i].num);
        fflush(stdin);

        printf("Digite o Saldo: ");
        scanf("%f", &conta[i].saldo);
        getchar();

        fprintf(CONTAS, "%s", conta[i].nome);
        fprintf(CONTAS, "%d\n", conta[i].num);
        fprintf(CONTAS, "%.2f\n", conta[i].saldo);
    }
    else
    {
        printf("Maximo de contas atingido!\n");
        system("pause");
    }
    fclose(CONTAS);
}

int main()
{
    struct Contas conta[100];
    FILE *CONTAS;
    CONTAS = NULL;
    int op, i = 0;
    int ctExterno = 0;

    do
    {
        op = menu();

        switch (op)
        {

        case 1:
            adicionarConta(CONTAS, conta, i);
            i++;
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nOperacao invalida!\n");
            break;
        }
    } while (op != 4);

    return 0;
}