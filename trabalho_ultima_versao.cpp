#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NOME_ARQUIVO "contas.txt"

struct Contas
{
    char nome[100];
    int num;
    float saldo;
};

int menu()
{
    int op;

    printf("\n1) Adicionar nova conta");
    printf("\n2) Ler alguma conta");
    printf("\n3) Ordenar as contas (Selection Sort)");
    printf("\n4) Ordenar as contas (Insertion Sort)");
    printf("\n5) Gerar dados para teste (Isso ira substituir o arquivo atual).");
    printf("\n6) Sair\n");
    printf("\nEscolha uma operacao: ");

    scanf("%d", &op);
    getchar();

    return op;
}

void criarArquivo()
{
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "w");
    if (arquivoContas == NULL)
    {
        printf("\nNao foi possivel criar o arquivo");
    }
    else
    {
        fclose(arquivoContas);
    }
}

int contaLinhas(FILE *arquivoContas)
{
    char c;
    int ct = 0;

    rewind(arquivoContas);

    while ((c = fgetc(arquivoContas)) != EOF)
    {
        if (c == '\n')
            ct = ct + 1;
    }

    return ct;
}

void adicionarConta(int maxContas)
{
    int qtdContas = 0;
    char nome[100];
    int num;
    float saldo;

    FILE *arquivoContas = fopen(NOME_ARQUIVO, "a+");
    if (arquivoContas == NULL)
    {
        criarArquivo();
        arquivoContas = fopen(NOME_ARQUIVO, "a+");
        if (arquivoContas == NULL)
        {
            printf("\nNao foi possivel abrir o arquivo");
            return;
        }
    }

    qtdContas = contaLinhas(arquivoContas) / 3;

    if (qtdContas < maxContas)
    {
        printf("Digite o Nome: ");
        fgets(nome, 99, stdin);

        printf("Digite o Numero(5 digitos): ");
        scanf("%5d", &num);
        fflush(stdin);

        printf("Digite o Saldo: ");
        scanf("%f", &saldo);
        getchar();

        fprintf(arquivoContas, "%s", nome);
        fprintf(arquivoContas, "%d\n", num);
        fprintf(arquivoContas, "%.2f\n", saldo);
    }
    else
    {
        printf("Maximo de contas atingido!\n");
    }

    fclose(arquivoContas);
}

void lerContas(struct Contas conta[], int *numContas)
{
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "r");

    if (arquivoContas == NULL)
    {
        printf("\nArquivo nao existe ou nao foi possivel abrir!");
        return;
    }

    int linha = 1;
    int i = 0;

    // Cabeçalho da tabela
    printf("%-10s%-20s%-10s%-10s\n", "Conta", "Nome", "Numero", "Saldo");

    while (fscanf(arquivoContas, "%[^\n]\n%d\n%f\n", conta[i].nome, &conta[i].num, &conta[i].saldo) != EOF)
    {
        printf("%-10d%-20s%-10d%-10.2f\n", linha, conta[i].nome, conta[i].num, conta[i].saldo);

        linha++;
        i++;
        (*numContas)++;
    }

    if (*numContas <= 0)
    {
        printf("\nNenhum resultado encontrado no arquivo.\n");
    }


    fclose(arquivoContas);
}

void insertionSort(struct Contas conta[], int numContas)
{
    printf("\nIniciando Insertion Sort\n");

    clock_t inicio = clock();
    int i, j;
    struct Contas chave;

    int comparacoes = 0;
    int movimentacoes = 0;

    for (i = 1; i < numContas; i++)
    {
        chave = conta[i];
        j = i - 1;

        while (j >= 0 && conta[j].num > chave.num)
        {
            conta[j + 1] = conta[j];
            j = j - 1;

            comparacoes++;
            movimentacoes++;
        }

        conta[j + 1] = chave;
        movimentacoes++;
    }

    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Insertion Sort");
    printf("\nTempo gasto: %.6f segundos", tempo_gasto);
    printf("\nComparacoes: %d", comparacoes);
    printf("\nMovimentacoes: %d\n", movimentacoes);
}

void selectionSort(struct Contas conta[], int numContas)
{
    printf("\nIniciando Selection Sort\n");
    clock_t inicio = clock();
    int i, j, minIndex;
    struct Contas temp;

    int comparacoes = 0;
    int movimentacoes = 0;

    for (i = 0; i < numContas - 1; i++)
    {
        minIndex = i;

        for (j = i + 1; j < numContas; j++)
        {
            if (conta[j].num < conta[minIndex].num)
            {
                minIndex = j;
            }

            comparacoes++;
        }

        temp = conta[minIndex];
        conta[minIndex] = conta[i];
        conta[i] = temp;

        movimentacoes++;
    }

    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Selection Sort");
    printf("\nTempo gasto: %.6f segundos", tempo_gasto);
    printf("\nComparacoes: %d", comparacoes);
    printf("\nMovimentacoes: %d\n", movimentacoes);
}

void ordenarContasArquivo(struct Contas conta[], int numContas, int op)
{
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "r+");

    if (arquivoContas == NULL)
    {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    int i;
    for (i = 0; i < numContas; i++)
    {
        fscanf(arquivoContas, "%[^\n]\n%d\n%f\n", conta[i].nome, &conta[i].num, &conta[i].saldo);
    }

    if (op == 3)
    {
        insertionSort(conta, numContas);
    }
    else if (op == 4)
    {
        selectionSort(conta, numContas);
    }

    rewind(arquivoContas);

    for (i = 0; i < numContas; i++)
    {
        fprintf(arquivoContas, "%s\n%d\n%.2f\n", conta[i].nome, conta[i].num, conta[i].saldo);
    }

    fclose(arquivoContas);
}

void gerarPiorCaso(int numContas)
{
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "w");

    if (arquivoContas == NULL)
    {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    int i;
    for (i = numContas; i > 0; i--)
    {
        char nomeConta[100];
        sprintf(nomeConta, "Conta %d", i);

        fprintf(arquivoContas, "%s\n%d\n%.2f\n", nomeConta, i, (float)i * 100);
    }

    fclose(arquivoContas);
}

void gerarMelhorCaso(int numContas)
{
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "w");

    if (arquivoContas == NULL)
    {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    int i;
    for (i = 1; i <= numContas; i++)
    {
        char nomeConta[100];
        sprintf(nomeConta, "Conta %d", i);

        fprintf(arquivoContas, "%s\n%d\n%.2f\n", nomeConta, i * 100, (float)i * 100);
    }

    fclose(arquivoContas);
}

void gerarCasoMedioAleatorio(int numContas)
{
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "w");

    if (arquivoContas == NULL)
    {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    srand(time(NULL));

    int i;
    for (i = 1; i <= numContas; i++)
    {
        char nomeConta[100];
        sprintf(nomeConta, "Conta %d", i);

        fprintf(arquivoContas, "%s\n%d\n%.2f\n", nomeConta, rand() % 1000 + 1, (float)(rand() % 1000));
    }

    fclose(arquivoContas);
}

void gerarDados(int numContas)
{
    int option;

    do
    {
        printf("\n1) Gerar pior caso.");
        printf("\n2) Gerar melhor caso.");
        printf("\n3) Gerar caso medio aleatorio.");

        printf("\nEscolha uma operacao: ");

        scanf("%d", &option);

        switch (option)
        {
        case 1:
            gerarPiorCaso(numContas);
            break;

        case 2:
            gerarMelhorCaso(numContas);
            break;

        case 3:
            gerarCasoMedioAleatorio(numContas);
            break;

        default:
            printf("\nOperacao invalida!\n");
            break;
        }

    } while (option != 1 && option != 2 && option != 3);
}

int main()
{
    int maxContas;

    do
    {
        printf("\nIniciando programa, por favor escolha a quantidade maxima de elementos: ");

        scanf("%d", &maxContas);

        if (maxContas <= 0)
        {
            printf("\nValor invalido!\n");
            return 0;
        }

    } while (maxContas <= 0);

    struct Contas *conta = (struct Contas *)malloc(maxContas * sizeof(struct Contas)); // Alocagem dinamica de memoria, para o tamanho maximo de contas que o usuario escolheu.

    if (conta == NULL)
    {
        printf("\nErro ao alocar memoria para conta.\n");
        exit(1);
    }

    int numContas = 0;
    int op;

    for (int i = 0; i < maxContas; i++)
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
            adicionarConta(maxContas);
            break;

        case 2:
            lerContas(conta, &numContas);
            break;

        case 3:
            ordenarContasArquivo(conta, numContas, op);
            break;

        case 4:
            ordenarContasArquivo(conta, numContas, op);
            break;

        case 5:
            gerarDados(maxContas);
            break;

        case 6:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nOperacao invalida!\n");
            break;
        }

    } while (op != 6);

    free(conta);
    return 0;
}
