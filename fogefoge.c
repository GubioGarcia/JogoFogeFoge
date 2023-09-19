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

void moverFantasmas () {
    MAPA mapCopia;
    copiarMapa(&mapCopia, &map);

    for (int i = 0; i < mapCopia.linhas; i++) {
        for (int j = 0; j < mapCopia.colunas; j++) {
            if (mapCopia.matriz[i][j] == FANTASMA) {
                if (eValida(&map, i, j+1) && eVazia(&map, i, j+1)) {
                    int xDestino;
                    int yDestino;

                    int encontrou = direcaoFantasma(i, j, &xDestino, &yDestino);
                    if (encontrou) {
                        andarNoMapa(&map, i, j, xDestino, yDestino);
                    }
                }
            }
        }
    }
    liberarMemoriaMapa(&mapCopia);
}

int direcaoFantasma (int xAtual, int yAtual, int* xDestino, int* yDestino) {
    int opcoes[4][2] = {
        { xAtual, yAtual+1},
        { xAtual+1, yAtual},
        { xAtual, yAtual-1},
        { xAtual-1, yAtual}
    };

    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int posicao = rand() % 4;

        if (eValida(&map, opcoes[posicao][0], opcoes[posicao][1]) && eVazia(&map, opcoes[posicao][0], opcoes[posicao][1])) {
            *xDestino = opcoes[posicao][0];
            *yDestino = opcoes[posicao][1];
        }
    }
}

int main () {
    lerMapa(&map);
    encontrarMapa (&map, &posHeroi, HEROI);

    do {
        imprimirMapa(&map);

        char comando;
        scanf(" %c", &comando);
        moverHeroi(comando);
        moverFantasmas();
    } while (!acabou());

    liberarMemoriaMapa(&map);
}