#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

static void lerTextoObrigatorio(const char *mensagem, char destino[], size_t tamanho) {
    for (;;) {
        printf("%s", mensagem);

        if (fgets(destino, (int)tamanho, stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }

        char *quebra = strpbrk(destino, "\r\n");
        if (quebra != NULL) {
            *quebra = '\0';
        } else {
            int caractere;
            while ((caractere = getchar()) != '\n' && caractere != EOF) {
                /* Descarta os caracteres que excederam o tamanho do campo. */
            }
            printf("Texto muito longo. Tente novamente.\n");
            continue;
        }

        if (destino[0] == '\0') {
            printf("O campo nao pode ficar vazio.\n");
            continue;
        }

        if (strchr(destino, ';') != NULL) {
            printf("Nao use ponto e virgula (;) no texto.\n");
            continue;
        }

        return;
    }
}

static double lerNumero(const char *mensagem, int permiteZero) {
    char linha[128];

    for (;;) {
        char *fim;
        double valor;

        printf("%s", mensagem);
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }

        if (strchr(linha, '\n') == NULL && !feof(stdin)) {
            int caractere;
            while ((caractere = getchar()) != '\n' && caractere != EOF) {
                /* Descarta entrada numerica muito longa. */
            }
            printf("Entrada muito longa. Tente novamente.\n");
            continue;
        }

        valor = strtod(linha, &fim);
        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim == linha || *fim != '\0' || !isfinite(valor) ||
            (permiteZero ? valor < 0.0 : valor <= 0.0)) {
            if (permiteZero) {
                printf("Digite um numero valido maior ou igual a zero.\n");
            } else {
                printf("Digite um numero valido maior que zero.\n");
            }
            continue;
        }

        return valor;
    }
}

int cadastrarAtivo(Ativo carteira[], int *total, int capacidade) {
    Ativo novo;

    if (*total >= capacidade) {
        printf("A carteira atingiu o limite de %d ativos.\n", capacidade);
        return 0;
    }

    printf("\n--- Cadastro de ativo ---\n");
    lerTextoObrigatorio("Nome do ativo: ", novo.nome, sizeof(novo.nome));
    lerTextoObrigatorio("Categoria: ", novo.categoria, sizeof(novo.categoria));
    novo.quantidade = lerNumero("Quantidade (maior que zero): ", 0);
    novo.precoCompra = lerNumero("Preco de compra por unidade (maior que zero): R$ ", 0);
    novo.precoAtual = lerNumero("Preco atual por unidade (maior ou igual a zero): R$ ", 1);

    carteira[*total] = novo;
    (*total)++;

    printf("Ativo cadastrado com sucesso.\n");
    return 1;
}

void listarAtivos(const Ativo carteira[], int total) {
    if (total == 0) {
        printf("\nA carteira esta vazia.\n");
        return;
    }

    printf("\n--- Ativos da carteira ---\n");
    printf("%-3s %-30s %-20s %12s %16s %16s %16s\n",
           "N", "Nome", "Categoria", "Quantidade", "Preco compra", "Preco atual", "Valor atual");
    printf("--------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        double valorAtual = carteira[i].quantidade * carteira[i].precoAtual;
        printf("%-3d %-30.30s %-20.20s %12.4f %16.2f %16.2f %16.2f\n",
               i + 1,
               carteira[i].nome,
               carteira[i].categoria,
               carteira[i].quantidade,
               carteira[i].precoCompra,
               carteira[i].precoAtual,
               valorAtual);
    }
}

double calcularValorTotal(const Ativo carteira[], int total) {
    double valorTotal = 0.0;

    for (int i = 0; i < total; i++) {
        valorTotal += carteira[i].quantidade * carteira[i].precoAtual;
    }

    return valorTotal;
}

double calcularRentabilidadeGeral(const Ativo carteira[], int total) {
    double valorInvestido = 0.0;
    double valorAtual = 0.0;

    for (int i = 0; i < total; i++) {
        valorInvestido += carteira[i].quantidade * carteira[i].precoCompra;
        valorAtual += carteira[i].quantidade * carteira[i].precoAtual;
    }

    if (valorInvestido <= 0.0) {
        return 0.0;
    }

    return ((valorAtual - valorInvestido) / valorInvestido) * 100.0;
}
