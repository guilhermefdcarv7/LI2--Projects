#include "regras.h"

// CC = 3
int pode_jogar(struct Carta carta_tabuleiro, struct Carta carta_descarte){ // Função que verifica se a carta do topo de uma pilha do tabuleiro pode ser jogada sobre a carta do topo da pilha de descarte.
    int diferenca = carta_tabuleiro.valor - carta_descarte.valor; // Calcula a diferença entre o valor da carta de um baralho da mesa e o valor da carta da pilha de descarte.

    if(diferenca < 0){ 
        diferenca = -diferenca; // Se a diferença for negativa, converte-a para positiva.
    }

    if(diferenca == 1){
        return 1; // Retorna 1 (True) se a diferença entre os valores das cartas for 1, logo a jogada é valida.
    } else{
        return 0; // Retorna 0 (False) se a diferença for diferente de 1, logo a jogada não é valida .
    }
}

// CC = 5
int existe_jogada_possivel(struct Mesa mesa, int jogada_possivel){ // Função que verifica se existe alguma jogada possivel com todas as cartas do topo das pilhas do tabuleiro e a carta do topo da pilha de descarte.
    struct Carta carta_descarte_topo = mesa.descarte.cartas[mesa.descarte.quantidade - 1]; // Carta do topo da pilha de descarte.
        for(int i = 0; i < 7 && jogada_possivel == 0; i++){ // Percorre as 7 pilhas do tabuleiro equanto não for encontrada uma jogada possivel...
            if(mesa.tabuleiro[i].quantidade > 0){ // Se a pilha atual do tabuleiro não está vazia...
                struct Carta carta_tabuleiro_topo = mesa.tabuleiro[i].cartas[mesa.tabuleiro[i].quantidade - 1]; // Carta no topo da pilha atual.
                if(pode_jogar(carta_tabuleiro_topo, carta_descarte_topo)){ // Se a carta do topo da pilha atual puder ser jogada com a carta do topo da pilha de descarte ...
                    jogada_possivel = 1; // Então existe jogada possivel.
                }
            }
        }

        return jogada_possivel;
}

// CC = 8
int verifica_estado_jogo(struct Mesa mesa){
    int pilhas_vazias = 1; // Assume inicialmente que todas as pilhas do tabuleiro estao vazias.
    int jogada_possivel = 0; // Inicializa a variável que indica que existe alguma jogada possivel.

    for(int i = 0; i < 7 && pilhas_vazias == 1; i++){ // Percorre as 7 pilhas do tabuleiro enquanto ainda se assume que estao todas vazias...
        if(mesa.tabuleiro[i].quantidade > 0){ // Se encontrar alguma pilha do tabuleiro que não esteja vazia...
            pilhas_vazias = 0; // Então já não estão todas vazias (Temos pelo menos uma pilha com cartas).
        }
    }

    if(pilhas_vazias == 1){ // Se todas as pilhas do tabuleiro estiverem vazias...
        return 1; // Retorna 1, indicando vitoria.
    }

    if(mesa.baralho.quantidade > 0){ // Se ainda existirem cartas no baralho de biscar...
        return 0; // Retorna 0, indicando que o jogo pode continuar.
    }

    if(mesa.descarte.quantidade > 0){ // Se ainda existirem cartas na pilha de descarte...
        jogada_possivel = existe_jogada_possivel(mesa, jogada_possivel); // Verifica se existe alguma jogada possivel a partir do topo do descarte.
    }

    if(jogada_possivel == 1){ // Se existir alguma jogada possível...
        return 0; // Retorna 0, indicando que o jogo pode continuar.
    }

    return -1; // Retorna -1 se não houver jogadas possiveis e o baralho estiver vazio, indicando derrota.
}