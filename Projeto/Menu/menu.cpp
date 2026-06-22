#include "menu.h"
#include "../Game/game.h"
#include <raylib.h>
#include <cstdlib>

enum Estado { ESTADO_MENU, ESTADO_JOGANDO, ESTADO_CONFIGURACOES };
Estado estadoAtual = ESTADO_MENU;

const int totalOpcoes = 4;
int opcaoSelecionada  = 0;

// Posicao central Y de cada botao na tela (ajuste se necessario)
const int botoesY[] = { 294, 361, 428, 495 };

// Largura e altura que cada botao vai ser desenhado na tela
const int botaoW = 320;
const int botaoH = 60;

const char* opcoesConfig[] = { "Volume", "Voltar" };
const int totalConfig = 2;
int opcaoConfig = 0;
const int botoesConfigY[] = { 294, 361 };

void loadMenu() {
    tela.menuImagem[0] = LoadTexture("Texturas/Fundos/Menu/FundoMenu.png");
    tela.menuBotoes[0] = LoadTexture("Texturas/Fundos/Menu/BotaoJogar.png");
    tela.menuBotoes[1] = LoadTexture("Texturas/Fundos/Menu/BotaoCarregar.png");
    tela.menuBotoes[2] = LoadTexture("Texturas/Fundos/Menu/BotaoOpcoes.png");
    tela.menuBotoes[3] = LoadTexture("Texturas/Fundos/Menu/BotaoSair.png");
}

void unloadMenu() {
    UnloadTexture(tela.menuImagem[0]);
    for (int i = 0; i < 4; i++)
        UnloadTexture(tela.menuBotoes[i]);
}

static void desenhaFundoMenu() {
    Rectangle source = { 0, 0, (float)tela.menuImagem[0].width, (float)tela.menuImagem[0].height };
    Rectangle dest   = { 0, 0, (float)tela.largura, (float)tela.altura };
    DrawTexturePro(tela.menuImagem[0], source, dest, { 0 }, 0.0f, WHITE);
}

static void desenhaBotao(int index, int selecionado) {
    Texture2D tex = tela.menuBotoes[index];

    // Calcula posicao centralizada
    float x = tela.largura  / 2.0f - botaoW / 2.0f;
    float y = botoesY[index] - botaoH / 2.0f;

    // Esmaece o botao Carregar (nao implementado)
    Color cor = (index == 1) ? DARKGRAY : WHITE;

    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest   = { x, y, (float)botaoW, (float)botaoH };
    DrawTexturePro(tex, source, dest, { 0 }, 0.0f, cor);

    // Borda branca no botao selecionado
    if (index == selecionado && index != 1) {
        DrawRectangleLinesEx({ x - 2, y - 2, (float)botaoW + 4, (float)botaoH + 4 }, 2, WHITE);
    }
}

static void updateMenuPrincipal() {
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        opcaoSelecionada = (opcaoSelecionada + 1) % totalOpcoes;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        opcaoSelecionada = (opcaoSelecionada - 1 + totalOpcoes) % totalOpcoes;

    // Pula o Carregar (index 1) que esta desabilitado
    if (opcaoSelecionada == 1) {
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
            opcaoSelecionada = 2;
        else
            opcaoSelecionada = 0;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        switch (opcaoSelecionada) {
            case 0: estadoAtual = ESTADO_JOGANDO;       break;
            case 1: /* Carregar — futuro */              break;
            case 2: estadoAtual = ESTADO_CONFIGURACOES; break;
            case 3: CloseWindow(); exit(0);             break;
        }
    }
}

static void updateConfiguracoes() {
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        opcaoConfig = (opcaoConfig + 1) % totalConfig;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        opcaoConfig = (opcaoConfig - 1 + totalConfig) % totalConfig;
    if (IsKeyPressed(KEY_ENTER) && opcaoConfig == totalConfig - 1)
        estadoAtual = ESTADO_MENU;
    if (IsKeyPressed(KEY_ESCAPE))
        estadoAtual = ESTADO_MENU;
}

void desenhaMenu() {
    // UPDATE
    if (estadoAtual == ESTADO_MENU)
        updateMenuPrincipal();
    else if (estadoAtual == ESTADO_JOGANDO) {
        updateJogo();
        if (IsKeyPressed(KEY_M)) estadoAtual = ESTADO_MENU;
    }
    else if (estadoAtual == ESTADO_CONFIGURACOES)
        updateConfiguracoes();

    // DRAW
    BeginDrawing();
    ClearBackground(BLACK);

    if (estadoAtual == ESTADO_MENU) {
        desenhaFundoMenu();

        for (int i = 0; i < totalOpcoes; i++)
            desenhaBotao(i, opcaoSelecionada);

        DrawText("W/S = Navegar | ENTER = Selecionar",
            tela.largura / 2 - MeasureText("W/S = Navegar | ENTER = Selecionar", 16) / 2,
            tela.altura - 30, 16, DARKGRAY);
    }
    else if (estadoAtual == ESTADO_JOGANDO) {
        drawJogo();
        DrawText("M = Menu", 10, 10, 18, DARKGRAY);
    }
    else if (estadoAtual == ESTADO_CONFIGURACOES) {
        desenhaFundoMenu();
        const char* titulo = "Configuracoes";
        DrawText(titulo, tela.largura / 2 - MeasureText(titulo, 40) / 2, 200, 40, WHITE);
        for (int i = 0; i < totalConfig; i++) {
            int fontSize = (i == opcaoConfig) ? 32 : 26;
            Color cor    = (i == opcaoConfig) ? YELLOW : WHITE;
            int x = tela.largura / 2 - MeasureText(opcoesConfig[i], fontSize) / 2;
            DrawText(opcoesConfig[i], x, botoesConfigY[i], fontSize, cor);
        }
        DrawText("ESC = Voltar",
            tela.largura / 2 - MeasureText("ESC = Voltar", 16) / 2,
            tela.altura - 30, 16, DARKGRAY);
    }

    EndDrawing();
}
