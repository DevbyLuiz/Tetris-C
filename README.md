# Tetris Stack – Gerenciador de Peças (Fila + Pilha)

Trabalho do 2º semestre. O objetivo é simular o sistema de peças do jogo Tetris Stack usando uma **fila circular** e uma **pilha de reserva**. A fila sempre fica cheia e as peças são geradas automaticamente.

## Funcionalidades
- Jogar peça (remove da fila)
- Reservar peça (fila → pilha)
- Usar peça reservada (pilha → fora do jogo)
- Trocar peça da fila com a da pilha
- Trocar as 3 primeiras peças da fila com as 3 da pilha
- Visualizar fila e pilha

## Estruturas usadas
- `struct Peca`
- Fila circular (5 posições)
- Pilha (3 posições)
- Funções simples para organizar o código

## Como executar
```bash
gcc tetris.c -o tetris
./tetris
