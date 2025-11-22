#ifndef GRAFO_H
#define GRAFO_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h> // Para medir tempo

// 1. Definição da estrutura de Grafo com Matriz de Adjacência
// V = Número de vértices
typedef struct {
    int V; // Número de vértices
    int **matriz; // Matriz de adjacência (V x V)
    // Para Hanoi: Mapeamento de Configuração (vetor int) -> Índice do vértice (int)
    // Para Planilha: Mapeamento de Célula (string) -> Índice do vértice (int)
} GrafoMatriz;

// 2. Definição da estrutura para Lista de Adjacência (usada nas Questões 2 e 4)
typedef struct no_lista {
    int destino;
    int peso; // Para Dijkstra: peso = 1
    struct no_lista *prox;
} NoLista;

typedef struct {
    int V; // Número de vértices
    NoLista **lista; // Vetor de ponteiros para listas (V posições)
} GrafoLista;

// Funções para Grafo - Matriz
GrafoMatriz* criar_grafo_matriz(int V);
void destruir_grafo_matriz(GrafoMatriz *g);
void adicionar_aresta_matriz(GrafoMatriz *g, int origem, int destino, int peso);

// Funções para Grafo - Lista
GrafoLista* criar_grafo_lista(int V);
void destruir_grafo_lista(GrafoLista *g);
void adicionar_aresta_lista(GrafoLista *g, int origem, int destino, int peso);

#endif // GRAFO_H