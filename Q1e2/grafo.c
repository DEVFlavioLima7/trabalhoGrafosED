#include "grafo.h"

// Implementação das funções de Matriz de Adjacência
GrafoMatriz* criar_grafo_matriz(int V) {
    GrafoMatriz *g = (GrafoMatriz*) malloc(sizeof(GrafoMatriz));
    if (!g) return NULL;
    g->V = V;
    g->matriz = (int**) calloc(V, sizeof(int*));
    for (int i = 0; i < V; i++) {
        g->matriz[i] = (int*) calloc(V, sizeof(int));
    }
    // Inicialmente, todas as arestas são 0 (sem conexão)
    return g;
}

void destruir_grafo_matriz(GrafoMatriz *g) {
    if (g) {
        for (int i = 0; i < g->V; i++) {
            free(g->matriz[i]);
        }
        free(g->matriz);
        free(g);
    }
}

void adicionar_aresta_matriz(GrafoMatriz *g, int origem, int destino, int peso) {
    if (origem >= 0 && origem < g->V && destino >= 0 && destino < g->V) {
        // Grafo não-direcionado (Hanoi) ou Direcionado (Planilha)
        // Para Torre de Hanói, o grafo é não-direcionado.
        g->matriz[origem][destino] = peso;
        // g->matriz[destino][origem] = peso; // Se for não-direcionado
    }
}

// Implementação das funções de Lista de Adjacência
GrafoLista* criar_grafo_lista(int V) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    if (!g) return NULL;
    g->V = V;
    g->lista = (NoLista**) calloc(V, sizeof(NoLista*));
    // Inicialmente, todas as listas são NULL
    return g;
}

void destruir_grafo_lista(GrafoLista *g) {
    if (g) {
        for (int i = 0; i < g->V; i++) {
            NoLista *atual = g->lista[i];
            while (atual) {
                NoLista *temp = atual;
                atual = atual->prox;
                free(temp);
            }
        }
        free(g->lista);
        free(g);
    }
}

void adicionar_aresta_lista(GrafoLista *g, int origem, int destino, int peso) {
    if (origem >= 0 && origem < g->V) {
        // Cria novo nó
        NoLista *novo_no = (NoLista*) malloc(sizeof(NoLista));
        if (!novo_no) return;
        novo_no->destino = destino;
        novo_no->peso = peso;
        
        // Adiciona no início da lista de adjacência da origem
        novo_no->prox = g->lista[origem];
        g->lista[origem] = novo_no;

        // Se for não-direcionado (Hanoi), adicione a aresta de volta
        /*
        NoLista *novo_no_rev = (NoLista*) malloc(sizeof(NoLista));
        novo_no_rev->destino = origem;
        novo_no_rev->peso = peso;
        novo_no_rev->prox = g->lista[destino];
        g->lista[destino] = novo_no_rev;
        */
    }
}