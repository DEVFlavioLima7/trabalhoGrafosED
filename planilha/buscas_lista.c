#include "buscas.h"
#include "planilha.h"
#include <stdio.h>

extern NoDependencia *grafo_adj_lista[NUM_CELLS];
static int visitada_busca[NUM_CELLS];
static int *p_resultados_busca;
static int contador_resultados;
static int fila_bfs[NUM_CELLS];
static int fila_inicio = 0, fila_fim = 0;

static void fila_reset() { fila_inicio = fila_fim = 0; }

static void fila_push(int v)
{
  if (fila_fim < NUM_CELLS)
    fila_bfs[fila_fim++] = v;
}

static int fila_pop() { return (fila_inicio < fila_fim) ? fila_bfs[fila_inicio++] : -1; }
static int fila_vazia() { return fila_inicio == fila_fim; }

static void dfs_core(int u)
{
  visitada_busca[u] = 1;
  p_resultados_busca[contador_resultados++] = u;

  NoDependencia *atual = grafo_adj_lista[u];
  while (atual != NULL)
  {
    int v = atual->indice_dependencia;
    if (!visitada_busca[v])
    {
      dfs_core(v);
    }
    atual = atual->proximo;
  }
}

int buscar_dfs(int indice_inicio, int *resultados)
{
  p_resultados_busca = resultados;
  contador_resultados = 0;
  for (int i = 0; i < NUM_CELLS; i++)
    visitada_busca[i] = 0;

  dfs_core(indice_inicio);
  return contador_resultados;
}

int buscar_bfs(int indice_inicio, int *resultados)
{
  p_resultados_busca = resultados;
  contador_resultados = 0;
  for (int i = 0; i < NUM_CELLS; i++)
    visitada_busca[i] = 0;
  fila_reset();

  fila_push(indice_inicio);
  visitada_busca[indice_inicio] = 1;

  while (!fila_vazia())
  {
    int u = fila_pop();
    p_resultados_busca[contador_resultados++] = u;

    NoDependencia *atual = grafo_adj_lista[u];
    while (atual != NULL)
    {
      int v = atual->indice_dependencia;
      if (!visitada_busca[v])
      {
        visitada_busca[v] = 1;
        fila_push(v);
      }
      atual = atual->proximo;
    }
  }
  return contador_resultados;
}