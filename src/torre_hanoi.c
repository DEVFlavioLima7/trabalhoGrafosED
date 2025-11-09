#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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

// Função para gerar a próxima configuração válida a partir da configuração atual
int gerar_proximas_configuracoes(Configuracao *config, Configuracao *proximas) {
    int num_proximas = 0;
    
    // Gerar todas as possíveis configurações (movimentos de discos)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != j) {
                // Verifica se podemos mover um disco da torre i para a torre j
                // Para simplificação, esta função apenas realiza as trocas básicas
                proximas[num_proximas] = *config;  // Copiar a configuração atual
                proximas[num_proximas].discos[i] &= ~(1 << 0);  // Remove o disco de i
                proximas[num_proximas].discos[j] |= (1 << 0);   // Coloca o disco em j
                num_proximas++;
            }
        }
    }

    return num_proximas;
}

// Função para aplicar o algoritmo de Dijkstra para o menor caminho entre configurações
int dijkstra(Configuracao grafo[], int n, int inicio, int fim) {
    int dist[n];  // Distância mínima de cada nó
    int visitado[n];  // Nós já visitados
    int pai[n];  // Para reconstruir o caminho
    memset(dist, INT_MAX, sizeof(dist));  // Inicializando as distâncias com valores altos
    memset(visitado, 0, sizeof(visitado));  // Inicializando todos os nós como não visitados
    memset(pai, -1, sizeof(pai));  // Inicializando os pais com -1

    dist[inicio] = 0;

    for (int i = 0; i < n; i++) {
        // Encontrar o nó com a menor distância
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INT_MAX) break;

        visitado[u] = 1;

        // Gerar as próximas configurações
        Configuracao proximas[6];
        int num_proximas = gerar_proximas_configuracoes(&grafo[u], proximas);

        // Atualizar as distâncias
        for (int v = 0; v < num_proximas; v++) {
            int v_index = v;  // Assumimos um índice fictício para a configuração
            if (dist[u] + 1 < dist[v_index]) {
                dist[v_index] = dist[u] + 1;
                pai[v_index] = u;
            }
        }
    }

    return dist[fim];  // Retorna a distância mínima do início até o fim
}

