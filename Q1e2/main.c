#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Incluir os cabeçalhos dos módulos
#include "hanoi.h" 
//#include "planilha.h" // Para as questões 3, 4, 5


void menu() {
    printf("===========================================\n");
    printf("   TRABALHO DE ESTRUTURAS DE DADOS II\n");
    printf("===========================================\n");
    printf("1.  Torre de Hanoi (4 Discos) - Matriz (Q1)\n");
    printf("2.  Torre de Hanoi (4 Discos) - Lista (Q2)\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int escolha;



    do {
        menu();
        scanf("%d", &escolha);
        printf("\n");

        switch (escolha) {
            case 1:
                // Chamada da Questão 1
                resolver_hanoi_matriz(); 
                break;
            case 2:
                // Chamada da Questão 2
                resolver_hanoi_lista(); 
                break;
            case 0:
                printf("Saindo do programa. Tchau!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        printf("\n");
    } while (escolha != 0);

    return 0;
}