#include <stdio.h>
#include <stdlib.h>

char** mapa;
int linhasMapa, colunasMapa;

void liberarMemoriaMapa () {
    // Liberar memória matriz mapa
    for (int i = 0; i < linhasMapa; i++) {
        free(mapa[i]);
    }
    free(mapa);
}

void alocarMemoriaMapa () {
    // Declaração dinâmica da matriz mapa
    mapa = malloc(sizeof(char*) * linhasMapa);
    for (int i = 0; i < linhasMapa; i++) {
        mapa[i] = malloc(sizeof(char) * (colunasMapa + 1));
    }
}

void lerMapa () {
    FILE* arqMapa;
    arqMapa = fopen("mapa.txt", "r");
    if (arqMapa == 0) {
        printf ("Erro na leitura do manpa\n");
        exit(1);
    }

    fscanf (arqMapa, "%d %d", &linhasMapa, &colunasMapa);

    alocarMemoriaMapa();

    for (int i = 0; i < 5; i++) { // leitura do mapa
        fscanf (arqMapa, "%s", mapa[i]);
    }
    fclose(arqMapa);
}

void imprimirMapa () {
    for (int i = 0; i < 5; i++) {
        printf ("%s\n", mapa[i]);
    }
}

int acabou () {
    return 0;
}

void move (char direcao) {
    int x;
    int y;

    // acha a posicao do personagem
    for (int i = 0; i < linhasMapa; i++) {
        for (int j = 0; j < colunasMapa; j++) {
            if (mapa[i][j] == '@') {
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (direcao) {
        case 'a':
            mapa[x][y-1] = '@';
            break;
        case 'w':
            mapa[x-1][y] = '@';
            break;
        case 's':
            mapa[x+1][y] = '@';
            break;
        case 'd':
            mapa[x][y+1] = '@';
            break;
    }

    mapa[x][y] = '.';
}

int main () {
    lerMapa();

    do
    {
        imprimirMapa();

        char comando;
        scanf(" %c", &comando);
        move(comando);
    } while (!acabou());

    liberarMemoriaMapa();
}