// cadastrarpremio.c
#include <stdio.h>
#include <stdlib.h>
#include "palavras.h"

// Função para cadastrar prêmios (apenas com o valor)
void cadastrar_premios(Premio premios[MAX_PREMIOS]) {
    int num_premios = 0;

    // Lê a quantidade de prêmios a serem cadastrados
    while (num_premios < MAX_PREMIOS) {
        printf("\nDigite o valor do prêmio (em reais): ");
        scanf("%f", &premios[num_premios].valor);
        getchar();  // Limpa o buffer do teclado

        num_premios++;

        // Pergunta se deseja cadastrar mais prêmios
        char opcao;
        printf("Deseja cadastrar outro prêmio? (S/N): ");
        scanf("%c", &opcao);
        getchar();  // Limpa o buffer do teclado

        if (opcao == 'N' || opcao == 'n') {
            break;
        }
    }

    // Salva os prêmios no arquivo
    FILE *arquivo = fopen("premios.dat", "wb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para salvar os prêmios.\n");
        return;
    }

    fwrite(&num_premios, sizeof(int), 1, arquivo);
    for (int i = 0; i < num_premios; i++) {
        fwrite(&premios[i], sizeof(Premio), 1, arquivo);
    }

    fclose(arquivo);
    printf("\nPrêmios cadastrados com sucesso!\n");
}
