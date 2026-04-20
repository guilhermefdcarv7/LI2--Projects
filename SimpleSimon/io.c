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

// CC = 4
void mostra_jogo(struct Mesa mesa){ // Função que mostra o estado atual do jogo.
        for(int i = 0; i < 10; i++){ // Ciclo que percorre as 10 pilhas do tabuleiro jogo...
            printf("%2d | ", i + 1); // Número da coluna.

            if(mesa.tabuleiro[i].quantidade == 0){ // Se a pilha do tabuleiro estiver vazia...
                printf(""); // Não será impresso nada.
            } else{ // Caso contrário...
                for(int j = 0; j < mesa.tabuleiro[i].quantidade; j++){ // Percorre todas as cartas da coluna.
                    mostra_carta(mesa.tabuleiro[i].cartas[j]); // Chama a função mostra_carta(struct Carta carta) para poder imprimir as cartas da coluna.
                    printf(" "); // Espaço entre as cartas da mesma coluna.
                }
            }
            printf("\n");
        }
        printf("\n");
}

// CC = 4
void jogo(){
    struct Mesa mesa = prepara_mesa(); // Cria uma mesa já pereparada para o jogo.
    int op; // Variável para armazenar a opção do jogador.

    while(verifica_estado_jogo(mesa) == 0){ // Enquando o estado do jogo for 0 (jogo em andamento)...
        mostra_jogo(mesa); // Função que mostra o estado atual do jogo.

        printf("Escolhe uma opção:\n");
        printf("1. Mover 1 carta.\n");
        printf("2. Mover mais que 1 carta.\n");

        scanf(" %d", &op); // Armazena a opção do jogador na variável op.

        if(op == 1){ // Se o jogador escolher a opção 1 (mover 1 carta)...
            printf("1. Escolhe a coluna de origem (1-10): \n"); // Pergunta ao jogador qual a coluna de origem da carta que quer mover.
            int coluna_origem; // Variável para armazenar a coluna de origem.
            scanf(" %d", &coluna_origem); // Armazena a coluna de origem na variável coluna_origem.
            printf("2. Escolhe a coluna de destino (1-10): \n"); // Pergunta ao jogador qual a coluna de destino da carta que quer mover.
            int coluna_destino; // Variável para armazenar a coluna de destino.
            scanf(" %d", &coluna_destino); // Armazena a coluna de destino na variável coluna_destino.

            mover_cartas(&mesa, coluna_origem - 1, coluna_destino - 1, 1); // move a carta da coluna de origem para a coluna de destino. Subtrai-se 1 ás colunas porque o jogador escolhe as colunas de 1 a 10, mas o array do tabuleiro começa em 0.
        } else if(op == 2){ // Se o jogador escolher a opção 2 (mover mais que 1 carta)...
            printf("1. Escolhe a coluna de origem (1-10): \n"); // Pergunta ao jogador qual a coluna de origem da carta que quer mover.
            int coluna_origem2; // Variável para armazenar a coluna de origem.
            scanf(" %d", &coluna_origem2);// Armazena a coluna de origem na variável coluna_origem2.
            printf("2. Escolhe a coluna de destino (1-10): \n");// Pergunta ao jogador qual a coluna de destino da carta que quer mover.
            int coluna_destino2; // Variável para armazenar a coluna de destino.
            scanf(" %d", &coluna_destino2); // Armazena a coluna de destino na variável coluna_destino2.
            printf("3. Quantas cartas quer mover? \n"); // Pergunta ao jogador quantas cartas quer mover.
            int qtd_cartas; // Variável para armazenar a quantidade de cartas que o jogador quer mover.
            scanf(" %d", &qtd_cartas); // Armazena a quantidade de cartas na variável qtd_cartas.

            mover_cartas(&mesa, coluna_origem2 - 1, coluna_destino2 - 1, qtd_cartas); // Move as cartas da coluna de origem para a coluna de destino. Subtrai-se 1 ás colunas porque o jogador escolhe as colunas de 1 a 10, mas o array do tabuleiro começa em 0.
        } else{ // Caso o jogador escolha uma o pção diferente de 1 ou 2...
            printf("Opção inválida. Tente novamente. \n"); // IMprime uma mensagem de errro.
        }
    }

    mostra_fim_de_jogo(mesa); // Chama a função que mostra uma mensagem de fim de jogo dependendo do resultado do jogo (vitória ou derrota).
}

// CC = 2
void mostra_fim_de_jogo(struct Mesa mesa){
    if(verifica_estado_jogo(mesa) == 1){ // Se o estado de jogo for 1 (vitória)...
        printf("Parabéns! Ganhaste o jogo!\n"); // Iimprime uma mensagem de vitoria.
    } else{ // Caso contrário (derrota)...
        printf("Jogo terminado. Tenta novamente.\n"); // Imprime uma mensagem de derrrota.
    }
}