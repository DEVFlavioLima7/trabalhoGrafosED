#include "algoritmos.h"
#include <limits.h>

#define INFINITO INT_MAX

// --- IMPLEMENTAÇÃO DIJKSTRA COM MATRIZ (Q1) ---

// Complexidade: O(V^2)
int dijkstra_matriz(GrafoMatriz *g, int origem, int destino) {
    int V = g->V;
    int dist[V];
    int visitado[V];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INFINITO;
        visitado[i] = 0;
    }
    dist[origem] = 0;
    
    for (int count = 0; count < V; count++) {
        // Encontra o vértice não visitado com a menor distância (O(V))
        int u = -1;
        int min_dist = INFINITO;
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }

        if (u == -1 || u == destino) break;
        
        visitado[u] = 1;

        // Relaxamento dos vizinhos (O(V))
        for (int v = 0; v < V; v++) {
            // Se houver aresta e o vértice não foi visitado
            if (!visitado[v] && g->matriz[u][v] != 0 && dist[u] != INFINITO) {
                int peso = g->matriz[u][v]; // Peso = 1
                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                }
            }
        }
    }
    
    return (dist[destino] == INFINITO) ? -1 : dist[destino]; 
}

// --- IMPLEMENTAÇÃO DIJKSTRA COM LISTA (Q2) ---

// Para otimizar, usaremos uma Fila de Prioridade simples (Array Min-Heap)
// Estrutura para a Fila de Prioridade (usando array para simplificar)
typedef struct {
    int v;
    int dist;
} ItemFila;

// Implementação simples O(V^2) para Lista (sem Heap), por consistência.
// Uma implementação O((V+E)logV) exigiria um Heap mais complexo.

// Complexidade: O(V^2) (se não usar Fila de Prioridade)
int dijkstra_lista(GrafoLista *g, int origem, int destino) {
    int V = g->V;
    int dist[V];
    int visitado[V];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INFINITO;
        visitado[i] = 0;
    }
    dist[origem] = 0;
    
    for (int count = 0; count < V; count++) {
        // Encontra o vértice não visitado com a menor distância (O(V))
        int u = -1;
        int min_dist = INFINITO;
        for (int v = 0; v < V; v++) {
            if (!visitado[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }

        if (u == -1 || u == destino) break;
        
        visitado[u] = 1;

        // Relaxamento dos vizinhos (O(Grau(u)))
        NoLista *atual = g->lista[u];
        while (atual) {
            int v = atual->destino;
            int peso = atual->peso; // Peso = 1

            if (!visitado[v] && dist[u] != INFINITO) {
                 if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                }
            }
            atual = atual->prox;
        }
    }
    
    return (dist[destino] == INFINITO) ? -1 : dist[destino]; 
}

// ... (Implementação futura de BFS e DFS)
void bfs_matriz(GrafoMatriz *g, int origem) { /* ... */ }
void dfs_matriz(GrafoMatriz *g, int origem) { /* ... */ }