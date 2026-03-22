#include "regras.h"

// CC = 4
int pode_jogar(struct Carta carta_mesa, struct Carta carta_descarte){
    int diferenca = carta_mesa.valor - carta_descarte.valor;

    if(diferenca < 0){
        diferenca = -diferenca;
    }

    if(diferenca == 1){
        return 1;
    } else{
        return 0;
    }
}

int existe_jogada_possivel(struct Mesa mesa, int jogada_possivel){
    struct Carta carta_descarte_topo = mesa.descarte.cartas[mesa.descarte.quantidade - 1]; 
        for(int i = 0; i < 7 && jogada_possivel == 0; i++){
            if(mesa.tabuleiro[i].quantidade > 0){
                struct Carta carta_tabuleiro_topo = mesa.tabuleiro[i].cartas[mesa.tabuleiro[i].quantidade - 1]; 
                if(pode_jogar(carta_tabuleiro_topo, carta_descarte_topo)){
                    jogada_possivel = 1;
                }
            }
        }
}

int verifica_estado_jogo(struct Mesa mesa){
    int pilhas_vazias = 1;
    int jogada_possivel = 0;

    for(int i = 0; i < 7 && pilhas_vazias == 1; i++){
        if(mesa.tabuleiro[i].quantidade > 0){ 
            pilhas_vazias = 0; 
        }
    }

    if(pilhas_vazias == 1){
        return 1;
    }

    if(mesa.baralho.quantidade > 0){
        return 0;
    }

    if(mesa.descarte.quantidade > 0){
        existe_jogada_possivel(mesa, jogada_possivel);
    }

    if(jogada_possivel == 1){
        return 0;
    }
    return -1;
}