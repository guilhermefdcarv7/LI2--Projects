#include <stdlib.h>
#include "cartas.h"
#include "regras.h"

// CC = 1
struct Pilha pilha_vazia(){ // Função que devolve uma pilha vazia, para ser usada como base para criar as pilhas do tabuleiro.
    struct Pilha pilha; // É criada uma pilha.
    pilha.quantidade = 0; // Define-se a quantidade de cartas dessa pilha como 0, para que seja uma pilha vazia;
    return pilha; // Retorna essa pilha.
}

// CC = 1
struct Pilha add_carta(struct Pilha pilha, struct Carta carta){ // Função que adiciona uma carta específica a uma pilha específica.
    pilha.cartas[pilha.quantidade] = carta; // A carta é adicionada ao topo dessa pilha.
    pilha.quantidade += 1; // A quantidade de cartas na pilha é incrementada.
    return pilha; // Retorna a pilha atualizada.
}

// CC = 1
struct Carta carta_de_cima(struct Pilha pilha){ // Função que devolve a carta que está no topo de uma pilha.
    struct Carta carta = pilha.cartas[pilha.quantidade -1]; // Carta que está no topo da pilha.
    return carta; // Retorna a carta que está no topo da pilha.
}

// CC = 1
struct Pilha retira_carta_de_cima(struct Pilha pilha){ // Função que retira a carta que está no topo de uma pilha, para ser usada para retirar cartas do tabuleiro e jogar.
    pilha.quantidade -= 1; // A quantidade de cartas da pilha é decrementada, logo retira a carta que está no topo da pilha.
    return pilha; // Retorna a pilha sem a carta que estava no topo.
}

// CC = 3
struct Pilha cria_baralho(){ // Função que cria uma baralho de 52 cartas, para ser distribuido pelas 10 pilhas do tabuleiro.
    struct Pilha pilha = pilha_vazia(); // Cria uma pilha vazia que vai representar o baralho.

    for(int i = 0; i < 4; i++){ // Percorre os 4 naipes existentes.
        for(int j = 1; j <= 13; j++){ // Percorre os 13 valores de cartas de cada naipe.
            struct Carta carta; // Cria uma carta temporária.
            carta.valor = j; // Define o valor da carta.
            carta.naipe = i; // Define o naipe da carta.
            pilha = add_carta(pilha,carta); // Adiciona a carta ao baralho de 52 cartas.
        }
    }
    return pilha; // Retorna o baralho completo com as 52 cartas.
}

// CC = 2
struct Pilha baralhar(struct Pilha pilha){ // Função que baralha as cartas de uma pilha, para que as cartas não sejam distribuídas sempre na mesma ordem.
    for(int i = 0; i < pilha.quantidade; i++){ // Percorre todas as cartas da pilha...
        int posicao_aletaoria = rand() % pilha.quantidade; // Gera uma posição aleatoria dentro dos limites da pilha.
        struct Carta temporaria = pilha.cartas[i]; // Guarda temporariamente a carta da posição atual.
        pilha.cartas[i] = pilha.cartas[posicao_aletaoria]; // Coloca na posição atual a carta da posição aleatoria.
        pilha.cartas[posicao_aletaoria] = temporaria; // Coloca a carta temporaria na posiçao aleatoria, concluindo a troca.
    }
    return pilha; // Retorna a pilha com as cartas baralhadas.
}

// CC = 4
struct Mesa prepara_mesa(){ // Função que prepara a mesa para o início do jogo as 10 pilhas do tabuleiro.
    struct Mesa mesa; // Cria a estrutura que vai guardar o estado inicial da mesa.

    mesa.baralho = cria_baralho(); // Cria um baralho completo.
    mesa.baralho = baralhar(mesa.baralho); // Baralha o baralho antes de distribuir as cartas.

    int cartas_a_distribuir = 8; // Variável que controla quantas cartas devem ser distribuídas por coluna.

    for(int i = 0; i < 10; i++){ // Percorre as 10 colunas do tabuleiro.                                                                             
        mesa.tabuleiro[i] = pilha_vazia(); // Inicializa cada coluna do tabuleiro como vazia.                                             
        for(int j = 0; j < cartas_a_distribuir ; j++){ // Coloca 5 cartas em cada uma das 7 pilhas do tabuleiro.                                                     
            struct Carta carta_tirada = carta_de_cima(mesa.baralho); // Obtém a carta que está no topo do baralho de biscar.                      
            mesa.baralho = retira_carta_de_cima(mesa.baralho); // Remove essa carta do baralho.                                                   
            mesa.tabuleiro[i] = add_carta(mesa.tabuleiro[i], carta_tirada); // Adiciona essa carta à coluna atual do tabuleiro.                   
        }
        if(i >= 2){ // Se a coluna atual for a partir da terceira coluna...
            cartas_a_distribuir--; // o número de cartas a distribuitr é decrementado.
        }                                                                                                                            
    }                                                                                                                                           

    return mesa; // Retorna a mesa já preparada para o inicio do jogo.
}

// CC = 4
void mover_cartas(struct Mesa *mesa, int origem, int destino, int qtd){ // Função que move uma ou mais carta de uma coluna de origem para a coluna de destino, efetuando uma jogada.
    if(pode_jogar(*mesa, origem, destino, qtd) == 1){ // Se for possível jogar, ou seja, o movimento for válido...
        struct Pilha pilha_auxiliar = pilha_vazia(); // Cria uma pilha auxiliar vazia para guardar as cartas que vão ser movidas, para que seja possível mover mais do que uma carta de uma vez, sem misturar a ordem das cartas.

        for(int i = 0; i < qtd; i++){ // Percorre as cartas que o jogador quer mover...
            struct Carta carta_a_mover = carta_de_cima(mesa->tabuleiro[origem]); // Obtém a carta que está no topo da pilha de origem
            mesa->tabuleiro[origem] = retira_carta_de_cima(mesa->tabuleiro[origem]); // Retira essa carta da pilha de origem.
            pilha_auxiliar = add_carta(pilha_auxiliar, carta_a_mover); // Adiciona essa carta à pilha auxiliar, para guardar as cartas que vão ser movidas.
        }

        for(int i = 0; i < qtd; i++){ // Percorre as cartas que o jogador quer mover...
            struct Carta carta_a_mover = carta_de_cima(pilha_auxiliar); // Obtém a carta que estáno topo da pilha auxiliar, ous seja, a carta a ser movida.
            pilha_auxiliar = retira_carta_de_cima(pilha_auxiliar); // Retira essa carta da pilha auxiliar.
            mesa->tabuleiro[destino] = add_carta(mesa->tabuleiro[destino], carta_a_mover); // Adiciona essa carta à pilha de destino, concluindo a jogada.
        }

        verifica_conjuntos(mesa); // Verifica se, apó a jogada ser efetuada, foi formado algum conjunto completo, para atualizar a contagem de conjuntos completos da mesa.
    }
}