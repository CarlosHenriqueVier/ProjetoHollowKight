#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <raylib.h>
#include "estruturas.h"

void loadPersonagem();
void unloadPersonagem();
void updatePersonagem();
void desenhaPersonagem();
Vector2 movimentaPersonagem(Vector2 posicaoAtual);

#endif
