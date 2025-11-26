#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// -------------------- STRUCT --------------------
// Representa uma peça do Tetris Stack
typedef struct {
    char nome;  // Tipo da peça (I, O, T, L)
    int id;     // Identificador único
} Peca;

// -------------------- VARIÁVEIS GLOBAIS --------------------
int idGlobal = 0;  // controla o ID único das peças

// -------------------- GERAR NOVA PEÇA --------------------
Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = idGlobal++;
    return nova;
}

// -------------------- MOSTRAR ESTADO --------------------
void mostrarEstado(Peca fila[], int inicio, int fim, int qtdFila, Peca pilha[], int topo) {
    printf("\n================== ESTADO ATUAL ==================\n");

    // Fila
    printf("Fila de peças: ");
    if (qtdFila == 0) {
        printf("(vazia)");
    } else {
        int i = inicio;
        for (int c = 0; c < qtdFila; c++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAM_FILA;
        }
    }

    // Pilha
    printf("\nPilha de reserva (Topo -> Base): ");
    if (topo == -1) {
        printf("(vazia)");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n===================================================\n");
}

// -------------------- ENQUEUE --------------------
void enqueue(Peca fila[], int *fim, int *qtdFila) {
    if (*qtdFila == TAM_FILA) {
        return;  // Fila sempre cheia, não precisa inserir manualmente
    }

    *fim = (*fim + 1) % TAM_FILA;
    fila[*fim] = gerarPeca();
    (*qtdFila)++;
}

// -------------------- DEQUEUE --------------------
Peca dequeue(Peca fila[], int *inicio, int *qtdFila) {
    Peca removida = fila[*inicio];
    *inicio = (*inicio + 1) % TAM_FILA;
    (*qtdFila)--;
    return removida;
}

// -------------------- PUSH --------------------
void push(Peca pilha[], int *topo, Peca p) {
    (*topo)++;
    pilha[*topo] = p;
}

// -------------------- POP --------------------
Peca pop(Peca pilha[], int *topo) {
    Peca retirada = pilha[*topo];
    (*topo)--;
    return retirada;
}

// -------------------- TROCA SIMPLES --------------------
void trocarUma(Peca fila[], int inicio, Peca pilha[], int topo) {
    Peca temp = fila[inicio];
    fila[inicio] = pilha[topo];
    pilha[topo] = temp;
}

// -------------------- TROCA MÚLTIPLA --------------------
void trocarTres(Peca fila[], int inicio, Peca pilha[]) {
    for (int i = 0; i < 3; i++) {
        Peca temp = fila[(inicio + i) % TAM_FILA];
        fila[(inicio + i) % TAM_FILA] = pilha[2 - i];
        pilha[2 - i] = temp;
    }
}

// -------------------- MAIN --------------------
int main() {
    srand(time(NULL));

    // -------------------- Fila --------------------
    Peca fila[TAM_FILA];
    int inicio = 0, fim = -1, qtdFila = 0;

    // Inicializa fila cheia
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(fila, &fim, &qtdFila);
    }

    // -------------------- Pilha --------------------
    Peca pilha[TAM_PILHA];
    int topo = -1;

    int opcao;

    do {
        mostrarEstado(fila, inicio, fim, qtdFila, pilha, topo);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Reservar peça (fila -> pilha)\n");
        printf("3 - Usar peça reservada (pop)\n");
        printf("4 - Trocar frente da fila com topo da pilha\n");
        printf("5 - Trocar 3 peças da fila com 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1: // Jogar peça
                dequeue(fila, &inicio, &qtdFila);
                enqueue(fila, &fim, &qtdFila);
                break;

            case 2: // Reservar peça
                if (topo < TAM_PILHA - 1) {
                    Peca removida = dequeue(fila, &inicio, &qtdFila);
                    push(pilha, &topo, removida);
                    enqueue(fila, &fim, &qtdFila);
                } else {
                    printf("\nA pilha está cheia!\n");
                }
                break;

            case 3: // Usar peça da reserva
                if (topo >= 0) {
                    pop(pilha, &topo);
                } else {
                    printf("\nA pilha está vazia!\n");
                }
                break;

            case 4: // Troca simples
                if (topo >= 0) {
                    trocarUma(fila, inicio, pilha, topo);
                } else {
                    printf("\nNão há peça na pilha para trocar!\n");
                }
                break;

            case 5: // Troca múltipla
                if (topo == 2) {
                    trocarTres(fila, inicio, pilha);
                } else {
                    printf("\nÉ necessário ter 3 peças na pilha!\n");
                }
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
