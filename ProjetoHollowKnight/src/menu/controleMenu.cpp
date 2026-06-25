#include "menu.h"
#include "game.h"
#include "mapa.h"
#include "save.h"
#include "personagem.h"
#include <raylib.h>
#include <cstdlib>

void updateMenuPrincipal() {
    Vector2 mouse = GetMousePosition();
    bool cliqueMouse = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    float x = tela.largura / 2.0f - menuPrincipal.botaoW / 2.0f;
    for (int i = 0; i < menuPrincipal.totalOpcoes; i++) {
        float y = menuPrincipal.botoesY[i] - menuPrincipal.botaoH / 2.0f;
        Rectangle botao = { x, y, (float)menuPrincipal.botaoW, (float)menuPrincipal.botaoH };
        if (CheckCollisionPointRec(mouse, botao)) {
            menuPrincipal.opcaoSelecionada = i;
        }
    }

    if (IsKeyPressed(KEY_DOWN))
        menuPrincipal.opcaoSelecionada = (menuPrincipal.opcaoSelecionada + 1) % menuPrincipal.totalOpcoes;
    if (IsKeyPressed(KEY_UP))
        menuPrincipal.opcaoSelecionada = (menuPrincipal.opcaoSelecionada - 1 + menuPrincipal.totalOpcoes) % menuPrincipal.totalOpcoes;

    if (IsKeyPressed(KEY_ENTER) || cliqueMouse) {
        switch (menuPrincipal.opcaoSelecionada) {
            case 0:
                resetarEstadoNovoJogo();
                unloadMapa();
                map.localMapa = caminhoMapaPorFase(faseDoJogo);
                carregarMapaAtualComEntidades();
                estadoAtual = ESTADO_JOGANDO;
                break;
            case 1:
                carregaJogo();
                unloadMapa();
                map.localMapa = caminhoMapaPorFase(faseDoJogo);
                carregarMapaAtualComEntidades();
                estadoAtual = ESTADO_JOGANDO;
                break;
            case 2:
                estadoAtual = ESTADO_AJUDA;
                break;
            case 3:
                CloseWindow();
                exit(0);
                break;
        }
    }
}

void updatePause() {
    Vector2 mouse = GetMousePosition();
    bool cliqueMouse = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    float x = tela.largura / 2.0f - menuPause.botaoW / 2.0f;
    for (int i = 0; i < menuPause.totalOpcoes; i++) {
        float y = menuPause.botoesY[i] - menuPause.botaoH / 2.0f;
        Rectangle botao = { x, y, (float)menuPause.botaoW, (float)menuPause.botaoH };
        if (CheckCollisionPointRec(mouse, botao)) {
            menuPause.opcaoSelecionada = i;
        }
    }

    if (IsKeyPressed(KEY_DOWN))
        menuPause.opcaoSelecionada = (menuPause.opcaoSelecionada + 1) % menuPause.totalOpcoes;
    if (IsKeyPressed(KEY_UP))
        menuPause.opcaoSelecionada = (menuPause.opcaoSelecionada - 1 + menuPause.totalOpcoes) % menuPause.totalOpcoes;

    if (IsKeyPressed(KEY_ESCAPE))
        estadoAtual = ESTADO_JOGANDO;

    if (IsKeyPressed(KEY_TAB)) {
        estadoAtual = ESTADO_INVENTARIO;
        return;
    }

    if (IsKeyPressed(KEY_ENTER) || cliqueMouse) {
        switch (menuPause.opcaoSelecionada) {
            case 0: estadoAtual = ESTADO_JOGANDO; break;
            case 1: estadoAtual = ESTADO_INVENTARIO; break;
            case 2: estadoAtual = ESTADO_MENU; break;
            case 3: salvaJogo(); break;
            case 4: CloseWindow(); exit(0); break;
        }
    }
}

