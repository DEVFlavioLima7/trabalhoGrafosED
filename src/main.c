#include <stdio.h>
#include <stdlib.h>
#include "torre_hanoi.h"
#include "planilha.h"

void menu_torre_de_hanoi() {
    int n;
    printf("Digite o número de discos para a Torre de Hanói: ");
    scanf("%d", &n);
    printf("\nResolvendo o problema da Torre de Hanói para %d discos:\n", n);
    torre_de_hanoi(n, 'A', 'C', 'B');  // Resolver Torre de Hanói recursivamente
}

void menu_planilha() {
    int opcao;
    Celula planilha[20][8];
    inicializar_planilha(planilha);

    while (1) {
        printf("\n----- Menu Planilha -----\n");
        printf("1. Inserir valor em uma célula\n");
        printf("2. Inserir fórmula em uma célula\n");
        printf("3. Exibir planilha\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                {
                    char nome[3];
                    double valor;
                    printf("Digite o nome da célula (Ex: A1): ");
                    scanf("%s", nome);
                    printf("Digite o valor: ");
                    scanf("%lf", &valor);
                    inserir_valor(planilha, nome, valor);
                }
                break;
            
            case 2:
                {
                    char nome[3], formula[50];
                    printf("Digite o nome da célula (Ex: A1): ");
                    scanf("%s", nome);
                    printf("Digite a fórmula (Ex: =B1): ");
                    scanf("%s", formula);
                    inserir_formula(planilha, nome, formula);
                }
                break;
            
            case 3:
                exibir_planilha(planilha);
                break;
            
            case 4:
                return;  // Voltar ao menu principal
            
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }
}

int main() {
    int opcao;

    while (1) {
        // Exibir menu principal
        printf("\n----- Menu Principal -----\n");
        printf("1. Resolver o problema da Torre de Hanói\n");
        printf("2. Acessar a Planilha de Cálculo\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menu_torre_de_hanoi();  // Chama a função para resolver a Torre de Hanói
                break;
            
            case 2:
                menu_planilha();  // Chama a função da planilha de cálculo
                break;
            
            case 3:
                printf("Saindo...\n");
                exit(0);  // Sai do programa
                break;
            
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
