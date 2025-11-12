#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "planilha.h"
#include "buscas.h"

#define NUM_REPETICOES 30
#define NUM_INSERCOES_MEDIAS 100

static void setup_grafo_profundo()
{
  inicializar_planilha();
  char formula[10];
  char nome_celula_dep[4];
  for (int i = 0; i < NUM_CELLS - 1; i++)
  {
    get_nome_celula(i + 1, nome_celula_dep);
    sprintf(formula, "=%s", nome_celula_dep);
    atualizar_celula(i, formula);
  }
  atualizar_celula(NUM_CELLS - 1, "10");
  calcular_tudo();
}

void teste_a_insercao_media()
{
  printf("(a) Testando Insercao Media (100 numeros)...\n");
  double tempo_total_acumulado = 0.0;
  for (int i = 0; i < NUM_REPETICOES; i++)
  {
    inicializar_planilha();
    clock_t inicio = clock();
    for (int j = 0; j < NUM_INSERCOES_MEDIAS; j++)
    {
      atualizar_celula(j, "10");
    }
    clock_t fim = clock();
    tempo_total_acumulado += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  }
  double tempo_medio_total = tempo_total_acumulado / NUM_REPETICOES;
  double tempo_medio_por_insercao = tempo_medio_total / NUM_INSERCOES_MEDIAS;
  printf("  Tempo medio por insercao: %f segundos\n", tempo_medio_por_insercao);
}

void teste_a_insercao_pior_caso()
{
  printf("(a) Testando Pior Caso de Insercao (1 formula complexa)...\n");
  double tempo_total_acumulado = 0.0;
  for (int i = 0; i < NUM_REPETICOES; i++)
  {
    inicializar_planilha();
    clock_t inicio = clock();
    atualizar_celula(0, "@soma(B1..H20)");
    clock_t fim = clock();
    tempo_total_acumulado += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  }
  double tempo_medio = tempo_total_acumulado / NUM_REPETICOES;
  printf("  Tempo medio por insercao: %f segundos\n", tempo_medio);
}

void teste_b_busca_bfs()
{
  printf("(b) Testando Busca em Largura (BFS) - Pior Caso (Cadeia longa)...\n");
  double tempo_total_acumulado = 0.0;

  int resultados_fantasma[NUM_CELLS];

  for (int i = 0; i < NUM_REPETICOES; i++)
  {
    setup_grafo_profundo();
    clock_t inicio = clock();

    buscar_bfs(0, resultados_fantasma);

    clock_t fim = clock();
    tempo_total_acumulado += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  }

  double tempo_medio = tempo_total_acumulado / NUM_REPETICOES;
  printf("  Tempo medio por busca:  %f segundos\n", tempo_medio);
}

void teste_c_busca_dfs()
{
  printf("(c) Testando Busca em Profundidade (DFS) - Pior Caso (Cadeia longa)...\n");
  double tempo_total_acumulado = 0.0;

  int resultados_fantasma[NUM_CELLS];

  for (int i = 0; i < NUM_REPETICOES; i++)
  {
    setup_grafo_profundo();
    clock_t inicio = clock();

    buscar_dfs(0, resultados_fantasma);

    clock_t fim = clock();
    tempo_total_acumulado += ((double)(fim - inicio)) / CLOCKS_PER_SEC;
  }

  double tempo_medio = tempo_total_acumulado / NUM_REPETICOES;
  printf("  Tempo medio por busca:  %f segundos\n", tempo_medio);
}

int main()
{
  printf("--- Iniciando Testes de Performance (%d repeticoes cada) ---\n\n", NUM_REPETICOES);
  teste_a_insercao_media();
  teste_a_insercao_pior_caso();
  teste_b_busca_bfs();
  teste_c_busca_dfs();
  printf("\n--- Testes Concluidos ---\n");
  return 0;
}