#include <stdio.h>
#include <stdlib.h>

char** mapa;
int linhasMapa, colunasMapa;

void liberarMemoriaMapa() {
    // Liberar memória matriz mapa
    for (int i = 0; i < linhasMapa; i++) {
        free(mapa[i]);
    }
    free(mapa);
}

void alocarMemoriaMapa() {
    // Declaração dinâmica da matriz mapa
    mapa = malloc(sizeof(char*) * linhasMapa);
    for (int i = 0; i < linhasMapa; i++) {
        mapa[i] = malloc(sizeof(char) * (colunasMapa + 1));
    }
}

void lerMapa() {
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

int main () {
    lerMapa();

    for (int i = 0; i < 5; i++) { // Impressão mapa
        printf ("%s\n", mapa[i]);
    }

    liberarMemoriaMapa();
}