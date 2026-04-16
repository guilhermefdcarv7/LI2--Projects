#include "estrutura.h"

int pode_mover_carta(struct Mesa mesa, int origem, int destino);

int pode_mover_conjunto(struct Mesa mesa, int origme, int destino, int qtd);

int pode_jogar(struct Mesa mesa, int origem, int destino, int qtd);

void verifica_conjuntos(struct Mesa *mesa);

int verifica_estado_jogo(struct Mesa mesa);