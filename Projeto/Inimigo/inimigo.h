#ifndef INIMIGO_H
#define INIMIGO_H

#include <raylib.h>
#include "../Estruturas/estruturas.h"

void loadInimigo();
void unloadInimigo();
void updateInimigo();
void desenhaInimigo();
Vector2 movimentaInimigo(Vector2 posicaoAtual);

#endif