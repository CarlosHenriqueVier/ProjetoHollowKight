#include "boss.h"
#include "personagem.h"
#include "mapa.h"
#include <raylib.h>

extern float bossVelY;
extern float bossCountdown;
extern bool bossMovendo;
extern bool bossPreparando;
extern float bossDamageCooldown;
extern float bossDamageInterval;
extern int bossDamageValor;

static void aplicaKnockbackJogador(float forcaX, float forcaY) {
    float centroPlayer = personagem.posicao.x + personagem.largura * 0.5f;
    float centroBoss = chefao.posicao.x + chefao.largura * 0.5f;
    float direcao = (centroPlayer < centroBoss) ? -1.0f : 1.0f;
    float novoX = personagem.posicao.x + direcao * forcaX;

    float checkX = (direcao > 0.0f) ? (novoX + personagem.largura) : novoX;
    bool colideParede = blocoSolido(checkX, personagem.posicao.y + 2.0f)
                    || blocoSolido(checkX, personagem.posicao.y + personagem.altura - 2.0f);
    if (!colideParede) {
        personagem.posicao.x = novoX;
    }

    constantesJogo.velocidadeY = -forcaY;
}

static void resolveColisaoCorpoBossJogador() {
    Rectangle playerRect = { personagem.posicao.x, personagem.posicao.y, (float)personagem.largura, (float)personagem.altura };
    Rectangle bossRect = { chefao.posicao.x, chefao.posicao.y, (float)chefao.largura, (float)chefao.altura };

    if (!CheckCollisionRecs(bossRect, playerRect)) return;

    Rectangle inter = GetCollisionRec(bossRect, playerRect);
    if (inter.width <= 0.0f || inter.height <= 0.0f) return;

    float centroPlayerX = personagem.posicao.x + personagem.largura * 0.5f;
    float centroBossX = chefao.posicao.x + chefao.largura * 0.5f;

    // Separa pelo menor eixo de intersecao para evitar "grudar" no boss.
    if (inter.width < inter.height) {
        float direcao = (centroPlayerX < centroBossX) ? -1.0f : 1.0f;
        float novoX = personagem.posicao.x + direcao * (inter.width + 2.0f);
        float checkX = (direcao > 0.0f) ? (novoX + personagem.largura) : novoX;

        bool colideParede = blocoSolido(checkX, personagem.posicao.y + 2.0f)
                        || blocoSolido(checkX, personagem.posicao.y + personagem.altura - 2.0f);
        if (!colideParede) {
            personagem.posicao.x = novoX;
        }
    } else {
        // Fallback vertical: coloca o jogador acima do boss quando sobreposicao vertical predomina.
        personagem.posicao.y = chefao.posicao.y - personagem.altura - 0.1f;
        if (constantesJogo.velocidadeY > 0.0f) {
            constantesJogo.velocidadeY = 0.0f;
        }
    }
}

static void atualizaAtivacaoBoss() {
    if (bossMovendo || bossPreparando) return;

    float distanciaInicio = 260.0f;
    float diferencaX = personagem.posicao.x - chefao.posicaoInicial.x;
    float absDiferencaX = diferencaX < 0 ? -diferencaX : diferencaX;
    float diferencaY = personagem.posicao.y - chefao.posicaoInicial.y;
    float absDiferencaY = diferencaY < 0 ? -diferencaY : diferencaY;

    if (absDiferencaX <= distanciaInicio && absDiferencaY <= 200.0f) {
        bossPreparando = true;
        bossCountdown = 3.0f;
    }
}

static void atualizarCooldownDanoBoss() {
    if (bossDamageCooldown > 0.0f) {
        bossDamageCooldown -= GetFrameTime();
        if (bossDamageCooldown < 0.0f) bossDamageCooldown = 0.0f;
    }
}

static void tentarAplicarDanoBossNoJogador() {
    if (bossDamageCooldown > 0.0f) return;

    Rectangle areaAtaque = {
        chefao.posicao.x - 40.0f,
        chefao.posicao.y - 40.0f,
        chefao.largura + 80.0f,
        chefao.altura + 80.0f
    };
    Rectangle playerRect = { personagem.posicao.x, personagem.posicao.y, (float)personagem.largura, (float)personagem.altura };

    if (!CheckCollisionRecs(areaAtaque, playerRect)) return;

    personagem.dados.hp -= 1;
    if (personagem.dados.hp < 0) personagem.dados.hp = 0;
    if (personagem.dados.hp == 0) {
        personagem.dados.vivo = false;
    }

    aplicaKnockbackJogador(28.0f, 6.0f);
    bossDamageCooldown = bossDamageInterval;
}

void updateBoss() {
    if (!bossAtivo || !chefao.dados.vivo) return;

    if (!bossMovendo) {
        if (!bossPreparando) {
            atualizaAtivacaoBoss();
        }
        else {
            bossCountdown -= GetFrameTime();
            if (bossCountdown <= 0.0f) {
                bossPreparando = false;
                bossMovendo = true;
                bossPodeReceberDano = true;
            }
        }
    }

    if (bossMovendo) {
        chefao.posicao = movimentaBoss(chefao.posicao);
        resolveColisaoCorpoBossJogador();
        atualizarCooldownDanoBoss();
        tentarAplicarDanoBossNoJogador();
    }
}

void desenhaBoss() {
    if (bossAtivo && chefao.dados.vivo) {
        DrawRectangle((int)chefao.posicao.x, (int)chefao.posicao.y, chefao.largura, chefao.altura, ORANGE);
        DrawRectangle((int)chefao.posicao.x, (int)chefao.posicao.y - 15, chefao.largura, 6, RED);
        float vidaPercent = (float)chefao.dados.hp / 500.0f;
        DrawRectangle((int)chefao.posicao.x, (int)chefao.posicao.y - 15, (int)(chefao.largura * vidaPercent), 6, GREEN);
    }
}
