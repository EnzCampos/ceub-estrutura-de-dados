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
        printf("\nNao foi possivel abrir o arquivo");
        return;
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

void lerContas(struct Contas conta[], int numContas)
{
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "r");

    if (arquivoContas == NULL)
    {
        printf("\nArquivo nao existe ou nao foi possivel abrir!");
        return;
    }

    int i = 0;

    // Cabeçalho da tabela
    printf("%-10s%-20s%-10s\n", "Conta", "Nome", "Saldo");

    while (fscanf(arquivoContas, "%[^\n]\n%d\n%f\n", conta[i].nome, &conta[i].num, &conta[i].saldo) != EOF)
    {
        printf("%-10d%-20s%-10.2f\n", conta[i].num, conta[i].nome, conta[i].saldo);
        i++;
    }

    if (numContas <= 0)
    {
        printf("\nNenhum resultado encontrado no arquivo.\n");
    }

    fclose(arquivoContas);
}

void selectionSort(struct Contas conta[], int numContas)
{
    printf("\nIniciando Selection Sort\n");
    clock_t inicio = clock();
    int i, j, minIndex;
    struct Contas temp;

    // Para o selection sort, a quantidade de comparações será sempre a mesma, que é o somátorio de 1 até n-1, n sendo o número de contas nesse caso
    int comparacoes = numContas - 1; // Melhor caso
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

        if (minIndex != i)
        {
            temp = conta[minIndex];
            conta[minIndex] = conta[i];
            conta[i] = temp;

            movimentacoes++;
        }
    }

    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nSelection Sort");
    printf("\nTempo gasto: %.6f segundos", tempo_gasto);
    printf("\nComparacoes: %d", comparacoes);
    printf("\nMovimentacoes: %d\n", movimentacoes);
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
        }

        conta[j + 1] = chave;

        if (j + 1 != i) { // Verifica se houve movimentação
            movimentacoes++;
        }
    }

    // Correção para o melhor caso
    if (comparacoes == 0 && movimentacoes == 0) {
        comparacoes = numContas - 1;
    }

    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nInsertion Sort");
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
        selectionSort(conta, numContas);
    }
    else if (op == 4)
    {
        insertionSort(conta, numContas);
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
    srand(time(NULL));

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

        fprintf(arquivoContas, "%s\n%d\n%.2f\n", nomeConta, i, (float)(rand() % 1000));
    }

    fclose(arquivoContas);
}

void gerarMelhorCaso(int numContas)
{
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "w");
    srand(time(NULL));


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

        fprintf(arquivoContas, "%s\n%d\n%.2f\n", nomeConta, i, (float)(rand() % 1000));
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
    int *numeros = (int *)malloc(numContas * sizeof(int));

    // Preenche o vetor com os números de conta de 1 a numContas
    for (i = 0; i < numContas; i++)
    {
        numeros[i] = i + 1;
    }

    // Embaralha os números de conta
    for (i = numContas - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = numeros[i];
        numeros[i] = numeros[j];
        numeros[j] = temp;
    }

    for (i = 0; i < numContas; i++)
    {
        char nomeConta[100];
        sprintf(nomeConta, "Conta %d", numeros[i]);

        fprintf(arquivoContas, "%s\n%d\n%.2f\n", nomeConta, numeros[i], (float)(rand() % 1000));
    }

    fclose(arquivoContas);
}

void gerarDados(int numContas)
{
    int option;

    do
    {
        printf("\n1) Gerar melhor caso.");
        printf("\n2) Gerar caso medio aleatorio.");
        printf("\n3) Gerar pior caso.");

        printf("\nEscolha uma operacao: ");

        scanf("%d", &option);

        switch (option)
        {
        case 1:
            gerarMelhorCaso(numContas);
            break;

        case 2:
            gerarCasoMedioAleatorio(numContas);
            break;

        case 3:
            gerarPiorCaso(numContas);
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
    int opcaoArquivo;

    FILE *arquivoContas = fopen(NOME_ARQUIVO, "r");
    if (arquivoContas != NULL)
    {
        printf("\nArquivo existente encontrado.\n");
        printf("1) Continuar usando este arquivo.\n");
        printf("2) Recriar arquivo do zero.\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoArquivo);

        if (opcaoArquivo != 1 && opcaoArquivo != 2)
        {
            printf("\nOpcao invalida!\n");
            fclose(arquivoContas);
            return 0;
        }

        if (opcaoArquivo == 2)
        {
            printf("Informe a quantidade maxima de elementos: ");
            scanf("%d", &maxContas);
            fclose(arquivoContas);
            arquivoContas = fopen(NOME_ARQUIVO, "w");
            fclose(arquivoContas);
            printf("\nArquivo recriado.\n");
        }
        else
        {
            maxContas = contaLinhas(arquivoContas) / 3;
            printf("\nQuantidade maxima de elementos: %d\n", maxContas);
            fclose(arquivoContas);
        }
    }

    else
    {
        arquivoContas = fopen(NOME_ARQUIVO, "w");
        fclose(arquivoContas);
        printf("\nNovo arquivo criado.\n");

        do
        {
            printf("Informe a quantidade maxima de elementos: ");
            scanf("%d", &maxContas);

            if (maxContas <= 0)
            {
                printf("\nValor invalido!\n");
            }

        } while (maxContas <= 0);
    }

    struct Contas *conta = (struct Contas *)malloc(maxContas * sizeof(struct Contas)); 

    if (conta == NULL)
    {
        printf("\nErro ao alocar memoria para conta.\n");
        exit(1);
    }

    int numContas = 0;
    int op;

    if (opcaoArquivo == 2)
    {
        for (int i = 0; i < maxContas; i++)
        {
            *conta[i].nome = '\0';
            conta[i].num = 0;
            conta[i].saldo = 0;
        }
    }
    else
    {
        FILE *arquivoContas = fopen(NOME_ARQUIVO, "r");
        for (int i = 0; i < maxContas; i++)
        {
            fscanf(arquivoContas, "%[^\n]\n%d\n%f\n", conta[i].nome, &conta[i].num, &conta[i].saldo);

            if (conta[i].num != 0)
            {
                numContas++;
            }

            if (feof(arquivoContas))
            {
                break;
            }
        }
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
            lerContas(conta, numContas);
            break;

        case 3:
            ordenarContasArquivo(conta, numContas, op);
            break;

        case 4:
            ordenarContasArquivo(conta, numContas, op);
            break;

        case 5:
            gerarDados(maxContas);
            numContas = maxContas;
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
