#ifndef PLANILHA_H_
#define PLANILHA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

#define NUM_COLS 8
#define NUM_ROWS 20
#define NUM_CELLS (NUM_COLS * NUM_ROWS)

typedef struct NoDependencia
{
  int indice_dependencia;
  struct NoDependencia *proximo;
} NoDependencia;

typedef enum
{
  TIPO_VAZIA,
  TIPO_NUMERO,
  TIPO_REFERENCIA,
  TIPO_FUNCAO
} TipoCelula;

typedef struct
{
  char *input;
  double valor;
  TipoCelula tipo;
  int visitada;
} Celula;

void inicializar_planilha(void);
void limpar_planilha(void);
void atualizar_celula(int indice, const char *input);
void calcular_tudo(void);
void exibir_planilha(void);
int parse_nome_celula(const char *str);

NoDependencia *get_lista_adjacencia(int indice);

void free_lista_adjacencia(NoDependencia *lista);
void get_nome_celula(int indice, char *nome);

#endif