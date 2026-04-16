#include <stdlib.h>
#include "cartas.h"
#include "regras.h"

// CC = 1
struct Pilha pilha_vazia(){ // Função que devolve uma pilha vazia, para ser usada como base para criar o baralho de biscar, as pilhas do tabuleiro e a pilha de descarte.
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
struct Pilha retira_carta_de_cima(struct Pilha pilha){ // Função que retira a carta que está no topo de uma pilha, para ser usada para retirar cartas do baralho de biscar ou do tabuleiro e colocálas na pilha de descarte.
    pilha.quantidade -= 1; // A quantidade de cartas da pilha é decrementada, logo retira a carta que está no topo da pilha.
    return pilha; // Retorna a pilha sem a carta que estava no topo.
}

// CC = 3
struct Pilha cria_baralho(){ // Função que cria uma baralho de 52 cartas, para ser distribuido pelo baralho de biscar, baralho de descarte e as 7 pilhas do tabuleiro.
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

// CC = 3
struct Mesa prepara_mesa(){ // Função que prepara a mesa para o início do jogo, criando o baralho de biscar, as 7 pilhas do tabuleiro e a pilha de descarte.
    struct Mesa mesa; // Cria a estrutura que vai guardar o estado inicial da mesa.

    mesa.baralho = cria_baralho(); // Cria um baralho completo e atribui-o ao baralho de biscar da mesa.
    mesa.baralho = baralhar(mesa.baralho); // Baralha o baralho antes de distribuir as cartas.

    int cartas_a_distribuir = 8;

    for(int i = 0; i < 10; i++){ // Percorre as 10 colunas do tabuleiro.                                                                             
        mesa.tabuleiro[i] = pilha_vazia(); // Inicializa cada coluna do tabuleiro como vazia.                                             
        for(int j = 0; j < cartas_a_distribuir ; j++){ // Coloca 5 cartas em cada uma das 7 pilhas do tabuleiro.                                                     
            struct Carta carta_tirada = carta_de_cima(mesa.baralho); // Obtém a carta que está no topo do baralho de biscar.                      
            mesa.baralho = retira_carta_de_cima(mesa.baralho); // Remove essa carta do baralho.                                                   
            mesa.tabuleiro[i] = add_carta(mesa.tabuleiro[i], carta_tirada); // Adiciona essa carta à coluna atual do tabuleiro.                   
        }
        if(i >= 2){
            cartas_a_distribuir--;
        }                                                                                                                            
    }                                                                                                                                           

    return mesa; // Retorna a mesa já preparada para o inicio do jogo.
}

// CC = 4
void mover_cartas(struct Mesa *mesa, int origem, int destino, int qtd){
    if(pode_jogar(*mesa, origem, destino, qtd) == 1){

        struct Pilha pilha_auxiliar = pilha_vazia();

        for(int i = 0; i < qtd; i++){
            struct Carta carta_a_mover = carta_de_cima(mesa->tabuleiro[origem]);
            mesa->tabuleiro[origem] = retira_carta_de_cima(mesa->tabuleiro[origem]);
            pilha_auxiliar = add_carta(pilha_auxiliar, carta_a_mover);
        }

        for(int i = 0; i < qtd; i++){
            struct Carta carta_a_mover = carta_de_cima(pilha_auxiliar);
            pilha_auxiliar = retira_carta_de_cima(pilha_auxiliar);
            mesa->tabuleiro[destino] = add_carta(mesa->tabuleiro[destino], carta_a_mover);
        }

        verifica_conjuntos(mesa);
    }

    verifica_conjuntos(mesa);
}