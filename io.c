#include <stdio.h>
#include "cartas.h"
#include "estrutura.h"
#include "regras.h"
#include "io.h"

// CC = 5
void mostra_carta(struct Carta carta){ // Função que mostra uma carta no terminal.
    const char *cartas[4][13] = { // Array de símbolos como representação visual das cartas (4 Naipes(♧,♤,♢,♡), 13 Valores(Ás, 2, 3, 4, 5, 6, 7, 8, 9, 10, Valete, Dama e Rei)).
        {"🂡", "🂢", "🂣", "🂤", "🂥", "🂦", "🂧", "🂨", "🂩", "🂪", "🂫", "🂭", "🂮"},
        {"🃑", "🃒", "🃓", "🃔", "🃕", "🃖", "🃗", "🃘", "🃙", "🃚", "🃛", "🃝", "🃞"},
        {"🂱", "🂲", "🂳", "🂴", "🂵", "🂶", "🂷", "🂸", "🂹", "🂺", "🂻", "🂽", "🂾"},
        {"🃁", "🃂", "🃃", "🃄", "🃅", "🃆", "🃇", "🃈", "🃉", "🃊", "🃋", "🃍", "🃎"}
    };

    if(carta.naipe >= 0 && carta.naipe < 4 && carta.valor >= 1 && carta.valor <= 13){ // Verifica se o naípe e o valor da carta são válidos (O valor da carta está entre 0 e 13 e o naipe da carta está entre 1 e 4).
        printf("%s", cartas[carta.naipe][carta.valor -1]); // Imprime a carta. Como os valores vão de 1 a 13, e o array começa em 0, retira-se 1 ao valor
    }
}

// CC = 5
void mostra_jogo(struct Mesa mesa){ // Função que mostra o estado atual do jogo. (7 pilhas do tabuleiro, pilha de descarte e baralho de biscar).
    printf("\n\n\n\n\n\n\n\n\n\n");
    for(int i = 0; i < 7; i++){ // Ciclo que percorre as 7 pilhas do tabuleiro jogo...
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

    if(mesa.descarte.quantidade > 0){ // Se a pilha de desctarte não estiver vazia...
        printf("    "); // Espaço para alinhar a carta do topo do descarte com as cartas das pilhas do tabuleiro.
        mostra_carta(carta_de_cima(mesa.descarte)); // Mostra a carta do top da pilha de descarte.
        printf("\n"); // Mudança de linha para separar a carta do topo do descarte do número de cartas restantes no baralho de biscar.
    }
    printf("\nPilha de biscar: %d caratas restantes.\n", mesa.baralho.quantidade); // Mostra o número de cartas restantes no baralho de biscar.
}

// CC = 3
void mostra_fim_de_jogo(struct Mesa mesa){ // Função que mostra a mensagem de fim de jogo, de acordo com o resultado do jogo (vitoria ou derrota).
    int estado_jogo = verifica_estado_jogo(mesa); // Verifica o estado do jogo para mostrar a mensagem correta de acordo com o resultado do jogo.

    printf("\n=====================================================================================================================================================================================================================\n");             
    printf("\n\n\n\n\n\n\n\n\n\n");

    if(estado_jogo == 1){ // Se o jogador ganhou o jogo...
        printf("                                    PARABÉNS! LIMPASTE A MESA E GANHASTE! \n"); // Mostra a mensagem de vitória.
    } else if(estado_jogo == -1){ // Caso contrário...
        printf("                                    FIM DE JOGO! NÃO HÁ MAIS JOGADAS. \n"); // Mostra a mensagem de derrota.
    }
    
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n=====================================================================================================================================================================================================================\n");    
}

// CC = 6
void jogo(){
    struct Mesa mesa = prepara_mesa(); // Prepara a mesa para o início do jogo, criando o baralho de bicar, as 7 pilhas do tabuleiro e a pilha  de decarte.
    int estado_jogo = 0; // Incialização da varíavel que indica o estado do jogo, para controlar o ciclio do jogo e mostrar a mensgem de fim de jogo correta.
    char op_jogo; // Variável que guarda a opção que o utilizador escolheu para jogar (Escolher uma pilha do tabuleiro para jogar ou biscar do baralho de biscar).

    while(estado_jogo == 0){ // Enquanto o o jogo puder continuar...
        printf("\n=====================================================================================================================================================================================================================\n");
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("\n\n\n\n\n\n\n\n\n");
        mostra_jogo(mesa); // Mostra o estado atual do jogo (7 pilhas do tabuleiro, pilha de descarte e pilha de biscar).

        scanf(" %c", &op_jogo); // Lê a opção que o utlizador escolheu para jogar.

        printf("\n=====================================================================================================================================================================================================================\n");    

        if(op_jogo == 'B' || op_jogo == 'b'){ // Se o utlizador escolheu biscar do baralho de biscar...
            biscar(&mesa); // Bisca uma carta do baralho de biscar e coloca-a no topo da pilha de descarte.
        } else if(op_jogo >= '1' && op_jogo <= '7'){ // Se o utilizador escolheu jogar uma carta de uma pilha do tabuleiro...
            jogar_carta(&mesa, op_jogo); // Joga a carta do topo da pilha de descarte com a carta do topo da pilha do tabuleiro escolhida pelo usuário, se for uma jogada válida.
        }

        estado_jogo = verifica_estado_jogo(mesa); // Verifica o estado do jogo, para controlar o ciclo do jogo.
    }

    mostra_fim_de_jogo(mesa); // Quando o jogo terminar, mostra a mensagem de fim de jogo de acordo com o resultado (vitória ou derrota).

}

// CC = 2
void mostra_regras(){
    int op_regras; // Variável que guarda a opção que o utilizador escolheu para voltar ao menu.
    printf("\n=====================================================================================================================================================================================================================\n");
    printf("Objetivo: \n");
    printf(" * O objetivo do jogo é remover todas as 35 cartas do tabuleiro e colocá-las na pilha de descarte antes que o baralho de compra acabe.\n\n\n");
    printf("Regras: \n");
    printf(" * São dadas 35 cartas viradas para cima, distribuídas em 7 colunas de 5 cartas cada;\n");
    printf(" * As 17 cartas que sobram formam a pilha de biscar;\n");
    printf(" * Podes mover uma carta do tabuleiro para a pilha de descarte\n se ela tiver exatamente um valor acima ou um valor abaixo da carta que está no topo da pilha de descarte;\n");
    printf(" * Quando ficares sem jogadas possíveis no tabuleiro\n ,tira a carta do topo da pilha de compra e coloca-a na pilha descarte;\n");
    printf(" * Clicar na tecla de 1 a 7 para escolher a pilha para remover a carta;\n");
    printf(" * Clicar na tecla 'B' para biscar da pilha de biscar.\n");
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                                                                                      Prima 1 para voltar\n");
    printf("\n=====================================================================================================================================================================================================================\n");    
    scanf(" %d", &op_regras); // Lê a opção que o utlizador escolheu.

    if(op_regras == 1){ // Se o usuário escolheu voltar ao menu...
        mostra_menu(); // Mostra o menu inicial do jogo.
    }
}

// CC = 3
void mostra_menu(){
    int op_menu; // Variável que guarda a opção que o utilizador escolheu para jogar ou para ver as regras do jogo.
    printf("\n=====================================================================================================================================================================================================================\n");    
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n");
    printf("                                                                                              GOLF SOLITAIRE");
    printf("\n");
    printf("\n");
    printf("                                                                                         1. Jogar       2. Regras");
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("\n=====================================================================================================================================================================================================================\n");    
    scanf(" %d", &op_menu);

    if(op_menu == 1){ // Se o usuário escolheu jogar...
        jogo(); // Inicia o jogo.
    } else if(op_menu == 2){ // Se o usuário escolheu ver as regras do jogo...
        mostra_regras(); // Mostra as regras do jogo.
    }
}