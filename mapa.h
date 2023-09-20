#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|' 
#define PAREDE_ORIZONTAL '-'
#define PILULA '*'

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
void copiarMapa (MAPA* destino, MAPA* origem);
int encontrarMapa (MAPA* map, POSICAO* pos, char c);

int eVazia (MAPA* map, int x, int y);
int eValida (MAPA* map, int x, int y);
int eParede (MAPA* map, int x, int y);
int ePersonagem (MAPA* map, char personagem, int x, int y);
int podeAndar (MAPA* map, char personagem, int x, int y);
void andarNoMapa (MAPA* map, int xOrigem, int yOrigem, int xDestino, int yDestino);

#endif