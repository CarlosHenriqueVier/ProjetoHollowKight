#include "hud.h"
#include "personagem.h" // Importante para ler os dados do personagem
#include <raylib.h>
#include <stdio.h>

void initHud() {
    // Como a vida agora é controlada na inicialização do personagem,
    // não precisamos setar variáveis locais aqui.
}

void desenhaHud(int hp, int mp, int ataque, int defesa) {
    int barLargura = 200;
    int barAltura  = 18;
    int x          = 20;
    int yVida      = 20;
    int yEnergia   = 50;

    // --- VIDA ---
    DrawRectangle(x, yVida, barLargura, barAltura, { 40, 0, 0, 200 });
    DrawRectangle(x, yVida, (int)(barLargura * (hp / 100.0f)), barAltura, RED);
    DrawRectangleLines(x, yVida, barLargura, barAltura, WHITE);
    DrawText("HP", x + barLargura + 8, yVida + 2, 14, WHITE);

    // --- ENERGIA ---
    DrawRectangle(x, yEnergia, barLargura, barAltura, { 0, 0, 40, 200 });
    DrawRectangle(x, yEnergia, (int)(barLargura * (mp / 100.0f)), barAltura, BLUE);
    DrawRectangleLines(x, yEnergia, barLargura, barAltura, WHITE);
    DrawText("MP", x + barLargura + 8, yEnergia + 2, 14, WHITE);

    // --- ATAQUE E DEFESA ---
    int yInferior = tela.altura - 60;
    
    char atkText[20], defText[20];
    sprintf(atkText, "ATK: %d", ataque);
    sprintf(defText, "DEF: %d", defesa);
    
    DrawText(atkText, x, yInferior, 18, WHITE);
    DrawText(defText, x, yInferior + 25, 18, WHITE);
}