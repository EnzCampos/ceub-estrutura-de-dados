#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTAS 5 // Tamanho do array de structs.

struct Contas
{
    char nome[100];
    int num;
    float saldo;
};

int menu()
{
    int op;
    system("cls"); // O system cleanse retarda a inicializacao do programa, entao quando for testar, comente essa linha.
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
    CONTAS = fopen("contas.txt", "w");
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

// Funcao adicionarContas nao armazena as contas adicionadas dentro do struct, apenas dentro do arquivo.
void adicionarConta(FILE *CONTAS)
{
    int qtdContas = 0;
    char nome[100];
    int num;
    float saldo;

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
 nao vai haver espaco no struct para armazenar as informacoes. */
void lerContas(FILE *CONTAS, struct Contas conta[])
{
    CONTAS = fopen("contas.txt", "r");

    if (CONTAS == NULL)
    {
        printf("\nArquivo nao existe ou nao foi possivel abrir!");
        return;
    }

    int linha = 1;
    int i = 0;

    // Modificado na intencao de auxiliar os algoritmos sort.
    while (fscanf(CONTAS, "%[^\n]\n%d\n%f\n", conta[i].nome, &conta[i].num, &conta[i].saldo) != EOF)
    {
        printf("\nConta %d:\n", linha);
        printf("\nNome: %s\n", conta[i].nome);
        printf("Numero: %d\n", conta[i].num);
        printf("Saldo: %.2f\n", conta[i].saldo);
        system("pause");
        linha++;
        i++;
    }

    fclose(CONTAS);
}

int main()
{
    struct Contas conta[MAX_CONTAS];
    FILE *CONTAS;
    CONTAS = NULL;
    int op, i = 0;

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

        case 6: // Caso criado para teste. Nao permanecera no codigo final(talvez).
            for (int i = 0; i < 6; i++)
            {
                printf("\n%s", conta[i].nome);
                printf("\n%d", conta[i].num);
                printf("\n%f", conta[i].saldo);
                system("pause");
            }
            system("pause");
            break;

        default:
            printf("\nOperacao invalida!\n");
            break;
        }
    } while (op != 5);

    return 0;
}