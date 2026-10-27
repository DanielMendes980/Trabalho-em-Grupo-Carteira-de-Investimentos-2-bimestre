#include <stdio.h>
#include "modulo.h"

int carregarCarteira(const char *caminho, Ativo carteira[], int capacidade) {
    FILE *arquivo = fopen(caminho, "r");
    int total = 0;

    if (arquivo == NULL) {
        printf("Nao foi possivel abrir %s para leitura. A carteira iniciara vazia.\n", caminho);
        return 0;
    }

    while (total < capacidade) {
        int lidos = fscanf(arquivo, " %99[^;];%49[^;];%lf;%lf;%lf",
                           carteira[total].nome,
                           carteira[total].categoria,
                           &carteira[total].quantidade,
                           &carteira[total].precoCompra,
                           &carteira[total].precoAtual);

        if (lidos != 5) {
            break;
        }

        total++;

        /* Avanca ate o fim da linha para preparar a leitura do proximo ativo. */
        int caractere;
        do {
            caractere = fgetc(arquivo);
        } while (caractere != '\n' && caractere != EOF);
    }

    if (fclose(arquivo) != 0) {
        printf("Aviso: ocorreu um erro ao fechar %s.\n", caminho);
    }

    printf("Carteira carregada: %d ativo(s).\n", total);
    return total;
}

int salvarCarteira(const char *caminho, const Ativo carteira[], int total) {
    FILE *arquivo = fopen(caminho, "w");

    if (arquivo == NULL) {
        printf("Erro: nao foi possivel abrir %s para gravacao.\n", caminho);
        return 0;
    }

    for (int i = 0; i < total; i++) {
        if (fprintf(arquivo, "%s;%s;%.10g;%.10g;%.10g\n",
                    carteira[i].nome,
                    carteira[i].categoria,
                    carteira[i].quantidade,
                    carteira[i].precoCompra,
                    carteira[i].precoAtual) < 0) {
            printf("Erro ao gravar os dados da carteira.\n");
            fclose(arquivo);
            return 0;
        }
    }

    if (fclose(arquivo) != 0) {
        printf("Erro ao fechar o arquivo %s apos a gravacao.\n", caminho);
        return 0;
    }

    return 1;
}
