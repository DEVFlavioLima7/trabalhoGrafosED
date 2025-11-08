#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "torre_hanoi.h"

// Função para mover discos de uma torre para outra
void torre_de_hanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 1) {
        printf("Mover disco de %c para %c\n", origem, destino);
        return;
    }
    torre_de_hanoi(n - 1, origem, auxiliar, destino);
    printf("Mover disco de %c para %c\n", origem, destino);
    torre_de_hanoi(n - 1, auxiliar, destino, origem);
}

// Função para imprimir a configuração das torres
void imprimir_configuracao(Configuracao *config) {
    printf("Torre A: ");
    for (int i = 0; i < 3; i++) {
        if (config->discos[0] & (1 << i)) printf("%d ", i + 1);
    }
    printf("\n");

    printf("Torre B: ");
    for (int i = 0; i < 3; i++) {
        if (config->discos[1] & (1 << i)) printf("%d ", i + 1);
    }
    printf("\n");

    printf("Torre C: ");
    for (int i = 0; i < 3; i++) {
        if (config->discos[2] & (1 << i)) printf("%d ", i + 1);
    }
    printf("\n");
}

// Função para criar o grafo de movimentos (matriz de adjacência)
void criar_grafo(int n) {
    // Matriz de adjacência que representaria as conexões entre configurações
    // Para simplificação, consideramos um grafo muito pequeno aqui como exemplo.
    int grafo[6][6] = {
        {1, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };
    // Exemplo: criar o grafo baseado em 6 movimentos possíveis
    printf("Grafo criado com %d movimentos.\n", n);
}

// Função para aplicar o algoritmo de Dijkstra para o menor caminho entre configurações
int dijkstra(int grafo[][3], int n, int inicio, int fim) {
    int dist[n];  // Distância mínima de cada nó
    int visitado[n];  // Nós já visitados
    memset(dist, 1000, sizeof(dist));  // Inicializando as distâncias com valores altos
    memset(visitado, 0, sizeof(visitado));  // Inicializando todos os nós como não visitados

    dist[inicio] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == 1000) break;

        visitado[u] = 1;

        for (int v = 0; v < n; v++) {
            if (grafo[u][v] && dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
            }
        }
    }

    return dist[fim];  // Retorna a distância mínima do início até o fim
}
