// mostarpalavra.c
#include <stdio.h>
#include <stdlib.h>
#include "palavras.h"

// Função para exibir as palavras cadastradas
void exibir_palavras_carregadas(Pista pistas[MAX_PISTAS]) {
    FILE *arquivo = fopen("palavras.dat", "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    for (int i = 0; i < MAX_PISTAS; i++) {
        fread(&pistas[i].num_palavras, sizeof(int), 1, arquivo);
        fread(pistas[i].nome, sizeof(char), MAX_TAMANHO_NOME_PISTA, arquivo);
        printf("\nPista: %s\n", pistas[i].nome);
        for (int j = 0; j < pistas[i].num_palavras; j++) {
            fread(pistas[i].palavras[j], sizeof(char), MAX_TAMANHO_PALAVRA, arquivo);
            printf("- %s\n", pistas[i].palavras[j]);
        }
    }

    fclose(arquivo);
}
