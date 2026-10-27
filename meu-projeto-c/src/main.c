#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include "modulo.h"

static int lerOpcao(void) {
    char linha[64];
    char *fim;
    long opcao;

    for (;;) {
        printf("\nEscolha uma opcao: ");
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            return 5;
        }

        opcao = strtol(linha, &fim, 10);
        while (*fim == ' ' || *fim == '\t' || *fim == '\r' || *fim == '\n') {
            fim++;
        }

        if (fim == linha || *fim != '\0' || opcao < 1 || opcao > 5) {
            printf("Opcao invalida. Digite um numero de 1 a 5.\n");
            continue;
        }

        return (int)opcao;
    }
}

int main(void) {
    Ativo carteira[MAX_ATIVOS];
    int total = carregarCarteira("data/carteira.txt", carteira, MAX_ATIVOS);
    int opcao;

    do {
        printf("\n========== CARTEIRA DE INVESTIMENTOS ==========\n");
        printf("1. Cadastrar ativo\n");
        printf("2. Listar ativos\n");
        printf("3. Calcular valor total da carteira\n");
        printf("4. Calcular rentabilidade geral\n");
        printf("5. Salvar e sair\n");

        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                if (cadastrarAtivo(carteira, &total, MAX_ATIVOS)) {
                    if (salvarCarteira("data/carteira.txt", carteira, total)) {
                        printf("Carteira salva em data/carteira.txt.\n");
                    }
                }
                break;

            case 2:
                listarAtivos(carteira, total);
                break;

            case 3:
                printf("\nValor total atual da carteira: R$ %.2f\n",
                       calcularValorTotal(carteira, total));
                break;

            case 4:
                if (total == 0) {
                    printf("\nNao ha ativos cadastrados para calcular a rentabilidade.\n");
                } else {
                    printf("\nRentabilidade geral: %.2f%%\n",
                           calcularRentabilidadeGeral(carteira, total));
                    printf("O calculo considera os precos de compra e os precos atuais de todos os ativos.\n");
                }
                break;

            case 5:
                if (salvarCarteira("data/carteira.txt", carteira, total)) {
                    printf("Carteira salva. Encerrando o programa.\n");
                }
                break;

            default:
                /* A validacao em lerOpcao impede que este trecho seja executado. */
                break;
        }
    } while (opcao != 5);

    return EXIT_SUCCESS;
}
