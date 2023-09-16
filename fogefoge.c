#include "fogefoge.h"

MAPA map;
POSICAO posHeroi;

int acabou () {
    return 0;
}

void move (char direcao) {
    if (direcao != 'a' && direcao != 'w' && direcao != 's' && direcao != 'd') return;

    map.matriz[posHeroi.x][posHeroi.y] = '.';

    switch (direcao) {
        case 'a':
            map.matriz[posHeroi.x][posHeroi.y-1] = '@';
            posHeroi.y--;
            break;
        case 'w':
            map.matriz[posHeroi.x-1][posHeroi.y] = '@';
            posHeroi.x--;
            break;
        case 's':
            map.matriz[posHeroi.x+1][posHeroi.y] = '@';
            posHeroi.x++;
            break;
        case 'd':
            map.matriz[posHeroi.x][posHeroi.y+1] = '@';
            posHeroi.y++;
            break;
    }
}

int main () {
    lerMapa(&map);
    encontrarMapa (&map, &posHeroi, '@');

    do
    {
        imprimirMapa(&map);

        char comando;
        scanf(" %c", &comando);
        move(comando);
    } while (!acabou());

    liberarMemoriaMapa(&map);
}