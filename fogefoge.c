#include "fogefoge.h"

MAPA map;
POSICAO posHeroi;

int acabou () {
    return 0;
}

int validarDirecao (char direcao) {
    return direcao == 'a' || direcao == 'w' || direcao == 's' || direcao == 'd';
}

void moverHeroi (char direcao) {
    if (!validarDirecao(direcao)) return;

    int proximoX = posHeroi.x;
    int proximoY = posHeroi.y;

    switch (direcao) {
        case ESQUERDA:
            proximoY--;
            break;
        case CIMA:
            proximoX--;
            break;
        case BAIXO:
            proximoX++;
            break;
        case DIREITA:
            proximoY++;
            break;
    }

    if (!eValida(&map, proximoX, proximoY)) return;
    if (!eVazia(&map, proximoX, proximoY)) return;
    
    andarNoMapa(&map, posHeroi.x, posHeroi.y, proximoX, proximoY);
    posHeroi.x = proximoX;
    posHeroi.y = proximoY;
}

int main () {
    lerMapa(&map);
    encontrarMapa (&map, &posHeroi, '@');

    do {
        imprimirMapa(&map);

        char comando;
        scanf(" %c", &comando);
        moverHeroi(comando);
    } while (!acabou());

    liberarMemoriaMapa(&map);
}