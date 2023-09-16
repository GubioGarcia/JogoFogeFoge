#include <stdio.h>
#include <stdlib.h>

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