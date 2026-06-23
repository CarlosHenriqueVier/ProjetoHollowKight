#define _CRT_SECURE_NO_WARNINGS
#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

char** leituraMapa(infoMapa info) {
    FILE* abreMapa = fopen(info.localMapa, "r");
    if (abreMapa == NULL) return NULL;

    char** matriz = (char**)malloc(info.linhas * sizeof(char*));
    for (int i = 0; i < info.linhas; i++) {
        matriz[i] = (char*)malloc((info.colunas + 5) * sizeof(char));
        if (fgets(matriz[i], info.colunas + 5, abreMapa) == NULL) {
            matriz[i][0] = '\0';
        }
    }
    fclose(abreMapa);
    return matriz;
}


void liberaMapa(char** matriz, int linhas) {
    if (matriz == NULL) return;
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void loadMapa() {
    map.matrizMapa = leituraMapa(map);
}

void unloadMapa() {
    liberaMapa(map.matrizMapa, map.linhas);
    map.matrizMapa = NULL;
}


// Retorna true se o bloco na posição (px, py) do mundo é sólido
bool blocoSolido(float px, float py) {
    int col = (int)(px / bloco.largura);
    int lin = (int)(py / bloco.altura);

    // Clamp para não sair da matriz
    if (col < 0) col = 0;
    if (col >= map.colunas) col = map.colunas - 1;
    if (lin < 0) lin = 0;
    if (lin >= map.linhas)  lin = map.linhas  - 1;

    char c = map.matrizMapa[lin][col];
    return c == 'P';
}

void desenhaMapa() {
    if (map.matrizMapa == NULL) return;

    for (int i = 0; i < map.linhas; i++) {
        for (int j = 0; j < map.colunas; j++) {
            char c = map.matrizMapa[i][j];
            
            // IGNORA as letras de nascimento (J, M) para não pintar blocos fixos pretos ou vermelhos nelas
            if (c == ' ' || c == '\n' || c == '\0' || c == '\r' || c == 'J' || c == 'M') continue;

            float posX = j * bloco.largura;
            float posY = i * bloco.altura;

            if      (c == 'P') DrawRectangle((int)posX, (int)posY, (int)bloco.largura, (int)bloco.altura, BLACK);
            else if (c == 'C') DrawRectangle((int)posX, (int)posY, (int)bloco.largura, (int)bloco.altura, PURPLE);
            else if (c == 'A') DrawRectangle((int)posX, (int)posY, (int)bloco.largura, (int)bloco.altura, YELLOW);
            else if (c == 'H') DrawRectangle((int)posX, (int)posY, (int)bloco.largura, (int)bloco.altura, BLUE);
        }
    }
}