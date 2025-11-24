## planilhas

cd planilha

gcc main.c planilha_matrix_adjacencias.c -o planilha_matrix

gcc main.c planilha_lista_adjacencias.c -o planilha_lista


## buscas 

gcc main_buscas.c planilha_matrix_adjacencias.c buscas_matriz.c -o buscas_matriz

gcc main_buscas.c planilha_lista_adjacencias.c buscas_lista.c -o buscas_lista

## testes

gcc main_teste_tempo.c planilha_matrix_adjacencias.c buscas_matriz.c -o teste_matriz

gcc main_teste_tempo.c planilha_lista_adjacencias.c buscas_lista.c -o teste_lista 
