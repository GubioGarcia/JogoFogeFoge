#include "mapa.h"

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
