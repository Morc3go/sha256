#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// FUNÇÃO PARA PADDING
char* padding(char *mensagem) {
    int tamanho = strlen(mensagem);
    
    // Realloc para 64 bytes
    char *novaMensagem = realloc(mensagem, 64);
    if (novaMensagem == NULL) {
        perror("Erro ao realocar memória");
        exit(EXIT_FAILURE);
    }

    // Adiciona 0x80 logo após a mensagem original
    novaMensagem[tamanho] = 0x80;
    
    // Preenche com 0 até o byte 56
    for (int i = tamanho + 1; i < 56; i++) {
        novaMensagem[i] = 0x00;
    }

    // Adiciona o tamanho original da mensagem em bits (big-endian)
    uint64_t tamanho_bits = tamanho * 8;
    for (int i = 0; i < 8; i++) {
        novaMensagem[63 - i] = (tamanho_bits >> (8 * i)) & 0xFF;
    }

    return novaMensagem;
}

// FUNÇÃO PARA EXIBIR O BINÁRIO
void transformarBinario(char *mensagem, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (mensagem[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    // Aloca espaço inicial para "sla" (3 caracteres + 1 para \0)
    char *mensagem = malloc(4);
    if (mensagem == NULL) {
        perror("Erro ao alocar memória");
        return EXIT_FAILURE;
    }

    strcpy(mensagem, "sla");

    mensagem = padding(mensagem);
    transformarBinario(mensagem, 64);

    free(mensagem);
    return 0;
}
