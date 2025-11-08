#ifndef TORRE_DE_HANOI_H
#define TORRE_DE_HANOI_H

// Definindo a estrutura para armazenar a configuração das torres
typedef struct {
    int discos[3];  // Cada torre (0, 1, 2) terá uma pilha de discos
} Configuracao;

// Função para resolver o problema da Torre de Hanói recursivamente
void torre_de_hanoi(int n, char origem, char destino, char auxiliar);

// Função para criar o grafo que representa as configurações do problema
void criar_grafo(int n);

// Função para aplicar o algoritmo de Dijkstra e encontrar o menor caminho
int dijkstra(int grafo[][3], int n, int inicio, int fim);

// Função para imprimir a configuração das torres
void imprimir_configuracao(Configuracao *config);

#endif // TORRE_DE_HANOI_H
