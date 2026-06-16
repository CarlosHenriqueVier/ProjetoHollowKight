#include "game.h"
#include "../Mapa/mapa.h"
#include "../Personagem/personagem.h"
#include <raylib.h>

void loadJogo() {
    loadMapa();
    loadPersonagem();
}

void unloadJogo() {
    unloadMapa();
    unloadPersonagem();
}

void updateJogo() {
    updatePersonagem();

    tela.camera.target = {
        personagem.posicao.x + personagem.largura / 2.0f,
        personagem.posicao.y + personagem.altura / 2.0f
    };
    tela.camera.offset = {
        tela.largura / 2.0f,
        tela.altura / 2.0f
    };
}

void drawJogo() {
    BeginMode2D(tela.camera);
        desenhaMapa();
        desenhaPersonagem();
    EndMode2D();
}
