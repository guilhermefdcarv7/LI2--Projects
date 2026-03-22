#include <stdio.h>
#include "cartas.h"
#include "estrutura.h"
#include "regras.h"
#include "io.h"

// CC = 5
void mostra_carta(struct Carta carta){
    const char *cartas[4][13] = {
        {"🂡", "🂢", "🂣", "🂤", "🂥", "🂦", "🂧", "🂨", "🂩", "🂪", "🂫", "🂭", "🂮"},
        {"🃑", "🃒", "🃓", "🃔", "🃕", "🃖", "🃗", "🃘", "🃙", "🃚", "🃛", "🃝", "🃞"},
        {"🂱", "🂲", "🂳", "🂴", "🂵", "🂶", "🂷", "🂸", "🂹", "🂺", "🂻", "🂽", "🂾"}, 
        {"🃁", "🃂", "🃃", "🃄", "🃅", "🃆", "🃇", "🃈", "🃉", "🃊", "🃋", "🃍", "🃎"}
    };

    if(carta.naipe >= 0 && carta.naipe < 4 && carta.valor >= 1 && carta.valor <= 13){
        printf("%s", cartas[carta.naipe][carta.valor -1]);
    }
}

// CC = 5
void mostra_jogo(struct Mesa mesa){
    for(int i = 0; i < 7; i++){
        if(mesa.tabuleiro[i].quantidade == 0){
            printf("");
        } else{
            for(int j = 0; j < mesa.tabuleiro[i].quantidade; j++){
                mostra_carta(mesa.tabuleiro[i].cartas[j]);
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
    if(mesa.descarte.quantidade > 0){
        printf("    ");
        mostra_carta(carta_de_cima(mesa.descarte));
        printf("\n");
    }
    printf("\nPilha de biscar: %d caratas restantes.", mesa.baralho.quantidade);
}

// CC = 3
void mostra_fim_de_jogo(struct Mesa mesa){
    int estado_jogo = verifica_estado_jogo(mesa);

    printf("\n=======================================");   
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    if(estado_jogo == 1){
        printf("    PARABÉNS! LIMPASTE A MESA E GANHASTE! \n");
    } else if(estado_jogo == -1){
        printf("    FIM DE JOGO! NÃO HÁ MAIS JOGADAS. \n");
    }
    
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("==============================================\n");
}

// CC = 9
void jogo(){
    struct Mesa mesa = prepara_mesa();
    int estado_jogo = 0;
    char op_jogo;

    while(estado_jogo == 0){
        mostra_jogo(mesa);

        scanf(" %c", &op_jogo);

        if(op_jogo == 'B' || op_jogo == 'b'){
                if(mesa.baralho.quantidade > 0){
                    struct Carta carta = carta_de_cima(mesa.baralho);
                    mesa.baralho = retira_carta_de_cima(mesa.baralho);
                    mesa.descarte = add_carta(mesa.descarte, carta);
                }
        } else if(op_jogo >= '1' && op_jogo <= '7'){
                int numero_da_pilha = (op_jogo - '1');
                if(mesa.tabuleiro[numero_da_pilha].quantidade != 0){
                    struct Carta carta_da_pilha_escolhida = carta_de_cima(mesa.tabuleiro[numero_da_pilha]);
                    struct Carta carta_do_descarte = carta_de_cima(mesa.descarte);
                    if(pode_jogar(carta_da_pilha_escolhida, carta_do_descarte) == 1){
                        mesa.tabuleiro[numero_da_pilha] = retira_carta_de_cima(mesa.tabuleiro[numero_da_pilha]);
                        mesa.descarte = add_carta(mesa.descarte, carta_da_pilha_escolhida);
                    }
                }
        }

        estado_jogo = verifica_estado_jogo(mesa);
    }

    mostra_fim_de_jogo(mesa);

}

void mostra_regras(){
    int op_regras;
    printf("\n================================================================================================================\n");
    printf(" * São dadas 35 cartas viradas para cima, distribuídas em 7 colunas de 5 cartas cada;\n");
    printf(" * As 17 cartas que sobram formam a pilha de biscar;\n");
    printf(" * Podes mover uma carta do tabuleiro para a pilha de descarte\n se ela tiver exatamente um valor acima ou um valor abaixo da carta que está no topo do descarte;\n");
    printf(" * Quando ficares sem jogadas possíveis no tabuleiro\n ,tira a carta do topo da pilha de compra e coloca-a no descarte;\n");
    printf(" * Clicar na tecla de 1 a 7 para escolher a pilha para remover a carta;\n");
    printf(" * Clicar na tecla 'B' para biscar da pilha de biscar.\n");
    printf("\n                           Prima 1 para voltar                                 \n");
    printf("================================================================================================================\n");
    scanf(" %d", &op_regras);

    if(op_regras == 1){
        mostra_menu();
    }
}

void mostra_menu(){
    int op_menu;
    printf("\n===================================================");   
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                  GOLF SOLITAIRE                     ");
    printf("\n");
    printf("\n");
    printf("             1. Jogar       2. Regras               ");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("===================================================\n");
    scanf(" %d", &op_menu);

    if(op_menu == 1){
        jogo();
    } else if(op_menu == 2){
        mostra_regras();
    }
}