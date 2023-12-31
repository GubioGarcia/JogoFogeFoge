#include "fogefoge.h"

MAPA map;
POSICAO posHeroi;
int pilulasHeroi = 0;

int acabou () { // Verificar fim do jogo
    POSICAO pos;
    int encontrarHeroi = encontrarMapa(&map, &pos, HEROI);
    return !encontrarHeroi;
}

int validarDirecao (char direcao) { // Validar direção de entrada do usuário
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
    
    if (ePersonagem(&map, PILULA, proximoX, proximoY)) pilulasHeroi++;

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

int direcaoFantasma (int xAtual, int yAtual, int* xDestino, int* yDestino) { // Movimentar fantasmas randomicamente
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

void explodirPilulaRecursivo() {
    if (!pilulasHeroi) return;

    // Explodir nas quatro direções principais
    explodirPilula(posHeroi.x, posHeroi.y, 0, 1, 2); // Explodir para direita
    explodirPilula(posHeroi.x, posHeroi.y, 0, -1, 2); // Explodir para esquerda
    explodirPilula(posHeroi.x, posHeroi.y, 1, 0, 2); // Explodir para cima
    explodirPilula(posHeroi.x, posHeroi.y, -1, 0, 2); // Explodir para baixo

    // Explodir nas quatro direções diagonais
    explodirPilula(posHeroi.x, posHeroi.y, -1, -1, 2); // Explodir para cima e para a esquerda
    explodirPilula(posHeroi.x, posHeroi.y, -1, 1, 2); // Explodir para cima e para a direita
    explodirPilula(posHeroi.x, posHeroi.y, 1, -1, 2); // Explodir para baixo e para a esquerda
    explodirPilula(posHeroi.x, posHeroi.y, 1, 1, 2); // Explodir para baixo e para a direita

    pilulasHeroi = 0;
}

void explodirPilula (int x, int y, int somaX, int somaY, int qtd) {
    if (qtd == 0) return;

    int novoX = x + somaX;
    int novoY = y + somaY;

    if (!eValida(&map, novoX, novoY)) return;
    if (eParede(&map, novoX, novoY)) return;

    map.matriz[novoX][novoY] = VAZIO;
    explodirPilula(novoX, novoY, somaX, somaY, qtd--);
}

int menuIniciar() {
    int comando;

    while (1) { // Loop externo para manter o menu ativo
        printf("\n**BEM VINDO AO FOGE-FOGE**\n");
        printf("\nMENU INICIAR: \n");
        printf("Digite: '0' para INSTRUCOES ou '1' para INICIAR: \n");
        
        int scanfResult = scanf(" %d", &comando);

        // Verifica se a entrada foi um número inteiro válido
        if (scanfResult != 1) {
            printf("Entrada inválida. Digite apenas '0' para INSTRUCOES ou '1' para INICIAR.\n");
            // Limpa o buffer de entrada
            while (getchar() != '\n');
            continue;
        }

        if (comando == 0) { // INSTRUCOES DE JOGABILIDADE
            printf("\nINSTRUCOES DE JOGABILIDADE\n");
            printf("Bem-vindo ao Foge-Foge! Neste jogo, voce controlara um heroi que deve evitar fantasmas enquanto coleta pilulas no mapa.\n");
            printf("\nControles:\n");
            printf("Use as teclas wasd para mover o heroi pelo mapa.\n");
            printf("w: Mover para cima\na: Mover para a esquerda\ns: Mover para baixo\nd: Mover para a direita\n");
            printf("\nPressione a tecla 'b' para fazer o heroi explodir as pilulas que coletou. Isso eliminara fantasmas que estiverem ate duas casas proximas de seu heroi nas oito direcoes possiveis.\n");
            printf("Sobreviva o quanto puder. Colete pilulas e exploda fantasmas para marcar pontos\n\n");

            int auxMenu = -1;
            while (auxMenu != 0 && auxMenu != 1) {
                printf("Digite '0' para retornar ao MENU e '1' para INICIAR: ");
                int scanfResult = scanf(" %d", &auxMenu);

                // Verifica se a entrada foi um número inteiro válido
                if (scanfResult != 1) {
                    printf("OPCAO INVALIDA. Digite '0' para retornar ao MENU ou '1' para INICIAR: ");
                    while (getchar() != '\n'); // Limpa o buffer de entrada
                    continue;
                }
            }
            
            if (auxMenu == 0) continue; // Volta para o MENU
            else if (auxMenu == 1) return 1; // INICIAR JOGO

        } else if (comando == 1) { // INICIAR JOGO
            return 1;
        } else {
            printf("OPCAO INVALIDA. Digite '0' para INSTRUCOES ou '1' para INICIAR: ");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
    }
}

int main () {
    if (!menuIniciar()) return 0;

    lerMapa(&map);
    encontrarMapa (&map, &posHeroi, HEROI);

    do {
        printf("\nPilulas: %s\n", (pilulasHeroi ? "SIM" : "NAO"));
        system("cls || clear"); // Limpa a tela
        imprimirMapa(&map);

        char comando;
        comando = getch(); // APENAS NO WINDOWNS - inibe necessidade do 'ENTER' após a entrada do comando
        //scanf(" %c", &comando);

        if (comando == BOMBA) explodirPilulaRecursivo();
        else moverHeroi(comando);
        moverFantasmas();
        
    } while (!acabou());

    imprimirMapa(&map);
    liberarMemoriaMapa(&map);
}