#include "menu.h"
#include "../Game/game.h"
#include <raylib.h>

enum Estado { ESTADO_MENU, ESTADO_JOGANDO };
Estado estadoAtual = ESTADO_MENU;

void loadMenu() {
    tela.menuImagem[0] = LoadTexture("Texturas/Fundos/Menu/FundoMenu.png");
}

void unloadMenu() {
    UnloadTexture(tela.menuImagem[0]);
}

void desenhaMenu() {
    if (estadoAtual == ESTADO_MENU) {
        if (IsKeyPressed(KEY_ENTER)) estadoAtual = ESTADO_JOGANDO;
    }
    else if (estadoAtual == ESTADO_JOGANDO) {
        updateJogo();
        if (IsKeyPressed(KEY_M)) estadoAtual = ESTADO_MENU;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    if (estadoAtual == ESTADO_MENU) {
        Rectangle source = { 0, 0, (float)tela.menuImagem[0].width, (float)tela.menuImagem[0].height };
        Rectangle dest   = { 0, 0, (float)tela.largura, (float)tela.altura };
        DrawTexturePro(tela.menuImagem[0], source, dest, { 0 }, 0.0f, WHITE);
    }
    else if (estadoAtual == ESTADO_JOGANDO) {
        drawJogo();
    }

    EndDrawing();
}
