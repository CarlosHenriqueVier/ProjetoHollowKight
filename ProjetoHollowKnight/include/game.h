#ifndef GAME_H
#define GAME_H

#include "estruturas.h"

void loadJogo();
void unloadJogo();
void updateJogo(); 
void drawJogo();
void drawFundo();
void inicializaPosicoesEntidades();

extern FaseAtual faseDoJogo;

#endif  