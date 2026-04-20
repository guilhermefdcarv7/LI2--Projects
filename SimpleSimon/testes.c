#include <stdio.h>
#include <CUnit/Basic.h>
#include "estrutura.h"
#include "cartas.h"
#include "regras.h"

// Testar quantidade de cartas numa pilha vazia.
void test_pilha_vazia(void){
    struct Pilha pilha = pilha_vazia(); // Cria uma pilha vazia.
    CU_ASSERT_EQUAL(pilha.quantidade, 0); // A pilha tem de ter 0 cartas.
}

void test_pode_mover_carta_valido(void){
    struct Mesa mesa = prepara_mesa(); // Cria uma mesa já preparada para o jogo,

    struct Carta carta5 = {5, 0}; // 5 de Paus
    struct Carta carta6 = {6, 1}; // 6 de Espadas
    
    mesa.tabuleiro[0] = pilha_vazia(); // Esvazia a primeira coluna.
    mesa.tabuleiro[1] = pilha_vazia(); // Esvazia a segunda coluna.

    mesa.tabuleiro[0] = add_carta(mesa.tabuleiro[0], carta5); // Coluna de origem tem um 5 no topo
    mesa.tabuleiro[1] = add_carta(mesa.tabuleiro[1], carta6); // Coluna de destino tem um 6 no topo

    int resultado = pode_mover_carta(mesa, 0, 1); // Verifica sepode mover o 5 de Paus para cima do 6 de Espadas.
    CU_ASSERT_EQUAL(resultado, 1); 
}

void test_mover_para_coluna_vazia(void) {
    struct Mesa mesa = prepara_mesa();
    
    // Coluna de destino vazia.
    mesa.tabuleiro[0] = pilha_vazia(); 
    
    // Coluna de origem vazia.
    mesa.tabuleiro[1] = pilha_vazia();

    struct Carta carta5_ouros = {5, 2}; // 5 de Ouros.

    mesa.tabuleiro[1] = add_carta(mesa.tabuleiro[1], carta5_ouros); // Colocar um 5 de Ouros na coluna de origem.

    // TESTE 1: Mover uma carta individual para a coluna vazia (Tem de dar 1 / Válido)
    CU_ASSERT_EQUAL(pode_mover_carta(mesa, 1, 0), 1);

    // TESTE 2: Adicionar um 4 de Ouros para formar um conjunto perfeito (5 e 4)
    struct Carta carta4_ouros = {4, 2}; // 4 de Ouros.
    mesa.tabuleiro[1] = add_carta(mesa.tabuleiro[1], carta4_ouros);
    
    // TESTE 3: Mover esse conjunto de 2 cartas para a coluna vazia (Tem de dar 1 / Válido)
    CU_ASSERT_EQUAL(pode_mover_conjunto(mesa, 1, 0, 2), 1);
}

void test_prepara_mesa_contagens(void){
    struct Mesa mesa = prepara_mesa(); // Cria uma mesa já preparada para o jogo.
    
    // O jogo tem de começar com 0 conjuntos completos
    CU_ASSERT_EQUAL(mesa.conjuntos_completos, 0);

    // As colunas 1 a 3 têm de ter 8 cartas
    CU_ASSERT_EQUAL(mesa.tabuleiro[0].quantidade, 8);
    CU_ASSERT_EQUAL(mesa.tabuleiro[1].quantidade, 8);
    CU_ASSERT_EQUAL(mesa.tabuleiro[2].quantidade, 8);

    // A coluna 4 tem de ter 7 cartas.
    CU_ASSERT_EQUAL(mesa.tabuleiro[3].quantidade, 7);
    // A coluna 5 tem de ter 6 cartas.
    CU_ASSERT_EQUAL(mesa.tabuleiro[4].quantidade, 6);
    // A coluna 6 tem de ter 5 cartas.
    CU_ASSERT_EQUAL(mesa.tabuleiro[5].quantidade, 5);
    // A coluna 7 tem de ter 4 cartas.
    CU_ASSERT_EQUAL(mesa.tabuleiro[6].quantidade, 4);
    // A coluna 8 tem de ter 3 cartas.
    CU_ASSERT_EQUAL(mesa.tabuleiro[7].quantidade, 3);
    // A coluna 9 tem de ter 2 cartas.
    CU_ASSERT_EQUAL(mesa.tabuleiro[8].quantidade, 2);
    // A coluna 10 tem de ter 1 cartas.
    CU_ASSERT_EQUAL(mesa.tabuleiro[9].quantidade, 1);
}

void test_pode_mover_conjunto(void){
    struct Mesa mesa = prepara_mesa();
    
    // Esvazia as duas primeiras colunas
    mesa.tabuleiro[0] = pilha_vazia();
    mesa.tabuleiro[1] = pilha_vazia();

    struct Carta carta10_copas = {10, 3}; // 10 de Copas
    struct Carta carta9_paus = {9, 0}; // 9 de Paus
    struct Carta carta8_paus = {8,0}; // 8 de Paus
    struct Carta carta7_paus = {7,0}; // 8 de Paus

    // Colocar um 10 de Copas na coluna de destino
    mesa.tabuleiro[1] = add_carta(mesa.tabuleiro[1], carta10_copas);

    // Criar um bloco de 3 cartas na origem: 9, 8 e 7 de Paus 
    mesa.tabuleiro[0] = add_carta(mesa.tabuleiro[0], carta9_paus);
    mesa.tabuleiro[0] = add_carta(mesa.tabuleiro[0], carta8_paus);
    mesa.tabuleiro[0] = add_carta(mesa.tabuleiro[0], carta7_paus);

    // Cenario 1: Movimento VÁLIDO (Mover as 3 cartas para cima do 10)
    CU_ASSERT_EQUAL(pode_mover_conjunto(mesa, 0, 1, 3), 1);

    // Cenario 2: Movimento INVÁLIDO (Misturar naipes)
    mesa.tabuleiro[0].cartas[1].naipe = 2; // O 8 de Paus fica um 8 de Ouros
    CU_ASSERT_EQUAL(pode_mover_conjunto(mesa, 0, 1, 3), 0); 

    // Cenário 3: Movimento Inválido (Mudança de valor)
    mesa.tabuleiro[0].cartas[1].naipe = 0; // O 8 de Ouros volta a ser um 8 de Paus
    mesa.tabuleiro[0].cartas[0].valor = 5; // O 9 de Paus fica um 5 de Paus
    CU_ASSERT_EQUAL(pode_mover_conjunto(mesa, 0, 1, 3), 0); 
}

void test_manipulacao_pilhas(void){
    struct Pilha pilha = pilha_vazia(); // Cria uma pilha vazia.
    struct Carta c1 = {10, 2}; // 10 de Ouros.
    struct Carta c2 = {11, 2}; // Valete de Ouros.

    pilha = add_carta(pilha, c1); // Adiciona o 10 de Ouros à pilha vazia.
    CU_ASSERT_EQUAL(pilha.quantidade, 1); // Verifica se a quantidade de cartas nessa piha é 1.
    CU_ASSERT_EQUAL(carta_de_cima(pilha).valor, 10); // Verifica de se ovalor da carta de cima da pilha é 10.

    pilha = add_carta(pilha, c2); // Adiciona o Valete de Ouros à pilha, que já tem o 10 de Ouros.
    CU_ASSERT_EQUAL(pilha.quantidade, 2); // Verifica se a quantidade de cartas nessa pilha é 2.
    CU_ASSERT_EQUAL(carta_de_cima(pilha).valor, 11); // Verifica se o valor da carta de cima da pilha é 11 (Valete).

    pilha = retira_carta_de_cima(pilha); // Retira a carta de cima da pilha (Valete de Ouros).
    CU_ASSERT_EQUAL(pilha.quantidade, 1); // Verifica se a quantidade de cartas nessa pilha é 1.
    CU_ASSERT_EQUAL(carta_de_cima(pilha).valor, 10); // Verifica se o valor da carta de cima é 10.
}

void test_limpar_conjuntos_completos(void) {
    struct Mesa mesa = prepara_mesa(); // Cria uma mesa já preparada para o jogo.
    mesa.conjuntos_completos = 0; // Garantir que nao tem nenhum conjunto completo.
    mesa.tabuleiro[0] = pilha_vazia(); // Esvaziar a primeira coluna.

    for (int i = 13; i >= 1; i--) {
        struct Carta cartas_espadas = {i, 1}; // Criar várias cartas de Espadas (Ás a Rei).
        mesa.tabuleiro[0] = add_carta(mesa.tabuleiro[0], cartas_espadas); // Adicionar o conjunto completo à primeira coluna.
    }

    // Antes de verificar, a coluna tem de ter 13 cartas
    CU_ASSERT_EQUAL(mesa.tabuleiro[0].quantidade, 13); 

    // Chamamos a função para limpar o conjunto completo.
    verifica_conjuntos(&mesa);

    // TESTE 1: As 13 cartas devem ter desaparecido (quantidade = 0)
    CU_ASSERT_EQUAL(mesa.tabuleiro[0].quantidade, 0);
    
    // TESTE 2: O nosso contador de vitória tem de ter subido para 1.
    CU_ASSERT_EQUAL(mesa.conjuntos_completos, 1);
}

void test_condicao_de_vitoria(void) {
    struct Mesa mesa;
    
    // Se tiver 0 conjuntos, o jogo continua (retorna 0)
    mesa.conjuntos_completos = 0;

    CU_ASSERT_EQUAL(verifica_estado_jogo(mesa), 0); 
    
    // Se tiver 1 conjuntos, o jogo continua (retorna 0)
    mesa.conjuntos_completos = 1;
    CU_ASSERT_EQUAL(verifica_estado_jogo(mesa), 0);

    // Se tiver 2 conjuntos, o jogo continua (retorna 0)
    mesa.conjuntos_completos = 2;
    CU_ASSERT_EQUAL(verifica_estado_jogo(mesa), 0);

    // Se tiver 3 conjuntos, o jogo continua (retorna 0)
    mesa.conjuntos_completos = 3;
    CU_ASSERT_EQUAL(verifica_estado_jogo(mesa), 0);

    // Se chegar aos 4 conjuntos, o jogo tem de declarar vitória! (retorna 1)
    mesa.conjuntos_completos = 4;
    CU_ASSERT_EQUAL(verifica_estado_jogo(mesa), 1); 
}

int main(){
    if (CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    CU_pSuite suite_cartas = CU_add_suite("Suite_Cartas_e_Regras", NULL, NULL);
    if (NULL == suite_cartas){
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(suite_cartas, "Testar add e retira carta", test_manipulacao_pilhas);
    CU_add_test(suite_cartas, "Testar distribuicao da mesa", test_prepara_mesa_contagens);
    CU_add_test(suite_cartas, "Testar bloqueios de mover conjuntos", test_pode_mover_conjunto);  
    CU_add_test(suite_cartas, "Testar se a pilha inicia a 0", test_pilha_vazia);
    CU_add_test(suite_cartas, "Testar jogada valida de 1 carta", test_pode_mover_carta_valido);
    CU_add_test(suite_cartas, "Testar mover para destino vazio", test_mover_para_coluna_vazia);
    CU_add_test(suite_cartas, "Testar limpeza de naipe de Rei a As", test_limpar_conjuntos_completos);
    CU_add_test(suite_cartas, "Testar estado de vitoria final", test_condicao_de_vitoria);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}