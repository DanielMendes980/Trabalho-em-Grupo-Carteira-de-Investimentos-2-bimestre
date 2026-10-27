#ifndef FUNCOES_H
#define FUNCOES_H

#include "modulo.h"

int cadastrarAtivo(Ativo carteira[], int *total, int capacidade);
void listarAtivos(const Ativo carteira[], int total);
double calcularValorTotal(const Ativo carteira[], int total);
double calcularRentabilidadeGeral(const Ativo carteira[], int total);

#endif
