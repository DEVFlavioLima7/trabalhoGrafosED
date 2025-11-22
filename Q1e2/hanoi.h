#ifndef HANOI_H
#define HANOI_H

#include "grafo.h" // Dependência das estruturas de grafo

// Número de discos para o problema (N=4)
#define N_DISCOS 4
#define N_VERTICES 81 // 3^4 = 81

// Funções para mapeamento (Configuração <-> Índice)
int config_para_indice(int *config, int n);
void indice_para_config(int indice, int *config, int n);
int validar_movimento(int *config, int disco_idx, int pino_destino);

// Funções principais
GrafoMatriz* construir_grafo_hanoi_matriz();
GrafoLista* construir_grafo_hanoi_lista();

// ... no final de hanoi.h

// Função para testar a Questão 6 (Medição de tempo)
void testar_tempo_medio_hanoi();

void resolver_hanoi_matriz();
void resolver_hanoi_lista();

#endif // HANOI_H