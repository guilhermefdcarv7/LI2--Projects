#include <stdlib.h>
#include "cartas.h"

// CC = 1
struct Pilha pilha_vazia(){ // Função que devolve uma pilha vazia.
    struct Pilha pilha; // É criada uma pilha.
    pilha.quantidade = 0; // Define-se a quantidade de cartas dessa pilha como 0, para que seja uma pilha vazia;
    return pilha; // Retorna essa pilha.
}

// CC = 1
struct Pilha add_carta(struct Pilha pilha, struct Carta carta){ // Função que adiciona uma carta específica a uma pilha específica.
    pilha.cartas[pilha.quantidade] = carta; // A carta c é adicionada ao topo da pilha p.
    pilha.quantidade += 1; // A quantidade de cartas na pilha p é incrementada. 
    return pilha; // Retorna a pilha p atualizada
}

// CC = 1
struct Carta carta_de_cima(struct Pilha pilha){
    struct Carta carta = pilha.cartas[pilha.quantidade -1]; // Retorna a carta que está no topo da pilha p.
    return carta;
}

// CC = 1
struct Pilha retira_carta_de_cima(struct Pilha pilha){
    pilha.quantidade -= 1; // A quantidade de cartas da pilha p é decrementada, logo retira a carta que está no topo da pilha p.
    return pilha; // Retorna a pilha p sem a carta do topo.
}

// CC = 3
struct Pilha cria_baralho(){
    struct Pilha pilha = pilha_vazia();

    for(int i = 0; i < 4; i++){
        for(int j = 1; j <= 13; j++){
            struct Carta carta;
            carta.valor = j;
            carta.naipe = i;
            pilha = add_carta(pilha,carta);
        }
    }
    return pilha;
}

// CC = 2
struct Pilha baralhar(struct Pilha pilha){
    for(int i = 0; i < pilha.quantidade; i++){
        int posicao_aletaoria = rand() % pilha.quantidade;
        struct Carta temporaria = pilha.cartas[i];
        pilha.cartas[i] = pilha.cartas[posicao_aletaoria];
        pilha.cartas[posicao_aletaoria] = temporaria;
    }
    return pilha;
}

// CC = 3
struct Mesa prepara_mesa(){
    struct Mesa mesa;

    mesa.baralho = cria_baralho();
    mesa.baralho = baralhar(mesa.baralho);

    for(int i = 0; i < 7; i++){
        mesa.tabuleiro[i] = pilha_vazia();
        for(int j = 0; j < 5; j++){
            struct Carta carta_tirada = carta_de_cima(mesa.baralho);
            mesa.baralho = retira_carta_de_cima(mesa.baralho);
            mesa.tabuleiro[i] = add_carta(mesa.tabuleiro[i], carta_tirada);
        }
    }
    mesa.descarte = pilha_vazia();
    struct Carta primeira_carta = carta_de_cima(mesa.baralho);
    mesa.baralho = retira_carta_de_cima(mesa.baralho);
    mesa.descarte = add_carta(mesa.descarte, primeira_carta);

    return mesa;
}