#ifndef PLANILHA_H
#define PLANILHA_H

// Estrutura para armazenar uma célula
typedef struct {
    char nome[3];  // Nome da célula (ex: A1, B2)
    double valor;  // Valor da célula
    int dependencias[10];  // Referências para outras células (número máximo de dependências)
    int num_dependencias;  // Número de dependências
} Celula;

// Função para inicializar a planilha
void inicializar_planilha(Celula planilha[20][8]);

// Função para exibir a planilha
void exibir_planilha(Celula planilha[20][8]);

// Função para inserir um valor em uma célula
void inserir_valor(Celula planilha[20][8], char nome[], double valor);

// Função para inserir uma fórmula em uma célula
void inserir_formula(Celula planilha[20][8], char nome[], char formula[]);

// Função para calcular o valor de uma célula com base em dependências
double calcular_valor(Celula planilha[20][8], char nome[]);

#endif // PLANILHA_H
