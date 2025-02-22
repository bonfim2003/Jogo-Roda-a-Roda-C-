// palavras.h
#ifndef PALAVRAS_H
#define PALAVRAS_H

#define MAX_PISTAS 5
#define MAX_PALAVRAS_POR_PISTA 3
#define MAX_TAMANHO_PALAVRA 17
#define MAX_TAMANHO_NOME_PISTA 30
#define MAX_PREMIOS 12

typedef struct {
    char nome[MAX_TAMANHO_NOME_PISTA + 1];
    char palavras[MAX_PALAVRAS_POR_PISTA][MAX_TAMANHO_PALAVRA + 1];
    int num_palavras;
} Pista;

typedef struct {
    float valor;
    char descricao[50];  // Descrição do prêmio
} Premio;

void configurar_palavras(Pista pistas[MAX_PISTAS]);
void salvar_palavras(Pista pistas[MAX_PISTAS]);
void exibir_palavras_carregadas(Pista pistas[MAX_PISTAS]);

void cadastrar_premios(Premio premios[MAX_PREMIOS]);
void exibir_premios(Premio premios[MAX_PREMIOS]);

void carregar_palavras(Pista pistas[MAX_PISTAS]);
void salvar_palavras(Pista pistas[MAX_PISTAS]);

#endif
