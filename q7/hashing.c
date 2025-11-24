#include "hashing.h"
#include <math.h>
#include <time.h>

// --- Funções Auxiliares de Gerenciamento ---

TabelaHash* criar_tabela_hash(int tamanho) {
    TabelaHash *th = (TabelaHash*) malloc(sizeof(TabelaHash));
    if (!th) return NULL;
    
    th->tamanho = tamanho;
    th->colisoes = 0;
    th->ocupacao = 0;
    
    // Aloca a tabela e zera a memória
    th->tabela = (DadosAluno*) calloc(tamanho, sizeof(DadosAluno));
    if (!th->tabela) {
        free(th);
        return NULL;
    }
    // O calloc já garante que 'ocupado' é 0
    return th;
}

void destruir_tabela_hash(TabelaHash *th) {
    if (th) {
        free(th->tabela);
        free(th);
    }
}

// Função para gerar dados simulados de 4000 alunos (Matrículas de 11 dígitos)
void gerar_dados_alunos(DadosAluno alunos[], int n) {
    srand(time(NULL)); 
    
    int ano_inicial = 2010;
    int max_curso = 9;

    for (int i = 0; i < n; i++) {
        // d1 d2 d3 d4: Ano de Ingresso (Ex: 2010 a 2025)
        int ano_ingresso = ano_inicial + (rand() % 16); 
        
        // d5: Número do Curso (Ex: 1 a 9)
        int num_curso = 1 + (rand() % max_curso);
        
        // d6 d7 d8 d9 d10 d11: Número Específico do Aluno (000001 a 999999)
        int num_aluno = 1 + (rand() % 999999);
        
        // Formatação final da Matrícula (11 dígitos)
        sprintf(alunos[i].matricula, "%4d%1d%06d", ano_ingresso, num_curso, num_aluno);
        
        // Preenchimento dos outros campos (Simulação)
        sprintf(alunos[i].nome, "Aluno %d", i + 1);
        sprintf(alunos[i].curso, "IS%d", num_curso);
        alunos[i].periodo = 1 + (rand() % 8);
        alunos[i].ano_ingresso = ano_ingresso;
        alunos[i].ocupado = 0;
    }
}

// --- Funções para Questão 7(a) ---

// Hashing: rotação dos 5 primeiros dígitos para a direita
int hash_a(const char *mat, int tamanho) {
    char mat_rotacionada[MATRICULA_LEN + 1];
    strcpy(mat_rotacionada, mat);

    // 1. Rotação dos 5 primeiros dígitos (d1 d2 d3 d4 d5 -> d5 d1 d2 d3 d4)
    char d5 = mat_rotacionada[4];
    for (int i = 4; i > 0; i--) {
        mat_rotacionada[i] = mat_rotacionada[i - 1];
    }
    mat_rotacionada[0] = d5; // Matrícula rotacionada temporariamente

    // 2. Extrai o 2º, 4º e 5º dígitos (índices 1, 3, 4)
    char digitos[4] = {mat_rotacionada[1], mat_rotacionada[3], mat_rotacionada[4], '\0'};
    long valor_extraido = atol(digitos);
    
    // 3. Resto da divisão
    return valor_extraido % tamanho;
}

// Colisão: (hash_inicial + i * d1_rotacionado) % tamanho
// Nota: O parâmetro 'mat_rotacionada' aqui é a matrícula JÁ rotacionada (para extrair o d1)
int colisao_a(const char *mat_rotacionada, int i, int tamanho, int hash_inicial) {
    // O 1º dígito da matrícula rotacionada é mat_rotacionada[0]
    int d1_rotacionado = mat_rotacionada[0] - '0';
    
    // Sonda Linear Modificada
    return (hash_inicial + i * d1_rotacionado) % tamanho;
}

// --- Funções para Questão 7(b) ---

// Hashing: fold shift (d6 d7 d11 e d8 d9 d10)
int hash_b(const char *mat, int tamanho) {
    // Grupo 1: d6, d7, d11 (Índices: 5, 6, 10)
    char g1_str[4] = {mat[5], mat[6], mat[10], '\0'};
    long g1 = atol(g1_str);
    
    // Grupo 2: d8, d9, d10 (Índices: 7, 8, 9)
    char g2_str[4] = {mat[7], mat[8], mat[9], '\0'};
    long g2 = atol(g2_str);

    // Fold Shift (Soma)
    long resultado = g1 + g2; 
    
    // Resto da divisão
    return resultado % tamanho;
}

// Colisão: (hash_inicial + i * (d6 + d11)) % tamanho
// Nota: O parâmetro 'mat' aqui é a matrícula ORIGINAL
int colisao_b(const char *mat, int i, int tamanho, int hash_inicial) {
    // d6 (mat[5]) e d11 (mat[10])
    int d6 = mat[5] - '0';
    int d11 = mat[10] - '0';
    int incremento = d6 + d11;
    
    // Sonda Linear Modificada
    return (hash_inicial + i * incremento) % tamanho;
}

// --- Função de Inserção Genérica ---

int inserir_hash(TabelaHash *th, const DadosAluno *aluno, 
                 int (*hash_func)(const char*, int), 
                 int (*colisao_func)(const char*, int, int, int),
                 const char *mat_origem) {
                     
    int hash_inicial = hash_func(aluno->matricula, th->tamanho);
    int indice = hash_inicial;
    int tentativas = 0; 
    int i = 0; 
    
    // Prepara a matrícula rotacionada APENAS para a Colisão A
    char mat_rotacionada[MATRICULA_LEN + 1];
    strcpy(mat_rotacionada, aluno->matricula);
    if (colisao_func == colisao_a) {
        // Aplica a rotação para a função de colisão usar o d1 rotacionado
        char d5 = mat_rotacionada[4];
        for (int k = 4; k > 0; k--) {
            mat_rotacionada[k] = mat_rotacionada[k - 1];
        }
        mat_rotacionada[0] = d5;
    } 

    // --- Loop de Sonda ---
    do {
        if (th->tabela[indice].ocupado == 0) {
            // Posição livre: Inserir
            memcpy(&th->tabela[indice], aluno, sizeof(DadosAluno));
            th->tabela[indice].ocupado = 1;
            th->ocupacao++;
            return tentativas; 
        } 
        
        // Posição ocupada: Colisão
        th->colisoes++;
        
        i++; // Incrementa o passo da sonda
        
        // Calcula o próximo índice de sonda
        if (colisao_func == colisao_a) {
            indice = colisao_func(mat_rotacionada, i, th->tamanho, hash_inicial);
        } else {
            // Para colisao_b, o parâmetro é a matrícula original
            indice = colisao_func(mat_origem, i, th->tamanho, hash_inicial);
        }
        tentativas++;
        
        // Lógica de VETOR CHEIO/FALHA DE INSERÇÃO (substituição)
        // Se a sonda tentar todas as posições (o que é V vezes), substitui na hash inicial.
        if (tentativas >= th->tamanho) {
            // Substitui na hash inicial, conforme a observação do problema.
            indice = hash_inicial; 
            memcpy(&th->tabela[indice], aluno, sizeof(DadosAluno));
            th->tabela[indice].ocupado = 1;
            // th->ocupacao NÃO é incrementado, pois é uma substituição.
            return tentativas; 
        }

    } while (1); // Loop contínuo até retornar (sucesso ou substituição)
}


// --- Funções de Teste e Comparação ---

void simular_e_comparar_hashing() {
    DadosAluno alunos[N_ALUNOS];
    gerar_dados_alunos(alunos, N_ALUNOS);

    clock_t start, end;
    
    // --- Teste A1: Hashing A, Vetor 1211 ---
    TabelaHash *th_a1 = criar_tabela_hash(TAM_VETOR_A);
    start = clock();
    for (int i = 0; i < N_ALUNOS; i++) {
        inserir_hash(th_a1, &alunos[i], hash_a, colisao_a, alunos[i].matricula);
    }
    end = clock();
    double tempo_a1 = (double)(end - start) / CLOCKS_PER_SEC;

    // --- Teste A2: Hashing A, Vetor 1280 ---
    TabelaHash *th_a2 = criar_tabela_hash(TAM_VETOR_B);
    start = clock();
    for (int i = 0; i < N_ALUNOS; i++) {
        inserir_hash(th_a2, &alunos[i], hash_a, colisao_a, alunos[i].matricula);
    }
    end = clock();
    double tempo_a2 = (double)(end - start) / CLOCKS_PER_SEC;

    // --- Teste B1: Hashing B, Vetor 1211 ---
    TabelaHash *th_b1 = criar_tabela_hash(TAM_VETOR_A);
    start = clock();
    for (int i = 0; i < N_ALUNOS; i++) {
        inserir_hash(th_b1, &alunos[i], hash_b, colisao_b, alunos[i].matricula);
    }
    end = clock();
    double tempo_b1 = (double)(end - start) / CLOCKS_PER_SEC;

    // --- Teste B2: Hashing B, Vetor 1280 ---
    TabelaHash *th_b2 = criar_tabela_hash(TAM_VETOR_B);
    start = clock();
    for (int i = 0; i < N_ALUNOS; i++) {
        inserir_hash(th_b2, &alunos[i], hash_b, colisao_b, alunos[i].matricula);
    }
    end = clock();
    double tempo_b2 = (double)(end - start) / CLOCKS_PER_SEC;

    // --- Apresentação dos Resultados ---
    printf("\n--- RESULTADOS DA SIMULACAO DE HASHING (Questao 7) ---\n");
    printf("Simulacao de insercao de %d alunos em 4 cenarios diferentes.\n", N_ALUNOS);
    
    printf("\n| Teste | Funcao Hashing | Tamanho (M) | Colisoes | Tempo Total Insercao (s) |\n");
    printf("|:-----:|:--------------:|:-----------:|:--------:|:------------------------:|\n");
    printf("| A1    | Rotacao (A)    | %d          | %d      | %.6f                   |\n", TAM_VETOR_A, th_a1->colisoes, tempo_a1);
    printf("| A2    | Rotacao (A)    | %d          | %d      | %.6f                   |\n", TAM_VETOR_B, th_a2->colisoes, tempo_a2);
    printf("| B1    | Fold Shift (B) | %d          | %d      | %.6f                   |\n", TAM_VETOR_A, th_b1->colisoes, tempo_b1);
    printf("| B2    | Fold Shift (B) | %d          | %d      | %.6f                   |\n", TAM_VETOR_B, th_b2->colisoes, tempo_b2);
    
    // --- Análise da Maior Colisão ---
    int max_colisoes = th_a1->colisoes;
    if (th_a2->colisoes > max_colisoes) max_colisoes = th_a2->colisoes;
    if (th_b1->colisoes > max_colisoes) max_colisoes = th_b1->colisoes;
    if (th_b2->colisoes > max_colisoes) max_colisoes = th_b2->colisoes;

    printf("\nAnalise de Colisoes e Desempenho:\n");
    printf("* O maior numero de colisoes (%d) ocorreu em:\n", max_colisoes);
    if (th_a1->colisoes == max_colisoes) printf("  - Teste A1 (Hash A, Tam 1211)\n");
    if (th_a2->colisoes == max_colisoes) printf("  - Teste A2 (Hash A, Tam 1280)\n");
    if (th_b1->colisoes == max_colisoes) printf("  - Teste B1 (Hash B, Tam 1211)\n");
    if (th_b2->colisoes == max_colisoes) printf("  - Teste B2 (Hash B, Tam 1280)\n");
    
    printf("* O desempenho (tempo) esta diretamente ligado ao numero de colisoes e a eficiencia da funcao de colisao (sonda).\n");
    
    // --- Destruição ---
    destruir_tabela_hash(th_a1);
    destruir_tabela_hash(th_a2);
    destruir_tabela_hash(th_b1);
    destruir_tabela_hash(th_b2);
}