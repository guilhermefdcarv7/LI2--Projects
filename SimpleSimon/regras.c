#include "regras.h"
#include "estrutura.h"
#include "cartas.h"

int verifica_estado_jogo(struct Mesa mesa){
    if(mesa.conjuntos_completos == 4){
        return 1;
    }

    return 0;
}

// CC = 7
void verifica_conjuntos(struct Mesa *mesa){
    for(int i = 0; i < 10; i++){
        if(mesa->tabuleiro[i].quantidade >= 13){
            int base = mesa->tabuleiro[i].quantidade - 13;
            int conjunto_completo = 1;
            char naipe_alvo = mesa->tabuleiro[i].cartas[base].naipe;

            for(int j = 0; j < 13; j++){
                struct Carta carta_atual = mesa->tabuleiro[i].cartas[base + j];

                int valor_esperado = 13 - j;

                if(carta_atual.naipe != naipe_alvo || carta_atual.valor != valor_esperado){
                    conjunto_completo = 0;
                }
            }

            if(conjunto_completo == 1){
                mesa->tabuleiro[i].quantidade -= 13;
                mesa->conjuntos_completos += 1;
            }

        }
    }
}

// CC = 3
int pode_mover_carta(struct Mesa mesa, int origem, int destino){
    struct Pilha pilha_origem = mesa.tabuleiro[origem];
    struct Pilha pilha_destino = mesa.tabuleiro[destino];

    struct Carta carta_de_cima_origem = carta_de_cima(pilha_origem);
    struct Carta carta_de_cima_destino = carta_de_cima(pilha_destino);

    if(pilha_origem.quantidade == 0){
        return 0;
    }
    
    if(carta_de_cima_origem.valor == carta_de_cima_destino.valor - 1 || pilha_destino.quantidade == 0){
        return 1;
    }

    return 0;

}

// CC = 8 
int pode_mover_conjunto(struct Mesa mesa, int origem, int destino, int qtd){
    if(qtd <= 0 || qtd > mesa.tabuleiro[origem].quantidade){
        return 0;
    }

    int base = mesa.tabuleiro[origem].quantidade - qtd;

    for(int i = base; i < mesa.tabuleiro[origem].quantidade - 1; i++){
        struct Carta carta_atual = mesa.tabuleiro[origem].cartas[i];
        struct Carta carta_proxima = mesa.tabuleiro[origem].cartas[i + 1];

        if(carta_atual.naipe != carta_proxima.naipe || carta_atual.valor - 1 != carta_proxima.valor){
            return 0;
        }
    }

    if(mesa.tabuleiro[destino].quantidade == 0){
        return 1;
    }

    struct Carta carta_base_origem = mesa.tabuleiro[origem].cartas[base];
    struct Carta carta_topo_destino = carta_de_cima(mesa.tabuleiro[destino]);

    if(carta_base_origem.valor == carta_topo_destino.valor -1){
        return 1;
    }

    return 0;

}

// CC = 4
int pode_jogar(struct Mesa mesa, int origem, int destino, int qtd){
    if(qtd <= 0){
        return 0;
    }

    if(qtd == 1){
        return pode_mover_carta(mesa, origem, destino);
    }

    if(qtd > 1){
        return pode_mover_conjunto(mesa, origem, destino, qtd);
    }
}