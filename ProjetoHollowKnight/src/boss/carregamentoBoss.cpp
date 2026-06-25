#include "boss.h"
#include <raylib.h>

void loadBoss() {
    bossState.velY = 0.0f;
    bossState.countdown = 3.0f;
    bossState.movendo = false;
    bossState.preparando = false;
    bossState.podeReceberDano = false;
    bossState.jumpCooldown = 0.0f;
    bossState.damageCooldown = 0.0f;
}

void unloadBoss() {
    // Caso use texturas no futuro, descarregue aqui
}
