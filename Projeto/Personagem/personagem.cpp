#include "personagem.h"
#include "../Mapa/mapa.h"
#include <raylib.h>

void loadPersonagem() {
    personagem.imagem[0] = LoadTexture("Texturas/Personagem/Personagem.png");
    personagem.imagem[1] = LoadTexture("Texturas/Personagem/InvertePersonagem.png");
}

void unloadPersonagem() {
    UnloadTexture(personagem.imagem[0]);
    UnloadTexture(personagem.imagem[1]);
}

void updatePersonagem() {
    personagem.posicao = movimentaPersonagem(personagem.posicao);
}

void desenhaPersonagem() {
    DrawTextureEx(personagem.imagem[0], personagem.posicao, 0, 0.3f, WHITE);
}

Vector2 movimentaPersonagem(Vector2 posicaoAtual) {
    float velocidade = 5.0f;
    static float velocidadeY = 0.0f;

    velocidadeY += 0.5f;
    posicaoAtual.y += velocidadeY;

    int coluna = (int)((posicaoAtual.x + personagem.largura / 2.0f) / bloco.largura);
    int linha   = (int)((posicaoAtual.y + personagem.altura) / bloco.altura);

    if (coluna < 0) coluna = 0;
    if (coluna >= map.colunas) coluna = map.colunas - 1;
    if (linha  < 0) linha  = 0;
    if (linha  >= map.linhas)  linha  = map.linhas - 1;

    if (map.matrizMapa[linha][coluna] == 'P' && velocidadeY >= 0) {
        velocidadeY = 0;
        posicaoAtual.y = (linha * bloco.altura) - personagem.altura;
    }

    int linhaMeio      = (int)((posicaoAtual.y + personagem.altura / 2.0f) / bloco.altura);
    int colunaDireita  = (int)((posicaoAtual.x + personagem.largura) / bloco.largura);
    int colunaEsquerda = (int)(posicaoAtual.x / bloco.largura);

    if (linhaMeio     < 0) linhaMeio = 0;
    if (linhaMeio     >= map.linhas)  linhaMeio     = map.linhas  - 1;
    if (colunaDireita >= map.colunas) colunaDireita  = map.colunas - 1;
    if (colunaEsquerda < 0)           colunaEsquerda = 0;

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        if (map.matrizMapa[linhaMeio][colunaDireita] != 'P')
            posicaoAtual.x += velocidade;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        if (map.matrizMapa[linhaMeio][colunaEsquerda] != 'P')
            posicaoAtual.x -= velocidade;
    }
    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && map.matrizMapa[linha][coluna] == 'P') {
        velocidadeY = -10.0f;
    }

    return posicaoAtual;
}
