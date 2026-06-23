#include "hud.h"
#include "../Personagem/personagem.h" // Importante para ler os dados do personagem
#include <raylib.h>

void initHud() {
    // Como a vida agora é controlada na inicialização do personagem,
    // não precisamos setar variáveis locais aqui.
}

void desenhaHud() {
    int barLargura = 200;
    int barAltura  = 18;
    int x          = 20;
    int yVida      = 20;
    int yEnergia   = 50;

    // --- VIDA (HP) ---
    // Garante que o cálculo não quebre se o HP for menor que 0
    float hpAtual = (float)personagem.dados.hp;
    if (hpAtual < 0) hpAtual = 0;

    // Fundo escuro
    DrawRectangle(x, yVida, barLargura, barAltura, { 40, 0, 0, 200 });
    
    // Preenchimento dinâmico baseado no HP real do personagem (100 é a vida máxima)
    DrawRectangle(x, yVida, (int)(barLargura * (hpAtual / 100.0f)), barAltura, RED);
    
    // Contorno branco
    DrawRectangleLines(x, yVida, barLargura, barAltura, WHITE);
    // Label
    DrawText("HP", x + barLargura + 8, yVida + 2, 14, WHITE);


    // --- ENERGIA (MP) ---
    float mpAtual = (float)personagem.dados.mp;
    if (mpAtual < 0) mpAtual = 0;

    // Fundo escuro
    DrawRectangle(x, yEnergia, barLargura, barAltura, { 0, 0, 40, 200 });
    
    // Preenchimento dinâmico baseado no MP real (50 é a mana máxima definida na sua struct)
    DrawRectangle(x, yEnergia, (int)(barLargura * (mpAtual / 50.0f)), barAltura, BLUE);
    
    // Contorno branco
    DrawRectangleLines(x, yEnergia, barLargura, barAltura, WHITE);
    // Label
    DrawText("MP", x + barLargura + 8, yEnergia + 2, 14, WHITE);
}