#define _CRT_SECURE_NO_WARNINGS
#include "save.h"
#include "estruturas.h"
#include <stdio.h>

void salvaJogo() {
    FILE* arquivo = fopen("data/savegame.txt", "w");
    if (arquivo == NULL) {
        TraceLog(LOG_ERROR, "Erro ao salvar");
        return;
    }

    fprintf(arquivo, "%d\n", personagem.dados.hp);
    fprintf(arquivo, "%d\n", personagem.dados.mp);
    fprintf(arquivo, "%d\n", faseDoJogo);
    fprintf(arquivo, "%d\n", personagem.dados.habilidadesColetadas);
    
    for (int i = 0; i < TOTAL_AMULETOS; i++) {
        fprintf(arquivo, "%d\n", personagem.dados.amuletos[i].coletado ? 1 : 0);
    }

    fclose(arquivo);
}

void carregaJogo() {
    FILE* arquivo = fopen("data/savegame.txt", "r");
    if (arquivo == NULL) {
        return;
    }

    fscanf(arquivo, "%d", &personagem.dados.hp);
    fscanf(arquivo, "%d", &personagem.dados.mp);
    
    int faseCarregada;
    fscanf(arquivo, "%d", &faseCarregada);
    faseDoJogo = (FaseAtual)faseCarregada;
    
    fscanf(arquivo, "%d", &personagem.dados.habilidadesColetadas);
    
    for (int i = 0; i < TOTAL_AMULETOS; i++) {
        int coletado;
        fscanf(arquivo, "%d", &coletado);
        personagem.dados.amuletos[i].coletado = (coletado == 1);
    }

    fclose(arquivo);
}