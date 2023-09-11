#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTAS 10 // Tamanho do array de structs.
#define NOME_ARQUIVO "contas.txt" // Nome do arquivo.

struct Contas
{
    char nome[100];
    int num;
    float saldo;
};

int menu()
{
    int op;

    printf("\n1)Adicionar nova conta");
    printf("\n2)Ler alguma conta");
    printf("\n3)Ordenar as contas (Selection Sort)");
    printf("\n4)Ordenar as contas (Insertion Sort)");
    printf("\n5)Sair");
    printf("\nEscolha uma operacao: ");

    scanf("%d", &op);
    getchar();

    return op;
}

void criarArquivo(FILE *CONTAS)
{
    CONTAS = fopen(NOME_ARQUIVO, "w");
    if (CONTAS == NULL)
    {
        printf("\nNao foi possivel criar o arquivo");
    }
    else
        fclose(CONTAS);
}

// Retorna a quantidade de linhas em um arquivo.
int contaLinhas(FILE *CONTAS)
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

// Funcao adicionarContas nao armazena as contas adicionadas dentro do struct, apenas dentro do arquivo.
void adicionarConta(FILE *CONTAS)
{
    int qtdContas = 0;
    char nome[100];
    int num;
    float saldo;

    CONTAS = fopen(NOME_ARQUIVO, "a+");

    if (CONTAS == NULL)
    {
        criarArquivo(CONTAS);
        CONTAS = fopen(NOME_ARQUIVO, "a+");
        if (CONTAS == NULL)
        {
            printf("\nNao foi possivel abrir o arquivo");
            return;
        }
    }

    qtdContas = contaLinhas(CONTAS) / 3;

    if (qtdContas < MAX_CONTAS)
    {
        printf("Digite o Nome: ");
        fgets(nome, 99, stdin);

        printf("Digite o Numero(5 digitos): ");
        scanf("%5d", &num);
        fflush(stdin);

        printf("Digite o Saldo: ");
        scanf("%f", &saldo);
        getchar();

        fprintf(CONTAS, "%s", nome);
        fprintf(CONTAS, "%d\n", num);
        fprintf(CONTAS, "%.2f\n", saldo);
    }
    else
    {
        printf("Maximo de contas atingido!\n");
        system("pause");
    }
    
    fclose(CONTAS);
}

/* Se o numero de contas em um arquivo ja existente for maior que o valor de MAX_CONTAS
 não vai haver espaco no struct para armazenar as informacoes. */
void lerContas(FILE *CONTAS, struct Contas conta[])
{
    CONTAS = fopen(NOME_ARQUIVO, "r");

    if (CONTAS == NULL)
    {
        printf("\nArquivo nao existe ou nao foi possivel abrir!");
        return;
    }

    int linha = 1; 
    int i = 0;
    int resultados = 0;

    while (fscanf(CONTAS, "%[^\n]\n%d\n%f\n", conta[i].nome, &conta[i].num, &conta[i].saldo) != EOF)
    {
        printf("\nConta %d:\n", linha);
        printf("\nNome: %s\n", conta[i].nome);
        printf("\nNumero: %d\n", conta[i].num);
        printf("\nSaldo: %.2f\n", conta[i].saldo);

        system("pause");

        linha++;
        i++;
        resultados++;
    }

    if (resultados <= 0)
    {
        printf("\nNenhum resultado encontrado no arquivo.\n");
    }

    fclose(CONTAS);
}

int main()
{
    struct Contas conta[MAX_CONTAS];
    FILE *CONTAS;
    CONTAS = NULL;
    int op;

    for (int i = 0; i < MAX_CONTAS; i++)
    {
        *conta[i].nome = '\0';
        conta[i].num = 0;
        conta[i].saldo = 0;
    }

    do
    {
        op = menu();

        switch (op)
        {

            case 1:
                adicionarConta(CONTAS);
                break;

            case 2:
                lerContas(CONTAS, conta);
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOperacao invalida!\n");
                break;
        }

    } while (op != 5);

    return 0;
}