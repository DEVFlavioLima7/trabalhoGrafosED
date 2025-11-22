#include "hanoi.h"
#include "algoritmos.h"
#include <stdio.h>
#include <time.h>

#define REPETICOES 30
#define N_DISCOS 4
#define N_VERTICES 81

// Função auxiliar para calcular o tempo médio de inserção (construção)
double calcular_tempo_medio_construcao_matriz() {
    clock_t start, end;
    double total_time = 0;
    
    for (int i = 0; i < REPETICOES; i++) {
        start = clock();
        GrafoMatriz *g = construir_grafo_hanoi_matriz();
        end = clock();
        total_time += (double)(end - start) / CLOCKS_PER_SEC;
        destruir_grafo_matriz(g); // Destrói após a medição para isolar o tempo
    }
    return total_time / REPETICOES;
}

// Função auxiliar para calcular o tempo médio de busca (Dijkstra)
double calcular_tempo_medio_busca_matriz() {
    clock_t start, end;
    double total_time = 0;
    
    // Constrói o grafo uma vez (o tempo de construção não é medido aqui)
    GrafoMatriz *g = construir_grafo_hanoi_matriz();
    int origem = 0;
    int destino = N_VERTICES - 1;

    for (int i = 0; i < REPETICOES; i++) {
        start = clock();
        dijkstra_matriz(g, origem, destino);
        end = clock();
        total_time += (double)(end - start) / CLOCKS_PER_SEC;
    }

    destruir_grafo_matriz(g);
    return total_time / REPETICOES;
}

void testar_tempo_medio_hanoi() {
    printf("--- MEDIÇÃO DE TEMPO MÉDIO (QUESTÃO 6) ---\n");
    printf("Realizando %d repetições para Matriz de Adjacência...\n", REPETICOES);

    // Tempo para Matriz de Adjacência
    double tm_matriz_insercao = calcular_tempo_medio_construcao_matriz();
    double tm_matriz_busca = calcular_tempo_medio_busca_matriz();

    printf("\n[MATRIZ DE ADJACÊNCIA]\n");
    printf("(a) Tempo Médio Inserção (Construção): %.9f segundos\n", tm_matriz_insercao);
    printf("(b) Tempo Médio Busca (Dijkstra): %.9f segundos\n", tm_matriz_busca);

    // Fazer o mesmo para a Lista de Adjacência (Q2/Q6)
    // double tm_lista_insercao = calcular_tempo_medio_construcao_lista(); // Necessita de nova função
    // double tm_lista_busca = calcular_tempo_medio_busca_lista(); // Necessita de nova função

    // ... e apresentar a análise final (Q6)
}