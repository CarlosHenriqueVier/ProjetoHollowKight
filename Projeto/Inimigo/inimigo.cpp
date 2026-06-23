#include "inimigo.h"
#include "../Mapa/mapa.h"
#include <raylib.h>

void loadInimigo() {
    // Carrega as texturas normalmente
    listaInimigos[0].imagem[0] = LoadTexture("Texturas/Inimigo/Inimigo.png");
    listaInimigos[0].imagem[1] = LoadTexture("Texturas/Inimigo/InverteInimigo.png");
}

void unloadInimigo() {
    UnloadTexture(listaInimigos[0].imagem[0]);
    UnloadTexture(listaInimigos[0].imagem[1]);
}

Vector2 movimentaInimigoEspecifico(int indice, Vector2 posicaoAtual) {
    float x = posicaoAtual.x;
    float y = posicaoAtual.y;
    float w = (float)listaInimigos[indice].largura;
    float h = (float)listaInimigos[indice].altura;

    // Determina a direção baseada no booleano individual de cada inimigo
    float direcaoX = listaInimigos[indice].olhandoDireita ? 1.0f : -1.0f;

    // --- 1. PATRULHA HORIZONAL POR RAIO DE DISTÂNCIA ---
    // Faz o inimigo andar usando a velocidade do jogo (ex: 3.0f)
    x += direcaoX * constantesJogo.velocidade;

    // Se ele se afastar mais de 90 pixels para a direita da sua posição original, vira para a esquerda
    if (x > listaInimigos[indice].posicaoInicial.x + 90.0f) {
        listaInimigos[indice].olhandoDireita = false;
    }
    // Se ele se afastar mais de 90 pixels para a esquerda da sua posição original, vira para a direita
    if (x < listaInimigos[indice].posicaoInicial.x - 90.0f) {
        listaInimigos[indice].olhandoDireita = true;
    }

    // --- 2. GRAVIDADE SIMPLIFICADA E SEGURA ---
    // Aplica uma força constante de queda (simulando a gravidade de forma direta)
    y += 4.0f;

    // Colisão vertical com o chão do teu mapa
    bool colideChaoEsq = blocoSolido(x + 2,     y + h);
    bool colideChaoDir = blocoSolido(x + w - 2, y + h);

    if (colideChaoEsq || colideChaoDir) {
        int lin = (int)((y + h) / bloco.altura);
        y = lin * bloco.altura - h - 0.1f; // Ajusta perfeitamente no topo do bloco
    }

    // Retorna a nova posição corrigida para o elemento do array
    return {x, y};
}

void updateInimigo() {
    // Atualiza todos os inimigos vivos do array
    for (int i = 0; i < quantidadeInimigos; i++) {
        if (listaInimigos[i].dados.vivo) {
            listaInimigos[i].posicao = movimentaInimigoEspecifico(i, listaInimigos[i].posicao);
        }
    }
}

void desenhaInimigo() {
    // Desenha todos os inimigos na tela com o tamanho correto (30x30)
    for (int i = 0; i < quantidadeInimigos; i++) {
        if (listaInimigos[i].dados.vivo) {
            DrawRectangle((int)listaInimigos[i].posicao.x, (int)listaInimigos[i].posicao.y, 
                          listaInimigos[i].largura, listaInimigos[i].altura, RED);
        }
    }
}