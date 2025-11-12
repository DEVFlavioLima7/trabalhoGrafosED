## planilhas

gcc main.c planilha_matrix_adjacencias.c -o planilha

gcc main.c planilha_lista_adjacencias.c -o planilha


## buscas 

gcc main_buscas.c planilha_matrix_adjacencias.c buscas.c -o busca_lista

gcc main_buscas.c planilha_lista_adjacencias.c buscas.c -o busca_matriz

## testes

gcc main_teste_tempo.c planilha_lista_adjacencias.c buscas.c -o teste_lista 

gcc main_teste_tempo.c planilha_matrix_adjacencias.c buscas.c -o teste_matriz