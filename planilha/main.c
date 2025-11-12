#include <stdio.h>
#include <string.h>
#include "planilha.h"

int main()
{
  char input_buffer[256];
  char celula_nome[4];
  char celula_valor[252];

  inicializar_planilha();

  while (1)
  {
    exibir_planilha();

    printf("Digite a celula e o valor (ex: A1 10, C1 =B1)\n");
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

    if (sscanf(input_buffer, "%3s %251[^\n]", celula_nome, celula_valor) < 2)
    {
      printf("Formato invalido. Tente 'A1 10' ou 'B2 =C3'.\n");
      continue;
    }

    int indice = parse_nome_celula(celula_nome);

    if (indice == -1)
    {
      printf("Celula invalida: %s\n", celula_nome);
      continue;
    }

    atualizar_celula(indice, celula_valor);
    calcular_tudo();
  }

  limpar_planilha();

  printf("Ate logo!\n");
  return 0;
}