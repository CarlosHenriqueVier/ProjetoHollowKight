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
    updateInimigo();

    // Cria o retângulo do corpo do personagem
    Rectangle rectPlayer = { personagem.posicao.x, personagem.posicao.y, (float)personagem.largura, (float)personagem.altura };

    // --- LÓGICA DE ATAQUE DO PERSONAGEM (CAUSAR DANO) ---
    Rectangle rectAtaque = { 0 };
    if (personagem.dados.ataque) {
        float alcanceAtaque = 40.0f; // Distância do golpe em pixels
        
        // Se olhar para a direita, a área de ataque fica à frente. Se olhar para a esquerda, fica atrás.
        if (personagem.olhandoDireita) {
            rectAtaque = { personagem.posicao.x + personagem.largura, personagem.posicao.y, alcanceAtaque, (float)personagem.altura };
        } else {
            rectAtaque = { personagem.posicao.x - alcanceAtaque, personagem.posicao.y, alcanceAtaque, (float)personagem.altura };
        }
        
        // Opcional: Se quiser ver a área do golpe na tela para testar, descomente a linha abaixo (dentro do drawJogo)
        // DrawRectangleRec(rectAtaque, FADE(PURPLE, 0.5f));
    }

    // --- LOOP DE INTERAÇÃO COM TODOS OS INIMIGOS ---
    for (int i = 0; i < quantidadeInimigos; i++) {
        if (listaInimigos[i].dados.vivo) {
            Rectangle rectInimigo = { listaInimigos[i].posicao.x, listaInimigos[i].posicao.y, (float)listaInimigos[i].largura, (float)listaInimigos[i].altura };

            // 1. CHECA SE O PERSONAGEM BATEU NO INIMIGO
            if (personagem.dados.ataque && CheckCollisionRecs(rectAtaque, rectInimigo)) {
                // Inimigo perde 50% de vida (Dano = 50)
                listaInimigos[i].dados.hp -= 50;
                
                // Força o fim do ataque do jogador para não dar dano contínuo no mesmo golpe
                personagem.dados.ataque = false; 

                // Se o HP do inimigo chegar a 0%, ele morre
                if (listaInimigos[i].dados.hp <= 0) {
                    listaInimigos[i].dados.hp = 0;
                    listaInimigos[i].dados.vivo = false; // Inimigo some e desativa
                }
                
                // Faz o inimigo dar um mini "coice" para trás ao ser golpeado
                float direcaoInimigoEmpurrado = (personagem.posicao.x < listaInimigos[i].posicao.x) ? 1.0f : -1.0f;
                listaInimigos[i].posicao.x += direcaoInimigoEmpurrado * 15.0f;
                
                break; // Sai do loop para processar uma colisão por frame
            }

            // 2. CHECA SE O INIMIGO BATEU NO PERSONAGEM (DANO NO JOGADOR)
            // Só toma dano se o jogador NÃO estiver atacando naquele frame
            if (!personagem.dados.ataque && CheckCollisionRecs(rectPlayer, rectInimigo)) {
                personagem.dados.hp -= 10; // 10% de dano
                if (personagem.dados.hp <= 0) {
                    personagem.dados.hp = 0;
                    personagem.dados.vivo = false; 
                }

                // Knockback no jogador
                float direcaoKnockback = (personagem.posicao.x < listaInimigos[i].posicao.x) ? -1.0f : 1.0f;
                personagem.posicao.x += direcaoKnockback * 20.0f; 
                constantesJogo.velocidadeY = -6.0f; 

                break; 
            }
        }
    }

    // --- ATUALIZAÇÃO DA CÂMERA (Mantém igual) ---
    tela.camera.target = {
        personagem.posicao.x + personagem.largura / 2.0f,
        personagem.posicao.y + personagem.altura / 2.0f
    };
    tela.camera.offset = { tela.largura / 2.0f, tela.altura / 2.0f };

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