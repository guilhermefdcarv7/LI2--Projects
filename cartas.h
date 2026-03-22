#include "estrutura.h"

struct Pilha pilha_vazia();

struct Pilha add_carta(struct Pilha pilha, struct Carta carta);

struct Carta carta_de_cima(struct Pilha pilha);

struct Pilha retira_carta_de_cima(struct Pilha pilha);

struct Pilha cria_baralho();

struct Pilha baralhar(struct Pilha pilha);

struct Mesa prepara_mesa();