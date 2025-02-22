#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>    // Necessário para a função sleep() (em sistemas POSIX)
#include "palavras.h"  // Certifique-se de que este header define:
//                      MAX_PREMIOS, MAX_PISTAS, MAX_PALAVRAS_POR_PISTA, MAX_TAMANHO_PALAVRA,
//                      além das structs Pista e Premio.


// Função para carregar os prêmios do arquivo "premios.dat"
void carregar_premios(Premio premios[MAX_PREMIOS], int *num_premios) {
    FILE *arquivo = fopen("premios.dat", "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de prêmios.\n");
        return;
    }
    fread(num_premios, sizeof(int), 1, arquivo);
    for (int i = 0; i < *num_premios; i++) {
        fread(&premios[i], sizeof(Premio), 1, arquivo);
    }
    fclose(arquivo);
}

// Função para sortear um prêmio (a semente do random já é definida uma vez)
float sortear_premio(Premio premios[MAX_PREMIOS], int num_premios) {
    if (num_premios == 0) {
        printf("Nenhum prêmio cadastrado.\n");
        return 0.0f;
    }
    int indice = rand() % num_premios;
    return premios[indice].valor;
}

// Função para pedir os nomes dos jogadores
void pedir_nomes_jogadores(char jogadores[3][50]) {
    for (int i = 0; i < 3; i++) {
        printf("Digite o nome do Jogador %d: ", i + 1);
        fgets(jogadores[i], 50, stdin);
        jogadores[i][strcspn(jogadores[i], "\n")] = '\0';  // Remove a quebra de linha
    }
}

// Função para exibir a pista e o estado atual das palavras
void mostrar_palavra_atual(const char *pista, char palavra[MAX_PALAVRAS_POR_PISTA][MAX_TAMANHO_PALAVRA + 1], int num_palavras) {
    printf("\nPista: %s\n", pista);
    for (int i = 0; i < num_palavras; i++) {
        printf("Palavra %d: ", i + 1);
        for (int j = 0; j < strlen(palavra[i]); j++) {
            printf("%c ", palavra[i][j]);
        }
        printf("\n");
    }
}

// Função para exibir os saldos dos jogadores em formato de tabela.
// Se 'vencedor' for >= 0, a coluna correspondente exibirá "VENCEDOR" abaixo do saldo.
void mostrar_saldos(const char jogadores[3][50], float saldo[3], int vencedor) {
    printf("\n%-20s %-20s %-20s\n", jogadores[0], jogadores[1], jogadores[2]);
    printf("%-20s %-20s %-20s\n", "==================", "==================", "==================");
    printf("R$ %-17.2f R$ %-17.2f R$ %-17.2f\n", saldo[0], saldo[1], saldo[2]);
    if (vencedor >= 0 && vencedor < 3) {
        printf("%-20s %-20s %-20s\n", 
            (vencedor == 0 ? "VENCEDOR" : ""), 
            (vencedor == 1 ? "VENCEDOR" : ""), 
            (vencedor == 2 ? "VENCEDOR" : ""));
    }
}

// Função principal do jogo
void jogar(Pista pistas[MAX_PISTAS]) {
    char jogadores[3][50];
    float saldo[3] = {0.0f, 0.0f, 0.0f};
    int bonusAttempted[3] = {0, 0, 0};  // Controla se o jogador já tentou a rodada bônus

    // Carregar os prêmios
    Premio premios[MAX_PREMIOS];
    int num_premios = 0;
    carregar_premios(premios, &num_premios);

    // Pedir os nomes dos jogadores
    pedir_nomes_jogadores(jogadores);

    // Inicializa a semente do random apenas uma vez
    srand(time(NULL));

    // Sorteia uma pista aleatória e inicializa as palavras ocultas
    int indice_pista = rand() % MAX_PISTAS;
    char palavra[MAX_PALAVRAS_POR_PISTA][MAX_TAMANHO_PALAVRA + 1];
    for (int i = 0; i < pistas[indice_pista].num_palavras; i++) {
        strcpy(palavra[i], pistas[indice_pista].palavras[i]);
        for (int j = 0; j < strlen(palavra[i]); j++) {
            palavra[i][j] = '_';
        }
    }


    int jogador_atual = 0;
    int vencedor = -1;  // Se houver vencedor na rodada bônus, armazena seu índice
    char letra;

    // Loop principal do jogo
    while (1) {
        // Exibe sempre a pista e os saldos atualizados
        mostrar_palavra_atual(pistas[indice_pista].nome, palavra, pistas[indice_pista].num_palavras);
        mostrar_saldos(jogadores, saldo, -1);

        // Verifica se faltam apenas 3 letras para completar todas as palavras
        int totalUnderscores = 0;
        for (int i = 0; i < pistas[indice_pista].num_palavras; i++) {
            for (int j = 0; j < strlen(palavra[i]); j++) {
                if (palavra[i][j] == '_')
                    totalUnderscores++;
            }
        }
        if (totalUnderscores == 3) {
            if (bonusAttempted[jogador_atual]) {
                jogador_atual = (jogador_atual + 1) % 3;
                if (bonusAttempted[0] && bonusAttempted[1] && bonusAttempted[2]) {
                    printf("\nTodos os jogadores erraram na rodada bônus. O jogo terminou.\n");
                    break;
                }
                continue;
            }
            printf("\nFaltam 3 letras para completar a palavra.\n");
            saldo[jogador_atual] += 1000.00;
            printf("Valendo R$%.2f, a palavra é:\n", saldo[jogador_atual]);
            // Countdown de 5 segundos
            for (int count = 5; count >= 1; count--) {
                printf("Digite em %d...\n", count);
                sleep(1);
            }
            int bonus_success = 1;
            char resposta[MAX_TAMANHO_PALAVRA + 1];
            for (int i = 0; i < pistas[indice_pista].num_palavras; i++) {
                printf("Digite a palavra %d: ", i + 1);
                scanf("%s", resposta);
                if (strcmp(resposta, pistas[indice_pista].palavras[i]) != 0) {
                    bonus_success = 0;
                    break;
                }
            }
            bonusAttempted[jogador_atual] = 1;
            if (bonus_success) {
                vencedor = jogador_atual;
                printf("VENCEDOR!\n");
                break;
            } else {
                printf("Você errou, próximo jogador!\n");
                jogador_atual = (jogador_atual + 1) % 3;
                if (bonusAttempted[0] && bonusAttempted[1] && bonusAttempted[2]) {
                    printf("\nTodos os jogadores erraram na rodada bônus. O jogo terminou.\n");
                    break;
                }
                continue;
            }
        }

        // Rodada normal
        printf("\nJogador %s, seu saldo é R$ %.2f\n", jogadores[jogador_atual], saldo[jogador_atual]);
        float premio = sortear_premio(premios, num_premios);

        // Validação dos prêmios especiais
        if (premio == 0.00f) {
            printf("Perdeu a vez, próximo jogador!\n");
            jogador_atual = (jogador_atual + 1) % 3;
            continue;
        }
        if (premio == 0.01f) {
            printf("Perdeu tudo!\n");
            saldo[jogador_atual] = 0.01f;
            // O jogador continua nesta rodada
        }

        printf("Valendo R$%.2f, digite uma letra: ", premio);
        scanf(" %c", &letra);
        char letra_jogada = toupper(letra);

        int letras_acertadas = 0;
        // Verifica se a letra digitada está nas palavras (comparação case-insensitive)
        for (int i = 0; i < pistas[indice_pista].num_palavras; i++) {
            for (int j = 0; j < strlen(pistas[indice_pista].palavras[i]); j++) {
                if (toupper(pistas[indice_pista].palavras[i][j]) == letra_jogada && palavra[i][j] == '_') {
                    palavra[i][j] = pistas[indice_pista].palavras[i][j];  // Revela a letra correta
                    letras_acertadas++;
                    saldo[jogador_atual] += premio;
                }
            }
        }

        if (letras_acertadas > 0) {
            printf("Você acertou a letra '%c'!\n", letra_jogada);
        } else {
            printf("Não existe a letra '%c' nas palavras, próximo jogador!\n", letra_jogada);
            jogador_atual = (jogador_atual + 1) % 3;
        }

        // Verifica se todas as palavras foram completadas
        int acertos = 0;
        for (int i = 0; i < pistas[indice_pista].num_palavras; i++) {
            if (strchr(palavra[i], '_') == NULL)
                acertos++;
        }
        if (acertos == pistas[indice_pista].num_palavras) {
            printf("\nParabéns! O jogo acabou. Todas as palavras foram descobertas.\n");
            break;
        }
    } // fim do while principal

    // Exibe os saldos finais (se houver vencedor, exibe "VENCEDOR" abaixo do saldo)
    mostrar_saldos(jogadores, saldo, vencedor);

    // Revela as palavras
    printf("\nAs palavras eram:\n");
    for (int i = 0; i < pistas[indice_pista].num_palavras; i++) {
        printf("Palavra %d: %s\n", i + 1, pistas[indice_pista].palavras[i]);
    }
    printf("\nPressione qualquer tecla para voltar ao menu.\n");
    getchar();  // Captura o '\n' remanescente
    getchar();  // Aguarda o pressionamento de uma tecla
}
