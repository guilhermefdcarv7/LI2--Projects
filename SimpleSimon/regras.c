#include "regras.h"
#include "estrutura.h"
#include "cartas.h"

// CC = 2
int verifica_estado_jogo(struct Mesa mesa){ // Função que verifica o estado de jogo, ou seja, se o jogo está em andamento ou se o jogador ganhou.
    if(mesa.conjuntos_completos == 4){ // Se o número de conjuntos completos da mesa for 4...
        return 1; // O jogador ganhou o jogo.
    }

    return 0; // Se a condição de cima não for verdadeira então o jogo ainda está em andamento.
}

// CC = 7
void verifica_conjuntos(struct Mesa *mesa){ // Função que verifica se, após uma jogada, foi formado algum conjunto completo.
    for(int i = 0; i < 10; i++){  // Percorre as 10 colunas do tabuleiro...
        if(mesa->tabuleiro[i].quantidade >= 13){ // Se a coluna tiver 13 ou mais cartas...
            int base = mesa->tabuleiro[i].quantidade - 13; // CAlcula a posição da carta que seria o possível início de um conjunto completo.
            int conjunto_completo = 1; // Variável que controla se um conjunto está completo ou não.
            char naipe_alvo = mesa->tabuleiro[i].cartas[base].naipe; // Define o naipe do conjunto como sendo o naipe da carta que está na base desse conjunto.

            for(int j = 0; j < 13; j++){ // Percorre as 13 cartas do possível conjunto completo...
                struct Carta carta_atual = mesa->tabuleiro[i].cartas[base + j]; // Define a carta a ser verificada no momento como sendo a carta da posição base + j, ou seja para j = 0, obtemos a carta da base do conjunto, para j = 1, obtemos a carta seguinte e assim sucessivamente até obtermos a carta do topo do conjunto.

                int valor_esperado = 13 - j; // Define o valor esperado da carta atual como sendo 13 para a primeira carta do conjunto, 12 para a segunda e assim sucessivamente até chegar a 1.

                if(carta_atual.naipe != naipe_alvo || carta_atual.valor != valor_esperado){ // Se o naipe da carta que está a ser verificada for diferente do naipe calculado ou se o valor da carta que está a ser verificada for diferente do valor esperado...
                    conjunto_completo = 0; // então o conjunto não está completo, pois existe uma quebra na sequência das cartas do conjunto.
                }
            }

            if(conjunto_completo == 1){ // Se existir um conjunto completo na coluna atual...
                mesa->tabuleiro[i].quantidade -= 13; // então essas carts são retiradas.
                mesa->conjuntos_completos += 1; // E o número de conjuntos completos é incrementado em 1.
            }

        }
    }
}

// CC = 4
int pode_mover_carta(struct Mesa mesa, int origem, int destino){ // Função que cerifica se é possível mover uma única carta da coluna de origem para a coluna de destino.
    struct Pilha pilha_origem = mesa.tabuleiro[origem]; // Variável que guarda a pilha de origem.
    struct Pilha pilha_destino = mesa.tabuleiro[destino]; // Variável que guarda a pilha de destino.

    struct Carta carta_de_cima_origem = carta_de_cima(pilha_origem); // Variável que guarda a carta dque está no topo da pilha de origem.
    struct Carta carta_de_cima_destino = carta_de_cima(pilha_destino); // variável que guarda a carta que está no top da pilha de descarte.

    if(pilha_origem.quantidade == 0){ // Se a pilha de origem estiver vazia...
        return 0; // então não é possível mover nenhuma carta, pois não existem cartas nessa pilha.
    }
    
    if(carta_de_cima_origem.valor == carta_de_cima_destino.valor - 1 || pilha_destino.quantidade == 0){ // Se o valor da carta que está no topo da pilha de origem for imedatamente inferior ao valor da carta que está no topo da pilha de destino ou se a pilha de destino estiver vazia...
        return 1; // então épossível efetuar a jogada.
    }

    return 0; // Caso nenhuma das condições de cima seja verdadeira, então a jogada não é válida.

}

// CC = 8 
int pode_mover_conjunto(struct Mesa mesa, int origem, int destino, int qtd){ // Função que verifica se é possível mover um conjunto de cartas da coluna de origem para a coluna de destino.
    if(qtd <= 0 || qtd > mesa.tabuleiro[origem].quantidade){ // Se a quantidade de cartas a mover for meno ou igual a 0 ou se a quantidade de cartas a mover for maior que o número de cartas da pilha de origem...
        return 0; // então não é possível efetuar a jogada.
    }

    int base = mesa.tabuleiro[origem].quantidade - qtd; // Variável que calcula aposição da carta que seria a base do conjunto a ser movido.

    for(int i = base; i < mesa.tabuleiro[origem].quantidade - 1; i++){ // Percorre as cartas do conjunto a ser movido...
        struct Carta carta_atual = mesa.tabuleiro[origem].cartas[i]; // Variável que guarda a carta que está a ser verificada no momento.
        struct Carta carta_proxima = mesa.tabuleiro[origem].cartas[i + 1]; // Variável que guarda carta seguinte à carta que está a ser verificada no momento.

        if(carta_atual.naipe != carta_proxima.naipe || carta_atual.valor - 1 != carta_proxima.valor){ // Se o naipe da carta atual for diferente do naipe da carta seguinte ou se o valor da carta atual não for imediatamente superior ao valor da carta seguinte...
            return 0; // então o conjunto não pode ser movido, pois existe uma quebra na sequÊncia das cartas. do conjunto.
        }
    }

    if(mesa.tabuleiro[destino].quantidade == 0){ // Se a pilha de destino estiver vazia...
        return 1; // então é possível mover o conjunto para essa pilha.
    }

    struct Carta carta_base_origem = mesa.tabuleiro[origem].cartas[base]; // Variável que guarda a carta da base do conjunto a ser movido.
    struct Carta carta_topo_destino = carta_de_cima(mesa.tabuleiro[destino]); // Variável que guarda a carta do topo da pilha de destino.

    if(carta_base_origem.valor == carta_topo_destino.valor -1){ // Se o valor da carta da base do conjunto a ser movido for imediatamente inferior ao valor da carta do topo da pilha de destino...
        return 1; // então eº possível mover o conjunto para essa pilha
    }

    return 0; // Caso nenhuma das condições de cima seja verdadeira, então o conjunto não pode ser movido para a pilha d destino.

}

// CC = 4
int pode_jogar(struct Mesa mesa, int origem, int destino, int qtd){ // Função que verifica se é possível efetuar uma jogada.
    if(qtd <= 0){ // Se a quantidade de cartas a mover for menor ou igual a 0...
        return 0; // então não é possível efetuar a jogada.
    }

    if(qtd == 1){ // Se a quantidade de cartas a mover for igual a 1...
        return pode_mover_carta(mesa, origem, destino); // então verifica se é possível mover uma única carta da coluna de origem para a coluna de destino.
    }

    if(qtd > 1){ // Se a quantidade de cartas a mover for maior que 1...
        return pode_mover_conjunto(mesa, origem, destino, qtd); // então verifica se é possível mover um conjunto de cartas da coluna de origem para a coluna de destino.
    }
}
