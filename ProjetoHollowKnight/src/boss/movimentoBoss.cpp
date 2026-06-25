#include "boss.h"
#include "mapa.h"
#include "personagem.h"
#include <raylib.h>

Vector2 movimentaBoss(Vector2 posicaoAtual) {
    float x = posicaoAtual.x;
    float y = posicaoAtual.y;
    float w = (float)bossState.entidade.largura;
    float h = (float)bossState.entidade.altura;

    float velocidadeBoss = constantesJogo.velocidade * 0.4f;
    float distanciaChase = 300.0f;
    float distanciaPulo = 200.0f;
    float distanciaAtaque = 120.0f;
    float diferencaX = personagem.posicao.x - x;
    float absDiferencaX = diferencaX < 0 ? -diferencaX : diferencaX;

    bool jogadorEstaLonge = absDiferencaX > distanciaPulo;
    bool jogadorEstaPerto = absDiferencaX <= distanciaAtaque;

    if (bossState.jumpCooldown > 0.0f) {
        bossState.jumpCooldown -= GetFrameTime();
        if (bossState.jumpCooldown < 0.0f) bossState.jumpCooldown = 0.0f;
    }

    float moveX = 0.0f;

    if (jogadorEstaLonge) {
        if (diferencaX > 0) bossState.entidade.olhandoDireita = true;
        else bossState.entidade.olhandoDireita = false;

        if (bossState.velY == 0.0f && bossState.jumpCooldown <= 0.0f) {
            bossState.velY = -11.0f;
            bossState.jumpCooldown = 1.2f;
        }

        moveX = (diferencaX > 0 ? velocidadeBoss : -velocidadeBoss);
    }
    else {
        float direcaoX = bossState.entidade.olhandoDireita ? 1.0f : -1.0f;
        moveX = direcaoX * velocidadeBoss;

        if (diferencaX > 0) bossState.entidade.olhandoDireita = true;
        else bossState.entidade.olhandoDireita = false;
    }

    // Colisao horizontal com blocos solidos para evitar atravessar paredes.
    if (moveX != 0.0f) {
        float proximoX = x + moveX;
        float checkX = (moveX > 0.0f) ? (proximoX + w - 2.0f) : (proximoX + 2.0f);
        bool colideX = blocoSolido(checkX, y + h * 0.35f)
                    || blocoSolido(checkX, y + h * 0.7f)
                    || blocoSolido(checkX, y + h - 2.0f);
        if (!colideX) {
            x = proximoX;
        } else {
            // Evita ficar preso em parede/quina apos o pre-tempo.
            bossState.entidade.olhandoDireita = !bossState.entidade.olhandoDireita;
            if (bossState.velY == 0.0f) {
                bossState.velY = -6.0f;
            }
        }
    }

    float velocidadeQueda = 4.0f;
    bool pisouNoChao = false;

    bossState.velY += constantesJogo.gravidade;
    y += bossState.velY;

    for (int i = 1; i <= (int)velocidadeQueda; i++) {
        float testeY = y + i;

        bool colideEsq = blocoSolido(x + 4, testeY + h);
        bool colideMid = blocoSolido(x + (w / 2), testeY + h);
        bool colideDir = blocoSolido(x + w - 4, testeY + h);

        if (colideEsq || colideMid || colideDir) {
            int lin = (int)((testeY + h) / bloco.altura);
            y = lin * bloco.altura - h - 0.1f;
            pisouNoChao = true;
            bossState.velY = 0.0f;
            break;
        }
    }

    float limiteInferiorMapa = (map.linhas - 2) * bloco.altura;
    if (y > limiteInferiorMapa) {
        x = bossState.entidade.posicaoInicial.x;
        y = bossState.entidade.posicaoInicial.y - 10.0f;
    }

    // Limites horizontais do mapa para o boss nao sair da area jogavel.
    if (x < 0.0f) x = 0.0f;
    float limiteDireito = map.colunas * bloco.largura - w;
    if (x > limiteDireito) x = limiteDireito;

    return (Vector2){x, y};
}
