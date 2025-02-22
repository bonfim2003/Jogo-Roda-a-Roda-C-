// cadastrarpalavra.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h"

// Função para configurar as palavras
void configurar_palavras(Pista pistas[MAX_PISTAS]) {
    for (int i = 0; i < MAX_PISTAS; i++) {
        pistas[i].num_palavras = 0; // Inicializa o contador de palavras

        printf("\nConfiguração da Pista %d:\n", i + 1);
        printf("Digite o nome da Pista (máximo de %d caracteres): ", MAX_TAMANHO_NOME_PISTA);
        fgets(pistas[i].nome, sizeof(pistas[i].nome), stdin);
        pistas[i].nome[strcspn(pistas[i].nome, "\n")] = '\0';

        int opcao = 0;
        while (1) {
            printf("Quantas palavras deseja adicionar à pista '%s' (máximo de %d)? ", pistas[i].nome, MAX_PALAVRAS_POR_PISTA);
            scanf("%d", &opcao);
            getchar();

            if (opcao <= 0) {
                printf("Saindo... Nenhuma palavra adicionada.\n");
                break;
            } else if (opcao > MAX_PALAVRAS_POR_PISTA) {
                printf("Máximo de %d palavras por pista. Tente novamente.\n", MAX_PALAVRAS_POR_PISTA);
            } else {
                break;
            }
        }

        for (int j = 0; j < opcao; j++) {
            printf("Digite a palavra %d (máximo de %d caracteres): ", j + 1, MAX_TAMANHO_PALAVRA);
            char palavra[MAX_TAMANHO_PALAVRA + 1];
            fgets(palavra, sizeof(palavra), stdin);
            palavra[strcspn(palavra, "\n")] = '\0';

            if (strlen(palavra) > MAX_TAMANHO_PALAVRA) {
                printf("Palavra muito longa, tente novamente.\n");
                j--;
                continue;
            }

            strcpy(pistas[i].palavras[j], palavra);
            pistas[i].num_palavras++;
        }
    }
}

// Função para salvar as palavras no arquivo
void cadastrar_palavras(Pista pistas[MAX_PISTAS]) {
    FILE *arquivo = fopen("palavras.dat", "wb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < MAX_PISTAS; i++) {
        fwrite(&pistas[i].num_palavras, sizeof(int), 1, arquivo);
        fwrite(pistas[i].nome, sizeof(char), MAX_TAMANHO_NOME_PISTA, arquivo);
        for (int j = 0; j < pistas[i].num_palavras; j++) {
            fwrite(pistas[i].palavras[j], sizeof(char), MAX_TAMANHO_PALAVRA, arquivo);
        }
    }

    fclose(arquivo);
    printf("\nPalavras salvas no arquivo 'palavras.dat'.\n");
}
