#include "fogefoge.h"

MAPA map;
POSICAO posHeroi;
int pilulasHeroi = 0;

int acabou () {
    POSICAO pos;
    int encontrarHeroi = encontrarMapa(&map, &pos, HEROI);
    return !encontrarHeroi;
}

int validarDirecao (char direcao) {
    return direcao == ESQUERDA || direcao == CIMA || direcao == BAIXO || direcao == DIREITA;
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

    if (!podeAndar(&map, HEROI, proximoX, proximoY)) return;
    
    if (ePersonagem(&map, PILULA, proximoX, proximoY)) pilulasHeroi = 1;

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
                int xDestino;
                int yDestino;

                int encontrou = direcaoFantasma(i, j, &xDestino, &yDestino);

                if (encontrou) andarNoMapa(&map, i, j, xDestino, yDestino);
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

        if (podeAndar(&map, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
            *xDestino = opcoes[posicao][0];
            *yDestino = opcoes[posicao][1];

            return 1;
        }
    }
    return 0;
}

void explodirPilulaRecursivo () {
    if (!pilulasHeroi) return;    

    explodirPilula(posHeroi.x, posHeroi.y, 0, 1, 3); //explodir para direita
    explodirPilula(posHeroi.x, posHeroi.y, 0, -1, 3);//explodir para esquerda
    explodirPilula(posHeroi.x, posHeroi.y, 1, 0, 3); //explodir para cima
    explodirPilula(posHeroi.x, posHeroi.y, -1, 0, 3); //explodir para baixo

    pilulasHeroi = 0;
}

void explodirPilula (int x, int y, int somaX, int somaY, int qtd) {
    if (qtd == 0) return;

    int novoX = x + somaX;
    int novoY = y + somaY;

    if (!eValida(&map, novoX, novoY)) return;
    if (eParede(&map, novoX, novoY)) return;

    map.matriz[novoX][novoY] = VAZIO;
    explodirPilula(novoX, novoY, somaX, somaY, qtd-1);
}

int main () {
    lerMapa(&map);
    encontrarMapa (&map, &posHeroi, HEROI);

    do {
        printf("\nPilulas: %s\n", (pilulasHeroi ? "SIM" : "NAO"));
        imprimirMapa(&map);

        char comando;
        scanf(" %c", &comando);
        moverHeroi(comando);

        if (comando == BOMBA) explodirPilulaRecursivo();     

        moverFantasmas();
    } while (!acabou());

    liberarMemoriaMapa(&map);
}