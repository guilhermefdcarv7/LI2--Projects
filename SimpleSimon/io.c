#include <stdio.h>
#include "io.h"
#include "estrutura.h"
#include "cartas.h"
#include "regras.h"

// CC = 5
void mostra_carta(struct Carta carta){ // Função que mostra uma carta no terminal.
    const char *cartas[4][13] = { // Array de símbolos como representação visual das cartas (4 Naipes(♧,♤,♢,♡), 13 Valores(Ás, 2, 3, 4, 5, 6, 7, 8, 9, 10, Valete, Dama e Rei)).
        {"🂡", "🂢", "🂣", "🂤", "🂥", "🂦", "🂧", "🂨", "🂩", "🂪", "🂫", "🂭", "🂮"},
        {"🃑", "🃒", "🃓", "🃔", "🃕", "🃖", "🃗", "🃘", "🃙", "🃚", "🃛", "🃝", "🃞"},
        {"🂱", "🂲", "🂳", "🂴", "🂵", "🂶", "🂷", "🂸", "🂹", "🂺", "🂻", "🂽", "🂾"},
        {"🃁", "🃂", "🃃", "🃄", "🃅", "🃆", "🃇", "🃈", "🃉", "🃊", "🃋", "🃍", "🃎"}
    };

    if(carta.naipe >= 0 && carta.naipe < 4 && carta.valor >= 1 && carta.valor <= 13){ // Verifica se o naípe e o valor da carta são válidos (O valor da carta está entre 0 e 13 e o naipe da carta está entre 1 e 4).
        printf("%s", cartas[carta.naipe][carta.valor - 1]); // Imprime a carta. Como os valores vão de 1 a 13, e o array começa em 0, retira-se 1 ao valor
    }
}

// CC = 7
void mostra_jogo(struct Mesa mesa){ // Função que mostra o estado atual do jogo. (7 pilhas do tabuleiro, pilha de descarte e baralho de biscar).
        printf("\n\n\n\n\n\n\n\n\n\n");
        for(int i = 0; i < 10; i++){ // Ciclo que percorre as 10 pilhas do tabuleiro jogo...
            
            printf("%2d | ", i + 1);

            if(mesa.tabuleiro[i].quantidade == 0){ // Se a pilha do tabuleiro estiver vazia...
                printf(""); // Não será impresso nada.
            } else{ // Caso contrário...
                for(int j = 0; j < mesa.tabuleiro[i].quantidade; j++){ // Percorre todas as cartas da coluna.
                    mostra_carta(mesa.tabuleiro[i].cartas[j]); // Chama a função mostra_carta() para poder imprimir as cartas da coluna e dá um espaço de separação.
                    printf(" "); // Espaço entre as cartas da mesma coluna.
                }
            }
            printf("\n"); // Mudança de linha a cada coluna.
        }
        printf("\n");
}

void jogo(){
    struct Mesa mesa = prepara_mesa();
    int op;

    while(verifica_estado_jogo(mesa) == 0){
        mostra_jogo(mesa);

        printf("Escolhe uma opção:\n");
        printf("1. Mover 1 carta.\n");
        printf("2. Mover mais que 1 carta.\n");

        scanf(" %d", &op);

        if(op == 1){
            printf("1. Escolhe a coluna de origem (1-10): \n");
            int coluna_origem;
            scanf(" %d", &coluna_origem);
            printf("2. Escolhe a coluna de destino (1-10): \n");
            int coluna_destino;
            scanf(" %d", &coluna_destino);

            mover_cartas(&mesa, coluna_origem - 1, coluna_destino - 1, 1);
        } else if(op == 2){
            printf("1. Escolhe a coluna de origem (1-10): \n");
            int coluna_origem;
            scanf(" %d", &coluna_origem);
            printf("2. Escolhe a coluna de destino (1-10): \n");
            int coluna_destino;
            scanf(" %d", &coluna_destino);
            printf("3. Quantas cartas quer mover? \n");
            int qtd_cartas;
            scanf(" %d", &qtd_cartas);

            mover_cartas(&mesa, coluna_origem - 1, coluna_destino - 1, qtd_cartas);
        } else{
            printf("Opção inválida. Tente novamente. \n");
        }
    }

    mostra_fim_de_jogo(mesa);
}

// CC = 2
void mostra_fim_de_jogo(struct Mesa mesa){
    if(verifica_estado_jogo(mesa) == 1){
        printf("Parabéns! Ganhaste o jogo!\n");
    } else{
        printf("Jogo terminado. Tenta novamente.\n");
    }
}