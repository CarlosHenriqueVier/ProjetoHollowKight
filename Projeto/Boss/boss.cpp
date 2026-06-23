#include "boss.h"
#include "../Mapa/mapa.h"
#include <raylib.h>

// Definição das variáveis globais do Boss
infoEntidade chefao = { 0 };
bool bossAtivo = false;

void loadBoss() {
}

void unloadBoss() {
    // Caso use texturas no futuro, descarregue aqui
}

Vector2 movimentaBoss(Vector2 posicaoAtual) {
    float x = posicaoAtual.x;
    float y = posicaoAtual.y;
    float w = (float)chefao.largura;  // 60
    float h = (float)chefao.altura;   // 60

    float direcaoX = chefao.olhandoDireita ? 1.0f : -1.0f;

    // --- 1. PATRULHA HORIZONTAL ---
    x += direcaoX * (constantesJogo.velocidade + 0.5f);

    if (x > chefao.posicaoInicial.x + 150.0f) {
        chefao.olhandoDireita = false;
    }
    if (x < chefao.posicaoInicial.x - 150.0f) {
        chefao.olhandoDireita = true;
    }

    // --- 2. GRAVIDADE E DETECÇÃO DE CHÃO BLINDADA ---
    float velocidadeQueda = 4.0f;
    bool pisouNoChao = false;

    // Testamos pixel por pixel da queda para o Boss de 60px nunca "burlar" o chão
    for (int i = 1; i <= (int)velocidadeQueda; i++) {
        float testeY = y + i;

        bool colideEsq = blocoSolido(x + 4,       testeY + h);
        bool colideMid = blocoSolido(x + (w / 2), testeY + h); 
        bool colideDir = blocoSolido(x + w - 4,   testeY + h);

        if (colideEsq || colideMid || colideDir) {
            int lin = (int)((testeY + h) / bloco.altura);
            y = lin * bloco.altura - h - 0.1f;
            pisouNoChao = true;
            break; // Para de cair imediatamente
        }
    }

    // Se não encontrou chão nenhum no caminho, aplica a queda normal
    if (!pisouNoChao) {
        y += velocidadeQueda;
    }

    // --- 3. TRAVA ANTILIMBO (SEGURANÇA MÁXIMA) ---
    // Se por acaso ele passar da penúltima linha do mapa, força ele a voltar para a posição inicial
    float limiteInferiorMapa = (map.linhas - 2) * bloco.altura; 
    if (y > limiteInferiorMapa) {
        x = chefao.posicaoInicial.x;
        y = chefao.posicaoInicial.y - 10.0f; // Nasce um pouco acima para cair direito
    }

    // Retorna a posição corrigida
    Vector2 novaPosicao;
    novaPosicao.x = x;
    novaPosicao.y = y;
    return novaPosicao;
}

void updateBoss() {
    if (bossAtivo && chefao.dados.vivo) {
        chefao.posicao = movimentaBoss(chefao.posicao);
    }
}

void desenhaBoss() {
    if (bossAtivo && chefao.dados.vivo) {
        // Desenha o Boss como um quadrado ROXO ESCURO ou outra cor de destaque de 60x60
        DrawRectangle((int)chefao.posicao.x, (int)chefao.posicao.y, chefao.largura, chefao.altura, ORANGE);
        
        // Desenha uma barra de vida pequena acima da cabeça dele para dar o clima de Boss
        DrawRectangle((int)chefao.posicao.x, (int)chefao.posicao.y - 15, chefao.largura, 6, RED);
        float vidaPercent = (float)chefao.dados.hp / 500.0f;
        DrawRectangle((int)chefao.posicao.x, (int)chefao.posicao.y - 15, (int)(chefao.largura * vidaPercent), 6, GREEN);
    }
}