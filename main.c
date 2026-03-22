#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cartas.h"
#include "estrutura.h"
#include "regras.h"
#include "io.h"

int main(){
    srand(time(NULL));
    mostra_menu();
    return 0;
}