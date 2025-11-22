#include "hanoi.h"
#include "algoritmos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>

#define N_DISCOS 4
#define N_VERTICES 81

// --- Funções de Mapeamento ---

// Converte a configuração (vetor de pinos [d1, d2, d3, d4]) para o índice do vértice (0 a 80)
int config_para_indice(int *config, int n) {
    int indice = 0;
    // Base 3: (pino_d1 - 1)*3^0 + (pino_d2 - 1)*3^1 + ...
    for (int i = 0; i < n; i++) {
        indice += (config[i] - 1) * (int)pow(3, i);
    }
    return indice;
}

// Converte o índice do vértice (0 a 80) para a configuração (vetor de pinos)
void indice_para_config(int indice, int *config, int n) {
    for (int i = 0; i < n; i++) {
        config[i] = (indice % 3) + 1; // Pinos são 1, 2, 3
        indice /= 3;
    }
}

// Retorna o índice do menor disco no topo do pino 'pino_origem'.
// O disco 0 é o menor, o disco N_DISCOS-1 é o maior.
// Retorna -1 se o pino estiver vazio.
int buscar_disco_topo(int *config, int pino_origem) {
    for (int i = 0; i < N_DISCOS; i++) {
        if (config[i] == pino_origem) {
            return i; // i é o índice do disco (0 a 3)
        }
    }
    return -1; // Pino vazio
}

// Verifica se um movimento do disco 'disco_idx' para o 'pino_destino' é legal.
int validar_movimento(int *config, int disco_idx, int pino_destino) {
    // Um disco (disco_idx) só pode ser colocado se não houver um disco menor 
    // (com índice < disco_idx) já presente no pino de destino.
    
    for (int i = 0; i < disco_idx; i++) {
        // Se encontrarmos um disco MENOR (i) no destino, o movimento é ilegal.
        if (config[i] == pino_destino) {
            return 0; // Movimento Ilegal
        }
    }
    return 1; // Movimento Legal
}

// --- CONSTRUÇÃO DO GRAFO (MATRIZ) ---

GrafoMatriz* construir_grafo_hanoi_matriz() {
    GrafoMatriz *g = criar_grafo_matriz(N_VERTICES);
    int config_atual[N_DISCOS];
    
    for (int i = 0; i < N_VERTICES; i++) {
        indice_para_config(i, config_atual, N_DISCOS);
        
        // Tentar mover o disco de cada pino (1, 2, 3)
        for (int p_origem = 1; p_origem <= 3; p_origem++) {
            int disco_idx = buscar_disco_topo(config_atual, p_origem);
            
            if (disco_idx != -1) {
                // Tentar mover para os outros dois pinos
                for (int p_destino = 1; p_destino <= 3; p_destino++) {
                    if (p_origem != p_destino) {
                        
                        if (validar_movimento(config_atual, disco_idx, p_destino)) {
                            // Configura a nova situação
                            int config_nova[N_DISCOS];
                            memcpy(config_nova, config_atual, sizeof(int) * N_DISCOS);
                            config_nova[disco_idx] = p_destino;
                            
                            int j = config_para_indice(config_nova, N_DISCOS);
                            
                            // Adicionar aresta com peso 1 (Grafo não-direcionado)
                            adicionar_aresta_matriz(g, i, j, 1);
                            // Não precisamos adicionar (j, i) aqui, pois o loop i itera sobre todos.
                            // Mas para garantir que a matriz seja simétrica, adicionamos:
                            adicionar_aresta_matriz(g, j, i, 1); 
                        }
                    }
                }
            }
        }
    }
    return g;
}

// --- CONSTRUÇÃO DO GRAFO (LISTA) ---

GrafoLista* construir_grafo_hanoi_lista() {
    GrafoLista *g = criar_grafo_lista(N_VERTICES);
    int config_atual[N_DISCOS];
    
    for (int i = 0; i < N_VERTICES; i++) {
        indice_para_config(i, config_atual, N_DISCOS);
        
        for (int p_origem = 1; p_origem <= 3; p_origem++) {
            int disco_idx = buscar_disco_topo(config_atual, p_origem);
            
            if (disco_idx != -1) {
                for (int p_destino = 1; p_destino <= 3; p_destino++) {
                    if (p_origem != p_destino) {
                        
                        if (validar_movimento(config_atual, disco_idx, p_destino)) {
                            int config_nova[N_DISCOS];
                            memcpy(config_nova, config_atual, sizeof(int) * N_DISCOS);
                            config_nova[disco_idx] = p_destino;
                            
                            int j = config_para_indice(config_nova, N_DISCOS);
                            
                            adicionar_aresta_lista(g, i, j, 1);
                            adicionar_aresta_lista(g, j, i, 1);
                        }
                    }
                }
            }
        }
    }
    return g;
}

// --- FUNÇÕES DE RESOLUÇÃO (Q1 e Q2) ---

void resolver_hanoi_matriz() {
    printf("Resolvendo Torre de Hanoi (4 discos) usando Matriz de Adjacência...\n");
    clock_t start = clock();
    
    GrafoMatriz *g = construir_grafo_hanoi_matriz();
    
    int origem = 0; // Configuração (1,1,1,1)
    int destino = N_VERTICES - 1; // Configuração (3,3,3,3)
    
    int distancia = dijkstra_matriz(g, origem, destino); 
    
    clock_t end = clock();
    double tempo_gasto = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n--- RESULTADO Q1 (Matriz de Adjacencia) ---\n");
    printf("-> Menor Caminho (Movimentos): **%d**\n", distancia); // Deve ser 15
    printf("-> Tempo Total Gasto (Construcao + Busca): **%.6f segundos**\n", tempo_gasto);
    
    destruir_grafo_matriz(g);
}

void resolver_hanoi_lista() {
    printf("Resolvendo Torre de Hanói (4 discos) usando Lista de Adjacência...\n");
    clock_t start = clock();
    
    GrafoLista *g = construir_grafo_hanoi_lista();
    
    int origem = 0;
    int destino = N_VERTICES - 1;
    
    int distancia = dijkstra_lista(g, origem, destino); 
    
    clock_t end = clock();
    double tempo_gasto = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n--- RESULTADO Q2 (Lista de Adjacencia) ---\n");
    printf("-> Menor Caminho (Movimentos): **%d**\n", distancia); 
    printf("-> Tempo Total Gasto (Construcao + Busca): **%.6f segundos**\n", tempo_gasto);
 
    destruir_grafo_lista(g);
}