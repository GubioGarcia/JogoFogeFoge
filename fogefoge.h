#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'

int acabou();
int validarDirecao (char direcao);
void moverHeroi(char direcao);