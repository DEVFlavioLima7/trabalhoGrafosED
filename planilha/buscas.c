#include "buscas.h"
#include "planilha.h"

// --- Variáveis Estáticas (Privadas) ---
static int fila_bfs[NUM_CELLS];
static int fila_inicio = 0;
static int fila_fim = 0;
static int visitada_busca[NUM_CELLS];

// --- MUDANÇA: Variáveis globais (estáticas) para guardar os resultados ---
static int *p_resultados_busca; // Ponteiro para o array de resultados do main
static int contador_resultados; // Contador de quantos resultados encontramos

// --- Funções da Fila (sem mudanças) ---
static void fila_push(int indice)
{
  if (fila_fim < NUM_CELLS)
    fila_bfs[fila_fim++] = indice;
}
static int fila_pop()
{
  if (fila_inicio < fila_fim)
    return fila_bfs[fila_inicio++];
  return -1;
}
static int fila_vazia() { return fila_inicio == fila_fim; }
static void fila_reset()
{
  fila_inicio = 0;
  fila_fim = 0;
}

// --- Lógica do DFS ---
static void dfs_recursiva(int indice)
{
  visitada_busca[indice] = 1;

  // MUDANÇA: Em vez de imprimir, salva o resultado
  p_resultados_busca[contador_resultados] = indice;
  contador_resultados++;

  NoDependencia *dep = get_lista_adjacencia(indice);
  NoDependencia *atual = dep;
  while (atual != NULL)
  {
    if (!visitada_busca[atual->indice_dependencia])
    {
      dfs_recursiva(atual->indice_dependencia);
    }
    atual = atual->proximo;
  }
  free_lista_adjacencia(dep);
}

// MUDANÇA: A função agora aceita 'resultados' e retorna um 'int'
int buscar_dfs(int indice_inicio, int *resultados)
{
  // Configura os ponteiros estáticos
  p_resultados_busca = resultados;
  contador_resultados = 0;

  for (int i = 0; i < NUM_CELLS; i++)
    visitada_busca[i] = 0;

  // Os printf foram removidos
  dfs_recursiva(indice_inicio);

  return contador_resultados; // Retorna o número de itens encontrados
}

// --- Lógica do BFS ---
// MUDANÇA: A função agora aceita 'resultados' e retorna um 'int'
int buscar_bfs(int indice_inicio, int *resultados)
{
  // Configura os ponteiros estáticos
  p_resultados_busca = resultados;
  contador_resultados = 0;

  for (int i = 0; i < NUM_CELLS; i++)
    visitada_busca[i] = 0;
  fila_reset();

  // Os printf foram removidos
  fila_push(indice_inicio);
  visitada_busca[indice_inicio] = 1;

  while (!fila_vazia())
  {
    int indice_atual = fila_pop();

    // MUDANÇA: Em vez de imprimir, salva o resultado
    p_resultados_busca[contador_resultados] = indice_atual;
    contador_resultados++;

    NoDependencia *dep = get_lista_adjacencia(indice_atual);
    NoDependencia *atual = dep;
    while (atual != NULL)
    {
      if (!visitada_busca[atual->indice_dependencia])
      {
        visitada_busca[atual->indice_dependencia] = 1;
        fila_push(atual->indice_dependencia);
      }
      atual = atual->proximo;
    }
    free_lista_adjacencia(dep);
  }

  return contador_resultados; // Retorna o número de itens encontrados
}