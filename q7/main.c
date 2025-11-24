#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashing.h"    



void menu() {
    printf("\n===========================================\n");
    printf("   TRABALHO DE ESTRUTURAS DE DADOS II\n");
    printf("===========================================\n");
    printf("1.  Simulacao de Tabela Hashing (Q7)\n");
    printf("0. Sair\n");
    printf("-------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int escolha;
    
    // Define a localização para garantir que o tempo funcione corretamen

    do {
        menu();
        if (scanf("%d", &escolha) != 1) {
            // Limpa o buffer em caso de entrada não numérica
            while (getchar() != '\n'); 
            escolha = -1; 
            printf("\nEntrada invalida. Por favor, digite um numero.\n");
            continue;
        }
        printf("\n");

        switch (escolha) {
            case 1:
                printf("Executando Questão 7:\n");
                simular_e_comparar_hashing();
                break;
            case 0:
                printf("Saindo do programa. Tchau!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        printf("\n--- FIM DA EXECUCAO ---\n");
    } while (escolha != 0);

    return 0;
}