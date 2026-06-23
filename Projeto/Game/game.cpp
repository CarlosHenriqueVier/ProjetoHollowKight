#include "game.h"
#include "../Mapa/mapa.h"
#include "../Personagem/personagem.h"
#include "../Inimigo/inimigo.h"
#include <raylib.h>
#include "../Hud/hud.h"
#include <stdio.h>

void inicializaPosicoesEntidades() {
    if (map.matrizMapa == NULL) return;

    quantidadeInimigos = 0; // Reseta o contador ao carregar o jogo

    for (int i = 0; i < map.linhas; i++) {
        for (int j = 0; j < map.colunas; j++) {
            char c = map.matrizMapa[i][j];
            float posX = j * bloco.largura;
            float posY = i * bloco.altura;

            if (c == 'J') {
                personagem.posicao = { posX, posY };
                personagem.posicaoInicial = { posX, posY };
            }
            else if (c == 'M') {
                if (quantidadeInimigos < MAX_INIMIGOS) {
                    // Configura os dados base deste inimigo específico dentro do array
                    listaInimigos[quantidadeInimigos].posicao = { posX, posY };
                    listaInimigos[quantidadeInimigos].posicaoInicial = { posX, posY };
                    listaInimigos[quantidadeInimigos].largura = 30;
                    listaInimigos[quantidadeInimigos].altura = 30;
                    listaInimigos[quantidadeInimigos].olhandoDireita = true;
                    listaInimigos[quantidadeInimigos].dados.hp = 100;
                    listaInimigos[quantidadeInimigos].dados.mp = 0; // Usado para velocidade vertical
                    listaInimigos[quantidadeInimigos].dados.vivo = true;

                    quantidadeInimigos++;
                }
            }
        }
    }
    TraceLog(LOG_INFO, "Total de inimigos carregados com sucesso: %d", quantidadeInimigos);
}

void loadJogo() {
    loadMapa();
    inicializaPosicoesEntidades(); // Varre o mapa e posiciona Player e os Inimigos
    loadInimigo();
    tela.fundoJogo = LoadTexture("Texturas/Fundos/Jogo/FundoJogo.png");
}

void unloadJogo() {
    unloadMapa();
    unloadPersonagem();
    unloadInimigo();
    UnloadTexture(tela.fundoJogo); 
}

void updateJogo() {
    updatePersonagem();
    updateInimigo(); // Atualiza todos os inimigos da lista

    tela.camera.target = {
        personagem.posicao.x + personagem.largura / 2.0f,
        personagem.posicao.y + personagem.altura / 2.0f
    };
    tela.camera.offset = {
        tela.largura / 2.0f,
        tela.altura / 2.0f
    };

    // Limita câmera nas bordas do mapa
    float mapaLargura = map.colunas * bloco.largura;
    float mapaAltura  = map.linhas  * bloco.altura;
    float margemH     = (tela.largura  / 2.0f) / tela.camera.zoom;
    float margemV     = (tela.altura   / 2.0f) / tela.camera.zoom;

    if (tela.camera.target.x < margemH)               tela.camera.target.x = margemH;
    if (tela.camera.target.x > mapaLargura - margemH) tela.camera.target.x = mapaLargura - margemH;
    if (tela.camera.target.y < margemV)               tela.camera.target.y = margemV;
    if (tela.camera.target.y > mapaAltura  - margemV) tela.camera.target.y = mapaAltura  - margemV;
}

void drawFundo() {
    float fw = (float)tela.fundoJogo.width;
    float fh = (float)tela.fundoJogo.height;
    float mapaLargura = map.colunas * bloco.largura;
    float mapaAltura  = map.linhas  * bloco.altura;

    for (float x = 0; x < mapaLargura; x += fw) {
        for (float y = 0; y < mapaAltura; y += fh) {
            DrawTextureV(tela.fundoJogo, { x, y }, WHITE);
        }
    }
}

void drawJogo() {
    ClearBackground(PURPLE);

    BeginMode2D(tela.camera);
        desenhaMapa();
        desenhaPersonagem();
        desenhaInimigo(); // Desenha todos os inimigos da lista
    EndMode2D();
    
    desenhaHud(); 
}