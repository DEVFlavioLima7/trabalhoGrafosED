#include "planilha.h"

static Celula planilha[NUM_CELLS];

static int grafo_adj[NUM_CELLS][NUM_CELLS];

static int get_indice_celula(char col, int row)
{
  if (toupper(col) < 'A' || toupper(col) > 'H' || row < 1 || row > NUM_ROWS)
  {
    return -1;
  }
  int col_idx = toupper(col) - 'A';
  int row_idx = row - 1;
  return row_idx * NUM_COLS + col_idx;
}

void get_nome_celula(int indice, char *nome)
{
  if (indice < 0 || indice >= NUM_CELLS)
  {
    strcpy(nome, "ERR");
    return;
  }
  int col_idx = indice % NUM_COLS;
  int row_idx = indice / NUM_COLS;
  sprintf(nome, "%c%d", 'A' + col_idx, row_idx + 1);
}

static double calcular_celula(int indice);

static void adicionar_dependencias_range(int indice_origem, const char *range_str)
{
  char str_copia[64];
  strcpy(str_copia, range_str);

  const char *delimitadores = "..()";
  char *inicio_str = strtok(str_copia, delimitadores);
  char *fim_str = strtok(NULL, delimitadores);

  if (!inicio_str || !fim_str)
    return;

  int indice_inicio = parse_nome_celula(inicio_str);
  int indice_fim = parse_nome_celula(fim_str);
  if (indice_inicio == -1 || indice_fim == -1)
    return;

  int col_inicio = indice_inicio % NUM_COLS;
  int row_inicio = indice_inicio / NUM_COLS;
  int col_fim = indice_fim % NUM_COLS;
  int row_fim = indice_fim / NUM_COLS;

  if (col_inicio > col_fim)
  {
    int temp = col_inicio;
    col_inicio = col_fim;
    col_fim = temp;
  }
  if (row_inicio > row_fim)
  {
    int temp = row_inicio;
    row_inicio = row_fim;
    row_fim = temp;
  }

  for (int r = row_inicio; r <= row_fim; r++)
  {
    for (int c = col_inicio; c <= col_fim; c++)
    {
      int indice_dep = r * NUM_COLS + c;
      grafo_adj[indice_origem][indice_dep] = 1;
    }
  }
}

static double executar_funcao(const char *nome_funcao, const char *range_str)
{
  char str_copia[64];
  strcpy(str_copia, range_str);

  const char *delimitadores = "..()";
  char *inicio_str = strtok(str_copia, delimitadores);
  char *fim_str = strtok(NULL, delimitadores);

  if (!inicio_str || !fim_str)
    return 0.0;

  int indice_inicio = parse_nome_celula(inicio_str);
  int indice_fim = parse_nome_celula(fim_str);
  if (indice_inicio == -1 || indice_fim == -1)
    return 0.0;

  int col_inicio = indice_inicio % NUM_COLS;
  int row_inicio = indice_inicio / NUM_COLS;
  int col_fim = indice_fim % NUM_COLS;
  int row_fim = indice_fim / NUM_COLS;

  if (col_inicio > col_fim)
  {
    int temp = col_inicio;
    col_inicio = col_fim;
    col_fim = temp;
  }
  if (row_inicio > row_fim)
  {
    int temp = row_inicio;
    row_inicio = row_fim;
    row_fim = temp;
  }

  double resultado = 0.0;
  double min_val = DBL_MAX;
  double max_val = -DBL_MAX;
  int count = 0;

  for (int r = row_inicio; r <= row_fim; r++)
  {
    for (int c = col_inicio; c <= col_fim; c++)
    {
      int indice_dep = r * NUM_COLS + c;
      double valor_dep = calcular_celula(indice_dep);

      if (strncmp(nome_funcao, "soma", 4) == 0)
      {
        resultado += valor_dep;
      }
      else if (strncmp(nome_funcao, "media", 5) == 0)
      {
        resultado += valor_dep;
        count++;
      }
      else if (strncmp(nome_funcao, "max", 3) == 0)
      {
        if (valor_dep > max_val)
          max_val = valor_dep;
      }
      else if (strncmp(nome_funcao, "min", 3) == 0)
      {
        if (valor_dep < min_val)
          min_val = valor_dep;
      }
    }
  }

  if (strncmp(nome_funcao, "soma", 4) == 0)
    return resultado;
  if (strncmp(nome_funcao, "media", 5) == 0)
    return (count == 0) ? 0.0 : (resultado / count);
  if (strncmp(nome_funcao, "max", 3) == 0)
    return max_val;
  if (strncmp(nome_funcao, "min", 3) == 0)
    return min_val;

  return 0.0;
}

static double calcular_celula(int indice)
{
  Celula *celula = &planilha[indice];

  if (celula->visitada == 2)
    return celula->valor;
  if (celula->visitada == 1)
  {
    printf("ERRO: Referencia circular detectada na celula ");
    char nome[4];
    get_nome_celula(indice, nome);
    printf("%s\n", nome);
    return 0.0;
  }
  celula->visitada = 1;

  switch (celula->tipo)
  {
  case TIPO_VAZIA:
    celula->valor = 0.0;
    break;
  case TIPO_NUMERO:
    celula->valor = atof(celula->input);
    break;
  case TIPO_REFERENCIA:
  {
    int indice_dep = parse_nome_celula(celula->input + 1);
    celula->valor = (indice_dep != -1) ? calcular_celula(indice_dep) : 0.0;
    break;
  }
  case TIPO_FUNCAO:
  {
    char *nome_funcao = celula->input + 1;
    char *range_str = strchr(celula->input, '(');
    celula->valor = range_str ? executar_funcao(nome_funcao, range_str + 1) : 0.0;
    break;
  }
  }
  celula->visitada = 2;
  return celula->valor;
}

int parse_nome_celula(const char *str)
{
  if (!str || strlen(str) < 2)
    return -1;
  char col = str[0];
  int row = atoi(&str[1]);
  return get_indice_celula(col, row);
}

void inicializar_planilha(void)
{
  for (int i = 0; i < NUM_CELLS; i++)
  {
    if (planilha[i].input)
    {
      free(planilha[i].input);
      planilha[i].input = NULL;
    }
    planilha[i].valor = 0.0;
    planilha[i].tipo = TIPO_VAZIA;
    planilha[i].visitada = 0;
    for (int j = 0; j < NUM_CELLS; j++)
    {
      grafo_adj[i][j] = 0;
    }
  }
}

void limpar_planilha(void)
{
  for (int i = 0; i < NUM_CELLS; i++)
  {
    if (planilha[i].input)
    {
      free(planilha[i].input);
      planilha[i].input = NULL;
    }
  }
}

void atualizar_celula(int indice, const char *input)
{

  if (planilha[indice].input)
  {
    free(planilha[indice].input);
  }

  for (int j = 0; j < NUM_CELLS; j++)
  {
    grafo_adj[indice][j] = 0;
  }

  char input_limpo[128];
  int j = 0;
  for (int i = 0; input[i]; i++)
  {
    if (!isspace(input[i]))
    {
      input_limpo[j++] = input[i];
    }
  }
  input_limpo[j] = '\0';

  planilha[indice].input = strdup(input_limpo);

  if (planilha[indice].input[0] == '@')
  {
    planilha[indice].tipo = TIPO_FUNCAO;
    char *range_str = strchr(planilha[indice].input, '(');
    if (range_str)
    {

      adicionar_dependencias_range(indice, range_str + 1);
    }
  }
  else if (planilha[indice].input[0] == '=')
  {
    planilha[indice].tipo = TIPO_REFERENCIA;

    int indice_dep = parse_nome_celula(&planilha[indice].input[1]);
    if (indice_dep != -1)
    {
      grafo_adj[indice][indice_dep] = 1;
    }
  }
  else if (isdigit(planilha[indice].input[0]) || (planilha[indice].input[0] == '-' && isdigit(planilha[indice].input[1])))
  {
    planilha[indice].tipo = TIPO_NUMERO;
  }
  else
  {
    planilha[indice].tipo = TIPO_VAZIA;
  }
}

void calcular_tudo(void)
{
  for (int i = 0; i < NUM_CELLS; i++)
  {
    planilha[i].visitada = 0;
  }
  for (int i = 0; i < NUM_CELLS; i++)
  {
    if (planilha[i].tipo != TIPO_VAZIA)
    {
      calcular_celula(i);
    }
  }
}

void exibir_planilha(void)
{
  printf("\n     ");
  for (int c = 0; c < NUM_COLS; c++)
    printf("%-11c", 'A' + c);
  printf("\n     +");
  for (int c = 0; c < NUM_COLS; c++)
    printf("----------+");
  printf("\n");

  for (int r = 0; r < NUM_ROWS; r++)
  {
    printf("%-5d|", r + 1);
    for (int c = 0; c < NUM_COLS; c++)
    {
      int indice = get_indice_celula('A' + c, r + 1);
      if (planilha[indice].tipo == TIPO_VAZIA)
      {
        printf("          |");
      }
      else
      {
        printf("%-10.2f|", planilha[indice].valor);
      }
    }
    printf("\n");
  }
  printf("\n");
}

NoDependencia *get_lista_adjacencia(int indice)
{
  if (indice < 0 || indice >= NUM_CELLS)
    return NULL;

  NoDependencia *cabeca_lista = NULL;
  NoDependencia *cauda_lista = NULL;

  for (int j = 0; j < NUM_CELLS; j++)
  {
    if (grafo_adj[indice][j] == 1)
    {

      NoDependencia *novo_no = (NoDependencia *)malloc(sizeof(NoDependencia));
      if (!novo_no)
        continue;
      novo_no->indice_dependencia = j;
      novo_no->proximo = NULL;

      if (cabeca_lista == NULL)
      {

        cabeca_lista = novo_no;
        cauda_lista = novo_no;
      }
      else
      {

        cauda_lista->proximo = novo_no;
        cauda_lista = novo_no;
      }
    }
  }

  return cabeca_lista;
}

void free_lista_adjacencia(NoDependencia *lista)
{

  NoDependencia *atual = lista;
  while (atual != NULL)
  {
    NoDependencia *proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }
}