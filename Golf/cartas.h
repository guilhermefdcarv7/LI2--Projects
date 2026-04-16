#include "estrutura.h"

struct Pilha pilha_vazia(); 

struct Pilha add_carta(struct Pilha pilha, struct Carta carta);

struct Carta carta_de_cima(struct Pilha pilha);

struct Pilha retira_carta_de_cima(struct Pilha pilha);

struct Pilha cria_baralho();

struct Pilha baralhar(struct Pilha pilha);

void biscar(struct Mesa *mesa);

void jogar_carta(struct Mesa *mesa, char op_jogo);

struct Mesa prepara_mesa();
