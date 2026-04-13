#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade;
} Item;

typedef enum {
    POR_NOME,
    POR_TIPO,
    POR_PRIORIDADE
} CriterioOrdenacao;

Item mochila[MAX];
int numItens = 0;
bool ordenadaPorNome = false;

// ---------------- FUNÇÕES ----------------

void exibirMenu() {
    printf("\n===== MOCHILA =====\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens\n");
    printf("5. Buscar item por nome\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

void inserirItem() {
    if (numItens >= MAX) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);

    printf("Tipo: ");
    scanf(" %[^\n]", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[numItens++] = novo;
    ordenadaPorNome = false;

    printf("Item adicionado!\n");
}

void listarItens() {
    printf("\n--- ITENS ---\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d. %s | %s | Qtd: %d | Prioridade: %d\n",
            i + 1,
            mochila[i].nome,
            mochila[i].tipo,
            mochila[i].quantidade,
            mochila[i].prioridade
        );
    }
}

void removerItem() {
    char nome[50];
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            printf("Item removido!\n");
            return;
        }
    }

    printf("Item não encontrado!\n");
}

int comparar(Item a, Item b, CriterioOrdenacao criterio) {
    if (criterio == POR_NOME)
        return strcmp(a.nome, b.nome);
    else if (criterio == POR_TIPO)
        return strcmp(a.tipo, b.tipo);
    else
        return b.prioridade - a.prioridade; // maior primeiro
}

void insertionSort(CriterioOrdenacao criterio) {
    int comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0 && comparar(mochila[j], chave, criterio) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }
        mochila[j + 1] = chave;
    }

    if (criterio == POR_NOME)
        ordenadaPorNome = true;
    else
        ordenadaPorNome = false;

    printf("Ordenação concluída! Comparações: %d\n", comparacoes);
}

void menuOrdenacao() {
    int op;
    printf("\n1. Nome\n2. Tipo\n3. Prioridade\nEscolha: ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            insertionSort(POR_NOME);
            break;
        case 2:
            insertionSort(POR_TIPO);
            break;
        case 3:
            insertionSort(POR_PRIORIDADE);
            break;
        default:
            printf("Opção inválida\n");
    }
}

void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("Ordene por nome primeiro!\n");
        return;
    }

    char nome[50];
    printf("Digite o nome: ");
    scanf(" %[^\n]", nome);

    int inicio = 0, fim = numItens - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) {
            printf("Encontrado: %s | %s | Qtd: %d | Prioridade: %d\n",
                mochila[meio].nome,
                mochila[meio].tipo,
                mochila[meio].quantidade,
                mochila[meio].prioridade
            );
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Item não encontrado!\n");
}

// ---------------- MAIN ----------------

int main() {
    int op;

    do {
        exibirMenu();
        scanf("%d", &op);

        switch (op) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
        }

    } while (op != 0);

    return 0;
}