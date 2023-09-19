#include "mapa.h"

void andarNoMapa (MAPA* map, int xOrigem, int yOrigem, int xDestino, int yDestino) {
    char personagem = map->matriz[xOrigem][yOrigem];
    map->matriz[xDestino][yDestino] = personagem;
    map->matriz[xOrigem][yOrigem] = VAZIO;
}

int eValida (MAPA* map, int x, int y) {
    if (x >= map->linhas) return 0;
    if (y >= map->colunas) return 0;
    return 1;
}

int eVazia(MAPA* map, int x, int y) {
    return map->matriz[x][y] == VAZIO;
}

void encontrarMapa (MAPA* map, POSICAO* pos, char c) {
    for (int i = 0; i < map->linhas; i++) {
        for (int j = 0; j < map->colunas; j++) {
            if (map->matriz[i][j] == c) {
                pos->x = i;
                pos->y = j;
                break;
            }
        }
    }
}

void liberarMemoriaMapa (MAPA* map) {
    // Liberar memória matriz mapa
    for (int i = 0; i < map->linhas; i++) {
        free(map->matriz[i]);
    }
    free(map->matriz);
}

void alocarMemoriaMapa (MAPA* map) {
    // Declaração dinâmica da matriz mapa
    map->matriz = malloc(sizeof(char*) * map->linhas);
    for (int i = 0; i < map->linhas; i++) {
        map->matriz[i] = malloc(sizeof(char) * (map->colunas + 1));
    }
}

void lerMapa (MAPA* map) {
    FILE* arqMapa;
    arqMapa = fopen("mapa.txt", "r");
    if (arqMapa == 0) {
        printf ("Erro na leitura do manpa\n");
        exit(1);
    }

    fscanf (arqMapa, "%d %d", &map->linhas, &map->colunas);

    alocarMemoriaMapa(map);

    for (int i = 0; i < 5; i++) { // leitura do mapa
        fscanf (arqMapa, "%s", map->matriz[i]);
    }
    fclose(arqMapa);
}

void imprimirMapa (MAPA* map) {
    for (int i = 0; i < 5; i++) {
        printf ("%s\n", map->matriz[i]);
    }
}

void copiarMapa (MAPA* destino, MAPA* origem) {
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    alocarMemoriaMapa(destino);
    for (int i = 0; i < origem->linhas; i++) {
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}
