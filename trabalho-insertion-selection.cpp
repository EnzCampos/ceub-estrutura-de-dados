#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NOME_ARQUIVO "contas.txt"

struct Contas /*Registro com as informaçoes da conta*/
{
    char nome[100];
    int num;
    float saldo;
};

int menu() /*Essa é a função do menu que será inicializada todas as vezes  após o fim de alguma das opções presente nele*/ 
{
    int op;

    printf("\n1) Adicionar nova conta");
    printf("\n2) Ler todas as contas");
    printf("\n3) Ordenar as contas (Selection Sort)");
    printf("\n4) Ordenar as contas (Insertion Sort)");
    printf("\n5) Gerar dados para teste (Isso ira substituir o arquivo atual).");
    printf("\n6) Sair\n");
    printf("\nEscolha uma operacao: ");

    scanf("%d", &op);
    getchar();

    return op;
}

// Esta função conta o número de linhas em um arquivo, assumindo que cada linha é terminada por um caractere de nova linha ('\n').
// Ela utiliza um ponteiro de arquivo (arquivoContas) para realizar essa contagem.
int contaLinhas(FILE *arquivoContas)
{
    char c;
    int ct = 0;

    // Volta para o início do arquivo.
    rewind(arquivoContas);

    // Lê o arquivo caractere por caractere até atingir o final do arquivo (EOF).
    while ((c = fgetc(arquivoContas)) != EOF)
    {
        // Se o caractere lido for uma nova linha ('\n'), incrementa o contador.
        if (c == '\n')
            ct = ct + 1;
    }

    // Retorna o número total de linhas contadas.
    return ct;
}


// Esta função permite adicionar uma nova conta bancária ao arquivo de contas, desde que o número máximo de contas (maxContas) não tenha sido atingido.
// Ela recebe o número máximo de contas como argumento e permite ao usuário inserir os detalhes da conta.
void adicionarConta(int maxContas)
{
    int qtdContas = 0;
    char nome[100];
    int num;
    float saldo;

    // Abre o arquivo "NOME_ARQUIVO" para leitura e escrita (adiciona ao final do arquivo se já existir).
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "a+");

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivoContas == NULL)
    {
        printf("\nNão foi possível abrir o arquivo");
        return;
    }

    // Calcula a quantidade atual de contas no arquivo dividindo o número de linhas por 3 (cada conta tem 3 linhas).
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

        // Escreve os detalhes da conta no arquivo.
        fprintf(arquivoContas, "%s", nome);
        fprintf(arquivoContas, "%d\n", num);
        fprintf(arquivoContas, "%.2f\n", saldo);
    }
    else
    {
        printf("Máximo de contas atingido!\n");
    }

    // Fecha o arquivo após a escrita.
    fclose(arquivoContas);
}

// Esta função lê todas as contas do arquivo e as exibe em uma tabela.
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
    //  Ele cria três colunas, cada uma com um espaço de largura específico (10, 20 e 10).
    printf("%-10s%-20s%-10s\n", "N. Conta", "Nome", "Saldo");

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

// Esta função implementa o algoritmo de ordenação Selection Sort para ordenar o vetor de contas bancárias com base no saldo da conta.
void selectionSort(struct Contas conta[], int numContas)
{
    printf("\nIniciando Selection Sort\n");

    clock_t inicio = clock();

    int i, j, minIndex;
    struct Contas temp;

    long int comparacoes = numContas - 1;
    long int movimentacoes = 0;
    long int comparacoesEmMilhoes = 0;
    long int movimentacoesEmMilhoes = 0;

    for (i = 0; i < numContas - 1; i++) // Loop externo percorrendo o array.
    {
        minIndex = i; // Assume que o menor elemento é o primeiro.

        for (j = i + 1; j < numContas; j++) // Loop interno a partir do próximo elemento.
        {
            if (conta[j].num < conta[minIndex].num) // Compara o número da conta.
            {
                minIndex = j; // Atualiza o índice do menor elemento.
            }

            comparacoes++; // Incrementa o contador de comparações.
        }

        if (minIndex != i) // Se o menor elemento não é o atual.
        {
            temp = conta[minIndex]; // Realiza a troca usando variável temporária.
            conta[minIndex] = conta[i];
            conta[i] = temp;

            movimentacoes++; // Incrementa o contador de movimentações.
        }

        if (comparacoes > 1000000) {
            comparacoesEmMilhoes++;
            comparacoes -= 1000000;
        }
        if (movimentacoes > 1000000) {
            movimentacoesEmMilhoes++;
            movimentacoes -= 1000000;
        }
    }

    clock_t fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nSelection Sort");
    printf("\nTempo gasto: %.6f segundos", tempo_gasto);
    if (comparacoesEmMilhoes > 0) {
        printf("\nComparacoes: %lu milhoes", comparacoesEmMilhoes);
    } else {
        printf("\nComparacoes: %lu", comparacoes);
    }
    if (movimentacoesEmMilhoes > 0) {
        printf("\nMovimentacoes: %lu milhoes", movimentacoesEmMilhoes);
    } else {
        printf("\nMovimentacoes: %ld", movimentacoes);
    }
}

// Esta função implementa o algoritmo de ordenação Insertion Sort para ordenar um array de contas bancárias com base nos números de conta.
void insertionSort(struct Contas conta[], int numContas)
{
    // Iniciando a ordenação
    printf("\nIniciando Insertion Sort\n");

    clock_t inicio = clock();  // Marca o início do tempo de execução
    int i, j;
    struct Contas chave;

    long int comparacoes = 0;
    long int movimentacoes = 0;

    long int comparacoesEmMilhoes = 0;
    long int movimentacoesEmMilhoes = 0;

    for (i = 1; i < numContas; i++)
    {
        chave = conta[i];
        j = i - 1;

        // Move os elementos do array que são maiores que a chave para uma posição à frente de sua posição atual
        while (j >= 0 && conta[j].saldo > chave.saldo)
        {
            conta[j + 1] = conta[j];
            j = j - 1;

            comparacoes++;
        }

        conta[j + 1] = chave; // Insere a chave na posição correta

        if (j + 1 != i) {
            movimentacoes++;
        }

        // Verifica se as comparações ou movimentações ultrapassaram 1 milhão
        if (comparacoes > 1000000) {
            comparacoesEmMilhoes++;
            comparacoes -= 1000000;  // Subtrai 1 milhão para manter o valor correto
        }
        if (movimentacoes > 1000000) {
            movimentacoesEmMilhoes++;
            movimentacoes -= 1000000;  // Subtrai 1 milhão para manter o valor correto
        }
    }

    // Para o melhor caso, o número de movimentações é 0 e o número de comparações é n - 1
    if (comparacoes == 0 && movimentacoes == 0) {
        comparacoes = numContas - 1; 
    }

    clock_t fim = clock();  // Marca o fim do tempo de execução
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;

    // Exibindo informações sobre a ordenação
    printf("\nInsertion Sort");
    printf("\nTempo gasto: %.6f segundos", tempo_gasto);
    if (comparacoesEmMilhoes > 0) {
        printf("\nComparacoes: %lu milhoes", comparacoesEmMilhoes);
    } else {
        printf("\nComparacoes: %lu", comparacoes);
    }
    if (movimentacoesEmMilhoes > 0) {
        printf("\nMovimentacoes: %lu milhoes\n", movimentacoesEmMilhoes);
    } else {
        printf("\nMovimentacoes: %ld\n", movimentacoes);
    }
}

// Esta função recebe um array de estruturas "Contas", o número de contas no array e uma opção (op) que determina o tipo de ordenação a ser aplicada ao array.
void ordenarContasArquivo(struct Contas conta[], int numContas, int op)
{
    // Abre o arquivo "NOME_ARQUIVO" para leitura e escrita.
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "r+");

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivoContas == NULL)
    {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    int i;

    // Lê os dados do arquivo para o array de estruturas "conta".
    for (i = 0; i < numContas; i++)
    {
        fscanf(arquivoContas, "%[^\n]\n%d\n%f\n", conta[i].nome, &conta[i].num, &conta[i].saldo);
    }

    // Verifica a opção de ordenação escolhida.
    if (op == 3)
    {
        // Chama a função selectionSort para ordenar o array de estruturas "conta" com base no saldo.
        selectionSort(conta, numContas);
    }
    else if (op == 4)
    {
        // Chama a função insertionSort para ordenar o array de estruturas "conta" com base no saldo.
        insertionSort(conta, numContas);
    }

    // Volta para o início do arquivo.
    rewind(arquivoContas);

    // Escreve os dados ordenados de volta para o arquivo.
    for (i = 0; i < numContas; i++)
    {
        fprintf(arquivoContas, "%s\n%d\n%.2f\n", conta[i].nome, conta[i].num, conta[i].saldo);
    }

    // Fecha o arquivo.
    fclose(arquivoContas);
}


// Esta função gera um conjunto de dados no formato de contas bancárias que representa o "pior caso".
// No pior caso, os dados são gerados de forma ordenada em ordem decrescente de números de conta.
void gerarPiorCaso(int numContas)
{
    // Abre o arquivo "NOME_ARQUIVO" para escrita (sobrescreve o arquivo se já existir).
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "w");

    // Inicializa a semente do gerador de números aleatórios com base no tempo atual.
    srand(time(NULL));

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivoContas == NULL)
    {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    int i;
    for (i = numContas; i > 0; i--)
    {
        char nomeConta[100];
        sprintf(nomeConta, "Conta %d", i + 1);

        // Gera números de conta aleatorios e saldos decrescentes.
        fprintf(arquivoContas, "%s\n%d\n%.2f\n", nomeConta, ((rand() % 5000) + 1), (float)i * 100);
    }

    // Fecha o arquivo após a escrita.
    fclose(arquivoContas);
}


// Esta função gera um conjunto de dados no formato de contas bancárias que representa o "melhor caso".
// No melhor caso, os dados são gerados de forma ordenada, com números de conta sequenciais.
void gerarMelhorCaso(int numContas)
{
    // Abre o arquivo "NOME_ARQUIVO" para escrita (sobrescreve o arquivo se já existir).
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "w");

    // Inicializa a semente do gerador de números aleatórios com base no tempo atual.
    srand(time(NULL));

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivoContas == NULL)
    {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    int i;
    for (i = 1; i <= numContas; i++)
    {
        char nomeConta[100];
        sprintf(nomeConta, "Conta %d", i + 1);

        // Gera números de aleátorios e saldos crescentes.
        fprintf(arquivoContas, "%s\n%d\n%.2f\n", nomeConta, ((rand() % 5000) + 1), (float)i * 100);
    }

    // Fecha o arquivo após a escrita.
    fclose(arquivoContas);
}

// Esta função gera um conjunto de dados no formato de contas bancárias de forma aleatória no que é considerado um "caso médio".
void gerarCasoMedioAleatorio(int numContas)
{
    // Abre o arquivo "NOME_ARQUIVO" para escrita (sobrescreve o arquivo se já existir).
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "w");

    // Verifica se o arquivo foi aberto corretamente.
    if (arquivoContas == NULL)
    {
        printf("\nErro ao abrir o arquivo!");
        return;
    }

    // Inicializa a semente do gerador de números aleatórios com base no tempo atual.
    srand(time(NULL));

    int i;
    int *numeros = (int *)malloc(numContas * sizeof(int));

    // Preenche um vetor com os números de conta aleatórios entre 1 e 5000.
    for (i = 0; i < numContas; i++)
    {
        numeros[i] = rand() % 5000 + 1;
    }

    // Embaralha os números de conta aleatoriamente.
    for (i = numContas - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = numeros[i];
        numeros[i] = numeros[j];
        numeros[j] = temp;
    }

    // Gera dados aleatórios de contas bancárias e escreve no arquivo.
    for (i = 0; i < numContas; i++)
    {
        char nomeConta[100];
        sprintf(nomeConta, "Conta %d", i + 1); // Gera nomes de conta com base nos números de conta.

        // Gera saldos aleatórios entre 1 e 5000.
        float saldo = (float)(rand() % 5000 + 1);

        // Escreve os dados no arquivo.
        fprintf(arquivoContas, "%s\n%d\n%.2f\n", nomeConta, numeros[i], saldo);
    }

    // Fecha o arquivo após a escrita.
    fclose(arquivoContas);

    // Libera a memória alocada para o array de números.
    free(numeros);
}

// Esta função gera dados com base nas escolhas do usuário para gerar um melhor caso, caso médio aleatório ou pior caso.
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
            // Chama a função gerarMelhorCaso para gerar dados no melhor caso.
            gerarMelhorCaso(numContas);
            break;

        case 2:
            // Chama a função gerarCasoMedioAleatorio para gerar dados no caso médio aleatório.
            gerarCasoMedioAleatorio(numContas);
            break;

        case 3:
            // Chama a função gerarPiorCaso para gerar dados no pior caso.
            gerarPiorCaso(numContas);
            break;

        default:
            printf("\nOperação invalida!\n");
            break;
        }

    } while (option != 1 && option != 2 && option != 3);
}

// Função principal do programa que controla a interação com o usuário e as operações relacionadas às contas bancárias.
int main()
{
    int maxContas;
    int opcaoArquivo;

    // Verifica se o arquivo de contas já existe.
    FILE *arquivoContas = fopen(NOME_ARQUIVO, "r");

    if (arquivoContas != NULL)
    {
        recomeco:
        printf("\nArquivo existente encontrado.\n");
        printf("1) Continuar usando este arquivo.\n");
        printf("2) Recriar arquivo do zero.\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoArquivo);

        if (opcaoArquivo != 1 && opcaoArquivo != 2)
        {
            printf("\nOpcao invalida!\n\n");
            fclose(arquivoContas);
            goto recomeco;
        }

        if (opcaoArquivo == 2)
        {
            printf("Informe a quantidade maxima de contas: ");
            scanf("%d", &maxContas);
            fclose(arquivoContas);

            // Cria um novo arquivo vazio.
            arquivoContas = fopen(NOME_ARQUIVO, "w");
            fclose(arquivoContas);
            printf("\nArquivo recriado.\n");
        }
        else
        {
            // Recupera a quantidade máxima de contas do arquivo.
            maxContas = contaLinhas(arquivoContas) / 3;
            printf("\nQuantidade maxima de contas: %d\n", maxContas);
            fclose(arquivoContas);
        }
    }
    else
    {
        // Se o arquivo não existe, cria um novo arquivo vazio.
        arquivoContas = fopen(NOME_ARQUIVO, "w");
        fclose(arquivoContas);
        printf("\nNovo arquivo criado.\n");

        do
        {
            // Solicita ao usuário a quantidade máxima de elementos no arquivo.
            printf("Informe a quantidade maxima de contas: ");
            scanf("%d", &maxContas);

            if (maxContas <= 0)
            {
                printf("\nValor invalido!\n");
            }

        } while (maxContas <= 0);
    }

    // Aloca memória para o array de contas, é necessario pois não temos um tamanho fixo do vetor.
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
        // Inicializa o array de contas se um novo arquivo foi criado.
        for (int i = 0; i < maxContas; i++)
        {
            *conta[i].nome = '\0';
            conta[i].num = 0;
            conta[i].saldo = 0;
        }
    }
    else
    {
        // Lê as contas do arquivo existente.
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
        // Apresenta um menu e obtém a escolha do usuário.
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

    free(conta); // Libera a memória alocada para o array de contas.
    return 0;
}
