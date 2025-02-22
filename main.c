#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h"


// Função para verificar a senha do modo admin
int verificar_senha() {
    char senha[6];
    printf("Digite a senha para acessar o Modo Admin: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0'; // Remover o caractere de nova linha

    if (strcmp(senha, "12345") == 0) {
        return 1; // Senha correta
    } else {
        printf("Senha incorreta! Acesso negado.\n");
        return 0; // Senha incorreta
    }
}

int main() {
 
    Pista pistas[MAX_PISTAS];
    Premio premios[MAX_PREMIOS];

    carregar_palavras(pistas);

    int escolha;
    do {

        system("clear");
      
        printf("\nMenu do Jogo de Roda a Roda\n");
        printf("1. Iniciar o jogo\n");
        printf("2. Modo Admin\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer do teclado

        switch (escolha) {
            case 1:
                  system("clear");
                  jogar(pistas);
                  break;
            case 2:
                if (verificar_senha()) {
                    int opcao_admin;
                    do {
                        printf("\nModo Admin\n");
                        printf("1. Cadastrar Palavra\n");
                        printf("2. Mostrar Palavras\n");
                        printf("3. Cadastrar Prêmios\n");
                        printf("4. Ver Prêmios\n");
                        printf("5. Voltar ao menu principal\n");
                        printf("Escolha uma opção: ");
                        scanf("%d", &opcao_admin);
                        getchar(); // Limpa o buffer do teclado

                        switch (opcao_admin) {
                            case 1:
                                printf("Configurando as palavras...\n");
                                configurar_palavras(pistas);
                                cadastrar_palavras(pistas);
                                break;
                            case 2:
                                printf("Exibindo palavras cadastradas...\n");
                                exibir_palavras_carregadas(pistas);
                                break;
                            case 3:
                                printf("Cadastrando prêmios...\n");
                                cadastrar_premios(premios);
                                break;
                            case 4:
                                printf("Exibindo prêmios cadastrados...\n");
                                exibir_premios(premios);
                                break;
                            case 5:
                                printf("Voltando ao menu principal...\n");
                                break;
                            default:
                                printf("Opção inválida! Tente novamente.\n");
                        }
                    } while (opcao_admin != 5);
                }
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (escolha != 3);

    return 0;
}
