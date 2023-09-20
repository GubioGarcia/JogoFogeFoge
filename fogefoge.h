#ifndef FOGEFOGE_H
#define FOGEFOGE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapa.h"
#include "ui.h"

#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define BOMBA 'b'

int acabou();
int validarDirecao(char direcao);
void moverHeroi(char direcao);
void moverFantasmas();
int direcaoFantasma(int xAtual, int yAtual, int* xDestino, int* yDestino);
void explodirPilula(int x, int y, int somaX, int somaY, int qtd);
void explodirPilulaRecursivo ();

#endif