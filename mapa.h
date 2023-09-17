#include <stdio.h>
#include <stdlib.h>

#define HEROI '@'
#define VAZIO '.'

struct mapa {
    char** matriz;
    int linhas;
    int colunas;
};
typedef struct mapa MAPA;

struct posicao {
    int x;
    int y;
};
typedef struct posicao POSICAO;

void lerMapa (MAPA* map);
void imprimirMapa (MAPA* map);
void alocarMemoriaMapa (MAPA* map);
void liberarMemoriaMapa (MAPA* map);
void encontrarMapa (MAPA* map, POSICAO* pos, char c);

int eVazia (MAPA* map, int x, int y);
int eValida (MAPA* map, int x, int y);
void andarNoMapa (MAPA* map, int xOrigem, int yOrigem, int xDestino, int yDestino);