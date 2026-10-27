#ifndef MODULO_H
#define MODULO_H

#define MAX_ATIVOS 100
#define TAM_NOME 100
#define TAM_CATEGORIA 50

typedef struct Ativo {
    char nome[TAM_NOME];
    char categoria[TAM_CATEGORIA];
    double quantidade;
    double precoCompra;
    double precoAtual;
} Ativo;

int carregarCarteira(const char *caminho, Ativo carteira[], int capacidade);
int salvarCarteira(const char *caminho, const Ativo carteira[], int total);

#endif
