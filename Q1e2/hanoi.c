#include "hanoi.h"
#include "algoritmos.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h> // Para pow(), embora não seja estritamente necessário

#define N_DISCOS 4
// 3^N_DISCOS = 3^4 = 81
#define N_VERTICES 81

// 

int config_para_indice(int *config, int n) {
    int indice = 0;
    int mult = 1; // 3^0
    // Base 3: (pino_d1 - 1)*3^0 + (pino_d2 - 1)*3^1 + ...
    for (int i = 0; i < n; i++) {
        // Usamos (config[i] - 1) para obter 0, 1 ou 2.
        indice += (config[i] - 1) * mult;
        mult *= 3;
    }
    return indice;
}



void indice_para_config(int indice, int *config, int n) {
    for (int i = 0; i < n; i++) {
        // O resto da divisão por 3 é a posição do disco i (0, 1, ou 2).
        // Adicionamos 1 para obter o número do pino (1, 2, ou 3).
        config[i] = (indice % 3) + 1;
        indice /= 3;
    }
}


int buscar_disco_topo(int *config, int pino_origem) {
    // Busca do menor disco (índice 0) para o maior (índice N_DISCOS - 1).
    for (int i = 0; i < N_DISCOS; i++) {
        if (config[i] == pino_origem) {
            return i; // i é o índice do disco no topo.
        }
    }
    return -1; // Pino vazio
}


int validar_movimento(int *config, int disco_idx, int pino_destino) {
    // O movimento é legal SE NENHUM disco MENOR (índice < disco_idx) estiver no pino de destino.
    for (int i = 0; i < disco_idx; i++) {
        if (config[i] == pino_destino) {
            return 0; // Movimento Ilegal: Disco menor encontrado no destino.
        }
    }
    return 1; // Movimento Legal.
}

// --- CONSTRUÇÃO DO GRAFO (MATRIZ) ---


static void build_hanoi_graph(void *g, void (*add_edge)(void*, int, int, int)) {
    int config_atual[N_DISCOS];

    for (int i = 0; i < N_VERTICES; i++) {
        indice_para_config(i, config_atual, N_DISCOS);

        // Um disco só pode se mover do seu pino de origem para um dos outros dois pinos.
        for (int p_origem = 1; p_origem <= 3; p_origem++) {
            int disco_idx = buscar_disco_topo(config_atual, p_origem);

            // 1. O pino de origem deve ter um disco no topo.
            if (disco_idx == -1) {
                continue;
            }

            for (int p_destino = 1; p_destino <= 3; p_destino++) {
                // 2. O pino de destino não pode ser o pino de origem.
                // 3. O movimento deve ser legal.
                if ((p_origem != p_destino) && 
                    validar_movimento(config_atual, disco_idx, p_destino)) 
                {
                    // Cria o novo estado após o movimento.
                    int config_nova[N_DISCOS];
                    memcpy(config_nova, config_atual, sizeof(int) * N_DISCOS);
                    config_nova[disco_idx] = p_destino;

                    int j = config_para_indice(config_nova, N_DISCOS);

                    // Adiciona as arestas (movimento para frente e reverso) com peso 1.
                    add_edge(g, i, j, 1);
                    add_edge(g, j, i, 1);
                }
            }
        }
    }
}

// Pequenas wrappers para evitar casts de ponteiro de função
static void add_edge_matriz(void *g, int a, int b, int w) {
    adicionar_aresta_matriz((GrafoMatriz*)g, a, b, w);
}

static void add_edge_lista(void *g, int a, int b, int w) {
    adicionar_aresta_lista((GrafoLista*)g, a, b, w);
}

GrafoMatriz* construir_grafo_hanoi_matriz() {
    GrafoMatriz *g = criar_grafo_matriz(N_VERTICES);
    build_hanoi_graph(g, add_edge_matriz);
    return g;
}

// --- CONSTRUÇÃO DO GRAFO (LISTA) ---

GrafoLista* construir_grafo_hanoi_lista() {
    GrafoLista *g = criar_grafo_lista(N_VERTICES);
    build_hanoi_graph(g, add_edge_lista);
    return g;
}

// --- FUNÇÕES DE RESOLUÇÃO (Q1 e Q2) ---


void resolver_hanoi_matriz() {
    printf("Resolvendo Torre de Hanói (%d discos) usando Matriz de Adjacencia...\n", N_DISCOS);
    clock_t start = clock();
    
    GrafoMatriz *g = construir_grafo_hanoi_matriz();
    
    int origem = 0; // Configuração inicial (1,1,1,1) -> todos os discos no pino 1
    int destino = N_VERTICES - 1; // Configuração final (3,3,3,3) -> todos os discos no pino 3
    
    int distancia = dijkstra_matriz(g, origem, destino); 
    
    clock_t end = clock();
    double tempo_gasto = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n--- RESULTADO Q1 (Matriz de Adjacencia) ---\n");
    printf("-> Menor Caminho (Movimentos): %d\n", distancia); 
    printf("-> Tempo Total Gasto (Construcao + Busca): %.6f segundos\n", tempo_gasto);
    
    destruir_grafo_matriz(g);
}


void resolver_hanoi_lista() {
    printf("Resolvendo Torre de Hanói (%d discos) usando Lista de Adjacencia...\n", N_DISCOS);
    clock_t start = clock();
    
    GrafoLista *g = construir_grafo_hanoi_lista();
    
    int origem = 0; // Configuração inicial (1,1,1,1)
    int destino = N_VERTICES - 1; // Configuração final (3,3,3,3)
    
    int distancia = dijkstra_lista(g, origem, destino); 
    
    clock_t end = clock();
    double tempo_gasto = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("\n--- RESULTADO Q2 (Lista de Adjacencia) ---\n");
    printf("-> Menor Caminho (Movimentos): %d\n", distancia);
    printf("-> Tempo Total Gasto (Construcao + Busca): %.6f segundos\n", tempo_gasto);
 
    destruir_grafo_lista(g);
}