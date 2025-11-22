#ifndef HASHING_H
#define HASHING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definições ---
#define N_ALUNOS 4000
#define TAM_VETOR_A 1211 // Tamanho 1 (Primo)
#define TAM_VETOR_B 1280 // Tamanho 2 (Potência de 2, ou próximo)
#define MATRICULA_LEN 11

// Estrutura de Dados do Aluno (Informação a ser armazenada na Tabela Hash)
typedef struct {
    char matricula[MATRICULA_LEN + 1]; // 11 dígitos + '\0'
    char nome[100];
    char curso[50];
    int periodo;
    int ano_ingresso;
    int ocupado; // Flag para indicar se a posição está ocupada (1) ou livre (0)
} DadosAluno;

// Estrutura da Tabela Hash
typedef struct {
    DadosAluno *tabela;
    int tamanho;
    int colisoes; // Contador de colisões
    int ocupacao; // Contador de elementos inseridos
} TabelaHash;

// --- Funções Auxiliares ---
TabelaHash* criar_tabela_hash(int tamanho);
void destruir_tabela_hash(TabelaHash *th);

// Função para gerar dados simulados (necessário para o teste de 4000 alunos)
void gerar_dados_alunos(DadosAluno alunos[], int n);

// --- Funções de Hashing e Colisão ---

// Questão 7(a) - Hashing com Rotação e Sonda Linear Modificada
int hash_a(const char *mat, int tamanho);
int colisao_a(const char *mat_rotacionada, int i, int tamanho, int hash_inicial);

// Questão 7(b) - Hashing com Fold Shift e Sonda Linear Modificada
int hash_b(const char *mat, int tamanho);
int colisao_b(const char *mat, int i, int tamanho, int hash_inicial);

// --- Função de Inserção Genérica ---
int inserir_hash(TabelaHash *th, const DadosAluno *aluno, 
                 int (*hash_func)(const char*, int), 
                 int (*colisao_func)(const char*, int, int, int),
                 const char *mat_origem); // Usada para extrair info de colisão/hash

// --- Funções de Teste e Comparação ---
void simular_e_comparar_hashing();

#endif // HASHING_H