struct Carta{
    int valor; // 1(Ás) - 13 (Rei).
    char naipe; // {♧,♤,♢,♡}.
};

struct Pilha{
    struct Carta cartas[52]; // Array com espaço para até 52 cartas.
    int quantidade; // Número de cartas no baralho atualmente.
};

struct Mesa{
    struct Pilha tabuleiro[7]; // Conjunto de 7 pilhas. 
    struct Pilha baralho; // Pilha onde o utilizador pode biscar.
    struct Pilha descarte; // Pilha que o utilizador coloca as cartas descartadas.
};