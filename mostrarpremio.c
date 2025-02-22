// mostrarpremio.c
#include <stdio.h>
#include <stdlib.h>
#include "palavras.h"

// Função para exibir prêmios
void exibir_premios(Premio premios[MAX_PREMIOS]) {
    FILE *arquivo = fopen("premios.dat", "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para leitura dos prêmios.\n");
        return;
    }

    int num_premios;
    fread(&num_premios, sizeof(int), 1, arquivo);

    if (num_premios == 0) {
        printf("Nenhum prêmio cadastrado ainda.\n");
    } else {
        printf("\nLista de Prêmios (apenas valores):\n");
        for (int i = 0; i < num_premios; i++) {
            fread(&premios[i], sizeof(Premio), 1, arquivo);
            printf("%d. R$ %.2f\n", i + 1, premios[i].valor);
        }
    }

    fclose(arquivo);
}
