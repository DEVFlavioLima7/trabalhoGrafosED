#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "grafo.h"

// Algoritmo de Dijkstra
int dijkstra_matriz(GrafoMatriz *g, int origem, int destino);
int dijkstra_lista(GrafoLista *g, int origem, int destino);

// Busca em Largura (BFS) - Usada para Planilha/Atualização
void bfs_matriz(GrafoMatriz *g, int origem);

// Busca em Profundidade (DFS) - Usada para Planilha/Atualização
void dfs_matriz(GrafoMatriz *g, int origem);

// Observação: Para medição de tempo, repita a execução 30 vezes e calcule a média, 
// conforme solicitado na Questão 6.

#endif // ALGORITMOS_H