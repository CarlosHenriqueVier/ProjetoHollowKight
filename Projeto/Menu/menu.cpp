#include "menu.h"
#include "../Game/game.h"
#include <raylib.h>
#include <cstdlib>

Estado estadoAtual = ESTADO_MENU;

void loadMenu() {
    // Comentado temporariamente para não depender dos arquivos de imagem no disco
    /*
    menuPrincipal.menuImagem[0] = LoadTexture("Texturas/Fundos/Menu/FundoMenu.png");
    menuPrincipal.menuBotoes[0] = LoadTexture("Texturas/Fundos/Menu/BotaoJogar.png");
    menuPrincipal.menuBotoes[1] = LoadTexture("Texturas/Fundos/Menu/BotaoCarregar.png");
    menuPrincipal.menuBotoes[2] = LoadTexture("Texturas/Fundos/Menu/BotaoOpcoes.png");
    menuPrincipal.menuBotoes[3] = LoadTexture("Texturas/Fundos/Menu/BotaoSair.png");
    menuPrincipal.menuBotoes[4] = LoadTexture("Texturas/Fundos/Menu/BotaoSalvar.png");
    
    menuPause.menuImagem[0] = LoadTexture("Texturas/Fundos/Menu/FundoMenu.png");
    menuPause.menuBotoes[0] = LoadTexture("Texturas/Fundos/Menu/BotaoJogar.png");
    menuPause.menuBotoes[1] = LoadTexture("Texturas/Fundos/Menu/BotaoCarregar.png");
    menuPause.menuBotoes[2] = LoadTexture("Texturas/Fundos/Menu/BotaoOpcoes.png");
    menuPause.menuBotoes[3] = LoadTexture("Texturas/Fundos/Menu/BotaoSair.png");
    menuPause.menuBotoes[4] = LoadTexture("Texturas/Fundos/Menu/BotaoSalvar.png");
    
    menuConfiguracoes.menuImagem[0] = LoadTexture("Texturas/Fundos/Menu/FundoMenu.png");
    menuConfiguracoes.menuBotoes[0] = LoadTexture("Texturas/Fundos/Menu/BotaoJogar.png");
    menuConfiguracoes.menuBotoes[1] = LoadTexture("Texturas/Fundos/Menu/BotaoCarregar.png");
    menuConfiguracoes.menuBotoes[2] = LoadTexture("Texturas/Fundos/Menu/BotaoOpcoes.png");
    menuConfiguracoes.menuBotoes[3] = LoadTexture("Texturas/Fundos/Menu/BotaoSair.png");
    menuConfiguracoes.menuBotoes[4] = LoadTexture("Texturas/Fundos/Menu/BotaoSalvar.png");
    */
}

void unloadMenu() {
    // Comentado temporariamente já que não há texturas na VRAM
    /*
    UnloadTexture(menuPrincipal.menuImagem[0]);
    for (int i = 0; i < 5; i++)
        UnloadTexture(menuPrincipal.menuBotoes[i]);
    */
}

void desenhaFundoMenu() {
    // Substitui a imagem de fundo por um preenchimento cinza escuro sólido
    ClearBackground(DARKGRAY);
    
    // Adiciona um título de placeholder elegante para identificar o jogo
    const char* tituloJogo = "HOLLOW KNIGHT (PROTO)";
    int tamTitulo = MeasureText(tituloJogo, 40);
    DrawText(tituloJogo, tela.largura / 2 - tamTitulo / 2, 100, 40, LIGHTGRAY);
}

void desenhaBotao(int texIndex, int posIndex, int selecionado, bool desabilitado) {
    float x = tela.largura / 2.0f - menuPrincipal.botaoW / 2.0f;
    float y = menuPrincipal.botoesY[posIndex] - menuPrincipal.botaoH / 2.0f;
    
    // Determina a cor do bloco do botão baseado no seu estado
    Color corBotao = desabilitado ? GRAY : LIGHTGRAY;
    if (posIndex == selecionado && !desabilitado) corBotao = RAYWHITE;

    // Desenha o corpo do retângulo do botão
    DrawRectangle((int)x, (int)y, menuPrincipal.botaoW, menuPrincipal.botaoH, corBotao);

    // Converte o índice de textura antigo em um texto legível
    const char* textoBotao = "BOTAO";
    switch (texIndex) {
        case 0: textoBotao = "JOGAR"; break;
        case 1: textoBotao = "CARREGAR"; break;
        case 2: textoBotao = "OPCOES"; break;
        case 3: textoBotao = "SAIR"; break;
        case 4: textoBotao = "SALVAR"; break;
        case 5: textoBotao = "AJUDA"; break; // <-- Novo índice associado ao texto AJUDA
    }

    // Centraliza o texto perfeitamente dentro do retângulo alocado
    int tamTexto = MeasureText(textoBotao, 20);
    int textX = (int)(x + (menuPrincipal.botaoW / 2.0f) - (tamTexto / 2.0f));
    int textY = (int)(y + (menuPrincipal.botaoH / 2.0f) - 10);
    DrawText(textoBotao, textX, textY, 20, desabilitado ? DARKGRAY : BLACK);

    // Desenha a borda amarela de seleção (substituindo a antiga borda branca)
    if (posIndex == selecionado && !desabilitado)
        DrawRectangleLinesEx({ x - 2, y - 2, (float)menuPrincipal.botaoW + 4, (float)menuPrincipal.botaoH + 4 }, 2, YELLOW);
}

void desenhaBotaoPause(int texIndex, int posIndex, int selecionado, bool desabilitado) {
    float x = tela.largura / 2.0f - menuPause.botaoW / 2.0f;
    float y = menuPause.botoesY[posIndex] - menuPause.botaoH / 2.0f;
    
    Color corBotao = desabilitado ? GRAY : LIGHTGRAY;
    if (posIndex == selecionado && !desabilitado) corBotao = RAYWHITE;

    DrawRectangle((int)x, (int)y, menuPause.botaoW, menuPause.botaoH, corBotao);

    const char* textoBotao = "BOTAO";
    switch (texIndex) {
        case 0: textoBotao = "CONTINUAR"; break;
        case 1: textoBotao = "INVENTARIO"; break;
        case 2: textoBotao = "MENU PRINCIPAL"; break;
        case 3: textoBotao = "SAIR"; break;
        case 4: textoBotao = "SALVAR"; break;
    }

    int tamTexto = MeasureText(textoBotao, 18);
    int textX = (int)(x + (menuPause.botaoW / 2.0f) - (tamTexto / 2.0f));
    int textY = (int)(y + (menuPause.botaoH / 2.0f) - 9);
    DrawText(textoBotao, textX, textY, 18, desabilitado ? DARKGRAY : BLACK);

    if (posIndex == selecionado && !desabilitado)
        DrawRectangleLinesEx({ x - 2, y - 2, (float)menuPause.botaoW + 4, (float)menuPause.botaoH + 4 }, 2, YELLOW);
}

void updateMenuPrincipal() {
    // Navegação por setas (S / DOWN e W / UP) mapeando o total de opções atualizado
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        menuPrincipal.opcaoSelecionada = (menuPrincipal.opcaoSelecionada + 1) % menuPrincipal.totalOpcoes;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        menuPrincipal.opcaoSelecionada = (menuPrincipal.opcaoSelecionada - 1 + menuPrincipal.totalOpcoes) % menuPrincipal.totalOpcoes;

    // Atalho direto: Pressionar a tecla A seleciona a opção AJUDA (índice 4 no array de posições)
    if (IsKeyPressed(KEY_A)) {
        menuPrincipal.opcaoSelecionada = 4; // Foca no botão de Ajuda
    }

    // Mantém o pulo do botão "CARREGAR" (índice 1) que está desabilitado temporariamente
    if (menuPrincipal.opcaoSelecionada == 1) {
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) menuPrincipal.opcaoSelecionada = 2;
        else menuPrincipal.opcaoSelecionada = 0;
    }
    
    if (IsKeyPressed(KEY_ENTER)) {
        switch (menuPrincipal.opcaoSelecionada) {
            case 0: estadoAtual = ESTADO_JOGANDO;       break;
            case 1: /* Carregar — futuro */              break;
            case 2: estadoAtual = ESTADO_CONFIGURACOES; break;
            case 3: CloseWindow(); exit(0);             break;
            case 4: /* Futuro: estadoAtual = ESTADO_AJUDA; ou lógica de ajuda */ break;
        }
    }
    
    if (IsKeyPressed(KEY_N)) {
        estadoAtual = ESTADO_JOGANDO;
    }
    if (IsKeyPressed(KEY_C)) {
        // Carregar — futuro
    }
    if (IsKeyPressed(KEY_O)) {
        estadoAtual = ESTADO_CONFIGURACOES;
    }
    if (IsKeyPressed(KEY_S)) {
        CloseWindow(); 
        exit(0);
    }
}

void updatePause() {
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        menuPause.opcaoSelecionada = (menuPause.opcaoSelecionada + 1) % menuPause.totalOpcoes;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        menuPause.opcaoSelecionada = (menuPause.opcaoSelecionada - 1 + menuPause.totalOpcoes) % menuPause.totalOpcoes;

    if (IsKeyPressed(KEY_ESCAPE))
        estadoAtual = ESTADO_JOGANDO;

    if (IsKeyPressed(KEY_ENTER)) {
        switch (menuPause.opcaoSelecionada) {
            case 0: estadoAtual = ESTADO_JOGANDO; break;
            case 1: estadoAtual = ESTADO_INVENTARIO; break; 
            case 2: estadoAtual = ESTADO_MENU;    break;
            case 3: CloseWindow(); exit(0);        break;
        }
    }
}

void updateConfiguracoes() {
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        menuConfiguracoes.opcaoSelecionada = (menuConfiguracoes.opcaoSelecionada + 1) % menuConfiguracoes.totalOpcoes;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        menuConfiguracoes.opcaoSelecionada = (menuConfiguracoes.opcaoSelecionada - 1 + menuConfiguracoes.totalOpcoes) % menuConfiguracoes.totalOpcoes;
    if (IsKeyPressed(KEY_ENTER) && menuConfiguracoes.opcaoSelecionada == menuConfiguracoes.totalOpcoes - 1)
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
        if (IsKeyPressed(KEY_ESCAPE)) {
            estadoAtual = ESTADO_PAUSADO;
            menuPause.opcaoSelecionada = 0;
        }
    }
    else if (estadoAtual == ESTADO_PAUSADO)
        updatePause();
    else if (estadoAtual == ESTADO_CONFIGURACOES)
        updateConfiguracoes();

    // DRAW
    BeginDrawing();
    ClearBackground(BLACK);

    if (estadoAtual == ESTADO_MENU) {
        desenhaFundoMenu();
        
        // Renderiza os botões originais
        desenhaBotao(0, 0, menuPrincipal.opcaoSelecionada, false); // JOGAR
        desenhaBotao(1, 1, menuPrincipal.opcaoSelecionada, true);  // CARREGAR (Desabilitado)
        desenhaBotao(2, 2, menuPrincipal.opcaoSelecionada, false); // OPCOES
        desenhaBotao(3, 3, menuPrincipal.opcaoSelecionada, false); // SAIR
        
        // Novo botão seguindo estritamente o molde: passa texIndex=5 (AJUDA) e posIndex=4 (posição abaixo do Sair)
        desenhaBotao(5, 4, menuPrincipal.opcaoSelecionada, false); 
            
        DrawText("W/S = Navegar | A = Ajuda | ENTER = Selecionar",
            tela.largura / 2 - MeasureText("W/S = Navegar | A = Ajuda | ENTER = Selecionar", 16) / 2,
            tela.altura - 30, 16, DARKGRAY);
    }
    else if (estadoAtual == ESTADO_JOGANDO) {
        drawJogo();
        const char* hint = "ESC = Pause";
        DrawText(hint, tela.largura - MeasureText(hint, 18) - 10, 10, 18, DARKGRAY);
    }
    else if (estadoAtual == ESTADO_PAUSADO) {
        drawJogo();
        DrawRectangle(0, 0, tela.largura, tela.altura, { 0, 0, 0, 120 });

        const char* titulo = "Pausado";
        DrawText(titulo, tela.largura / 2 - MeasureText(titulo, 32) / 2, 160, 32, WHITE);

        desenhaBotaoPause(0, 0, menuPause.opcaoSelecionada, false); // Continuar
        desenhaBotaoPause(1, 1, menuPause.opcaoSelecionada, false); // Inventário
        desenhaBotaoPause(2, 2, menuPause.opcaoSelecionada, false); // Menu Principal
        desenhaBotaoPause(3, 3, menuPause.opcaoSelecionada, false); // Sair

        const char* hint = "W/S = Navegar | ENTER = Selecionar | ESC = Continuar";
        DrawText(hint, tela.largura / 2 - MeasureText(hint, 14) / 2, tela.altura - 30, 14, DARKGRAY);
    }
    else if (estadoAtual == ESTADO_CONFIGURACOES) {
        desenhaFundoMenu();
        const char* titulo = "Configuracoes";
        const char* opcoes[3] = { "VOLUME", "AJUSTES", "VOLTAR" };
        DrawText(titulo, tela.largura / 2 - MeasureText(titulo, 40) / 2, 200, 40, WHITE);
        
        for (int i = 0; i < menuConfiguracoes.totalOpcoes; i++) {
            int fontSize = (i == menuConfiguracoes.opcaoSelecionada) ? 32 : 26;
            Color cor    = (i == menuConfiguracoes.opcaoSelecionada) ? YELLOW : WHITE;
            int x = tela.largura / 2 - MeasureText(opcoes[i], fontSize) / 2;
            DrawText(opcoes[i], x, menuConfiguracoes.botoesY[i], fontSize, cor);
        }
        
        DrawText("ESC = Voltar",
            tela.largura / 2 - MeasureText("ESC = Voltar", 16) / 2,
            tela.altura - 30, 16, DARKGRAY);
    }

    EndDrawing();
}