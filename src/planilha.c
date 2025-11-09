#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planilha.h"

#define MAX_CELULAS 20  // Máximo de linhas (A até T)
#define MAX_COLUNAS 8   // Máximo de colunas (A até H)

// Função para inicializar a planilha
void inicializar_planilha(Celula planilha[20][8]) {
    for (int i = 0; i < MAX_CELULAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            planilha[i][j].valor = 0;
            planilha[i][j].num_dependencias = 0;
        }
    }
}

// Função para exibir a planilha
void exibir_planilha(Celula planilha[20][8]) {
    printf("Planilha de Cálculo:\n");
    for (int i = 0; i < MAX_CELULAS; i++) {
        for (int j = 0; j < MAX_COLUNAS; j++) {
            printf("Célula %c%d: %.2f\n", 'A' + j, i + 1, planilha[i][j].valor);
        }
    }
}

// Função para inserir um valor em uma célula
void inserir_valor(Celula planilha[20][8], char nome[], double valor) {
    int linha = nome[1] - '1';  // Converte a linha (1..20) para índice (0..19)
    int coluna = nome[0] - 'A'; // Converte a coluna (A..H) para índice (0..7)
    
    planilha[linha][coluna].valor = valor;
    printf("Valor %.2f inserido na célula %s.\n", valor, nome);
}

// Função para inserir uma fórmula em uma célula
void inserir_formula(Celula planilha[20][8], char nome[], char formula[]) {
    int linha = nome[1] - '1';
    int coluna = nome[0] - 'A';
    
    // Para simplicidade, vamos assumir que as fórmulas são somas de células vizinhas
    if (formula[0] == '=' && formula[1] == 'B') {
        // Exemplo de fórmula: soma das células B1 e C1
        planilha[linha][coluna].valor = planilha[linha][coluna + 1].valor + planilha[linha][coluna + 2].valor;
        printf("Fórmula %s inserida na célula %s.\n", formula, nome);
    }
}

// Função para calcular o valor de uma célula
double calcular_valor(Celula planilha[20][8], char nome[]) {
    int linha = nome[1] - '1';
    int coluna = nome[0] - 'A';

    // Simples: se tiver uma fórmula, calcula o valor
    if (planilha[linha][coluna].num_dependencias > 0) {
        // Aqui você pode aplicar lógica para calcular as fórmulas dependendo das dependências
    }

    return planilha[linha][coluna].valor;
}
