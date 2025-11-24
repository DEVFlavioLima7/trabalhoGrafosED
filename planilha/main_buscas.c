#include <stdio.h>
#include <string.h>
#include "planilha.h"
#include "buscas.h"

void pausar_e_limpar_buffer()
{
  printf("Pressione Enter para continuar...\n");

  getchar();
}

int main()
{
  char input_buffer[256];
  char comando_ou_celula[10];
  char argumento_ou_valor[252];

  int resultados_busca[NUM_CELLS];
  char nome_celula_temp[4];

  inicializar_planilha();

  while (1)
  {
    exibir_planilha();
    printf("Digite a celula e o valor (ex: A1 10, C1 =B1)\n");
    printf("Ou um comando de busca (ex: bfs C1, dfs C1)\n");
    printf("Ou digite 'sair' para terminar.\n");
    printf("> ");

    if (!fgets(input_buffer, sizeof(input_buffer), stdin))
    {
      break;
    }
    input_buffer[strcspn(input_buffer, "\n")] = 0;

    if (strcmp(input_buffer, "sair") == 0)
    {
      break;
    }

    int n = sscanf(input_buffer, "%9s %251[^\n]", comando_ou_celula, argumento_ou_valor);

    if (n == 2)
    {
      if (strcmp(comando_ou_celula, "bfs") == 0)
      {
        int indice = parse_nome_celula(argumento_ou_valor);
        if (indice != -1)
        {

          printf("BFS a partir de %s:\n", argumento_ou_valor);

          int num_encontrados = buscar_bfs(indice, resultados_busca);

          for (int i = 0; i < num_encontrados; i++)
          {
            get_nome_celula(resultados_busca[i], nome_celula_temp);
            printf("%s ", nome_celula_temp);
          }
          printf("\nFim da busca.\n\n");

          pausar_e_limpar_buffer();
        }
        else
        {
          printf("Uso invalido. Tente: bfs A1\n");
        }
        continue;
      }

      if (strcmp(comando_ou_celula, "dfs") == 0)
      {
        int indice = parse_nome_celula(argumento_ou_valor);
        if (indice != -1)
        {

          printf("DFS a partir de %s:\n", argumento_ou_valor);

          int num_encontrados = buscar_dfs(indice, resultados_busca);

          for (int i = 0; i < num_encontrados; i++)
          {
            get_nome_celula(resultados_busca[i], nome_celula_temp);
            printf("%s ", nome_celula_temp);
          }
          printf("\nFim da busca.\n\n");

          pausar_e_limpar_buffer();
        }
        else
        {
          printf("Uso invalido. Tente: dfs A1\n");
        }
        continue;
      }

      int indice = parse_nome_celula(comando_ou_celula);
      if (indice == -1)
      {
        printf("Celula ou comando invalido: %s\n", comando_ou_celula);
        continue;
      }
      atualizar_celula(indice, argumento_ou_valor);
      calcular_tudo();
    }
    else if (n == 1)
    {
      printf("Comando incompleto ou formato invalido.\n");
      printf("Tente 'A1 10' ou 'bfs C1'.\n");
    }
    else
    {
      continue;
    }
  }

  limpar_planilha();
  printf("Ate logo!\n");
  return 0;
}