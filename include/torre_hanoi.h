#ifndef TORRE_DE_HANOI_H
#define TORRE_DE_HANOI_H

#define MAX_CONFIGURACOES 1000  // Máximo de configurações possíveis

// Definindo a estrutura para armazenar a configuração das torres
typedef struct {
    int discos[3];  // Cada torre (0, 1, 2) terá uma pilha de discos
} Configuracao;

// Função para resolver o problema da Torre de Hanói recursivamente
void torre_de_hanoi(int n, char origem, char destino, char auxiliar);

// Função para imprimir a configuração das torres
void imprimir_configuracao(Configuracao *config);

// Função para criar o grafo de movimentos (matriz de adjacência)
void criar_grafo(int n);

// Função para aplicar o algoritmo de Dijkstra e encontrar o menor caminho
int dijkstra(Configuracao grafo[], int n, int inicio, int fim);

#endif // TORRE_DE_HANOI_H
