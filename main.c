#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cartas.h"
#include "estrutura.h"
#include "regras.h"
#include "io.h"

// CC = 1
int main(){
    srand(time(NULL)); // Incializa a semente para a geração de números aleatórios, através das horas do PC,  para que o baralho seja baralhado de forma diferente cada vez que se iniciar o jogo.
    mostra_menu(); // Mostra o menu inicial do jogo.
    return 0;
}