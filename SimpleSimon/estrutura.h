struct Carta{
    int valor; // 1(Ás) - 13 (Rei).
    char naipe; // {♧,♤,♢,♡}.
};

struct Pilha{
    struct Carta cartas[52]; // Array com espaço para até 52 cartas.
    int quantidade; // Número de cartas no baralho atualmente.
};

struct Mesa{
    struct Pilha baralho;
    struct Pilha tabuleiro[10]; // Conjunto de 10 pilhas.
    int conjuntos_completos;
};