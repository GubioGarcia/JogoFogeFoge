#include "ui.h"

char desenhoParede[4][7] = {
	{"......" },
	{"......" },
	{"......" },
	{"......" }
};

char desenhoFantasma[4][7] = {
	{" .-.  " },
	{"| OO| " },
	{"|   | " },
	{"'^^^' " }
};

char desenhoHeroi[4][7] = {
	{" .--. "  },
	{"/ _.-'"  },
	{"\\  '-." },
	{" '--' "  }
};

char desenhoPilula[4][7] = {
	{"      "},
	{" .-.  "},
	{" '-'  "},
	{"      "}
};

char desenhoVazio[4][7] = {
	{"      "},
	{"      "},
	{"      "},
	{"      "}
};

void imprimirParte(char desenho[4][7], int parte) {
	printf("%s", desenho[parte]);
}

void imprimirMapa(MAPA* map) {
	for(int i = 0; i < map->linhas; i++) {
		for(int parte = 0; parte < 4; parte++) {
			for(int j = 0; j < map->colunas; j++) {
				switch(map->matriz[i][j]) {
					case FANTASMA:
						imprimirParte(desenhoFantasma, parte);
						break;
					case HEROI:
						imprimirParte(desenhoHeroi, parte);
						break;
					case PILULA:
						imprimirParte(desenhoPilula, parte);
						break;
					case PAREDE:
						imprimirParte(desenhoParede, parte);
						break;
					case VAZIO:
						imprimirParte(desenhoVazio, parte);
						break;
				}
			}
			printf("\n");
		}
	}
}