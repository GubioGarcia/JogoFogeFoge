#include <stdio.h>

int main () {
    char mapa[5][10+1];

    FILE* arqAux;
    arqAux = fopen("mapa.txt", "r");
    if (arqAux == 0) {
        printf ("Erro na leitura do manpa\n");
        return 1;
    }
    
    for (int i = 0; i < 5; i++) { // leitura do mapa
        fscanf (arqAux, "%s", mapa[i]);
    }

    for (int i = 0; i < 5; i++) { // Impressão mapa
        printf ("%s\n", mapa[i]);
    }
}