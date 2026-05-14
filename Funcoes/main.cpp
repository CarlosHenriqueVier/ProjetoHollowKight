#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

// --- Estruturas ---
struct infoTela {
    const int largura = 1200;
    const int altura = 800;
    char titulo[15] = "Hollow Knight";
} tela;

struct infoBloco {
    const float largura = 10;
    const float altura = 10;
} bloco;

struct infoMapa {
    const int colunas = 151; // Largura do TXT
    const int linhas = 16;   // Altura do TXT
    char localMapa[20] = "Mapas/MapaTeste.txt";
    char** matrizMapa;
} map;

struct infoPersonagem {
    Vector2 posicao = { 10, 700 };
    Texture2D imagem;
} personagem;
// Protótipos de funções
Vector2 movimentaPersoangem(Vector2);

char** leituraMapa(struct infoMapa info);

void liberaMapa(char** matriz, int linhas);

void startJogo(void);

void saveGame(void);

void outGame(void);

char menu(void);

// Criamos uma variável para controlar onde o jogador está
enum Estado { ESTADO_MENU, ESTADO_JOGANDO };
Estado estadoAtual = ESTADO_MENU;

int main(void) {
    InitWindow(tela.largura, tela.altura, tela.titulo);
    map.matrizMapa = leituraMapa(map);
    personagem.imagem = LoadTexture("Texturas/Personagem/Personagem1.png");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        if (estadoAtual == ESTADO_MENU) {
            // No menu, apenas verificamos se ele quer começar
            if (IsKeyPressed(KEY_C)) {
                estadoAtual = ESTADO_JOGANDO;
            }

            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("HOLLOW KNIGHT - MENU", 400, 300, 30, WHITE);
            DrawText("Pressione 'C' para iniciar", 450, 400, 20, WHITE);
            EndDrawing();
        }
        else if (estadoAtual == ESTADO_JOGANDO) {
            // Se estiver jogando, chama a função de lógica/desenho
            startJogo();

            // Se apertar ESC, volta para o menu
            if (IsKeyPressed(KEY_ESCAPE)) {
                estadoAtual = ESTADO_MENU;
            }
        }
    }

    UnloadTexture(personagem.imagem);
    liberaMapa(map.matrizMapa, map.linhas);
    CloseWindow();
    return 0;
}

//Funções:

char** leituraMapa(struct infoMapa info) {
    FILE* abreMapa = fopen(info.localMapa, "r");
    if (abreMapa == NULL) return NULL;

    // Aloca as linhas
    char** matriz = (char**)malloc(info.linhas * sizeof(char*));
    for (int i = 0; i < info.linhas; i++) {
        // Aloca colunas (+2 para garantir espaço do \n e \0)
        matriz[i] = (char*)malloc((info.colunas + 2) * sizeof(char));
        if (fgets(matriz[i], info.colunas + 2, abreMapa) == NULL) {
            matriz[i][0] = '\0';
        }
    }

    fclose(abreMapa);
    return matriz;
}

void liberaMapa(char** matriz, int linhas) {
    if (matriz == NULL) return;
    for (int i = 0; i < linhas; i++) free(matriz[i]);
    free(matriz);
}

Vector2 movimentaPersoangem(Vector2 personagemPosicao) {
    float velocidade = 5.0f;//quanto o perosnagem andará
    if (IsKeyDown(KEY_LEFT) && personagemPosicao.x > 0) {
        personagemPosicao.x -= velocidade;
    }
    if (IsKeyDown(KEY_RIGHT) && personagemPosicao.x < 1100) {
        personagemPosicao.x += velocidade;
    }
    if (IsKeyDown(KEY_UP) && personagemPosicao.y > 0) {
        personagemPosicao.y -= velocidade;
    }
    if (IsKeyDown(KEY_DOWN) && personagemPosicao.y < 700) {
        personagemPosicao.y += velocidade;
    }
    return personagemPosicao;
}

void startJogo(void) {
        // Atualização
        personagem.posicao = movimentaPersoangem(personagem.posicao);

        // Desenho
        BeginDrawing();
        ClearBackground(BLACK);

        // 2. Lógica para desenhar o mapa
        if (map.matrizMapa != NULL) {
            for (int i = 0; i < map.linhas; i++) {
                for (int j = 0; j < map.colunas; j++) {
                    // Verifica se o caractere não é espaço ou quebra de linha
                    char caractere = map.matrizMapa[i][j];
                    if (caractere != ' ' && caractere != '\n' && caractere != '\0' && caractere != '\r') {

                        // Calcula a posição do bloco baseado no índice da matriz
                        float posX = j * bloco.largura;
                        float posY = i * bloco.altura;

                        DrawRectangle(posX, posY, bloco.largura - 1, bloco.altura - 1, GREEN);

                    }
                }
            }
        }
        DrawTextureV(personagem.imagem, personagem.posicao, WHITE);
        EndDrawing();
}

char menu(void) {
    // Por enquanto, apenas detecta se o jogador apertou 'C'
    if (IsKeyPressed(KEY_C)) return 'c';
    if (IsKeyPressed(KEY_S)) return 's';
    if (IsKeyPressed(KEY_O)) return 'o';

    return ' '; // Retorna vazio se nenhuma tecla do menu foi pressionada
}
void saveGame(void) {
    // Lógica de salvar futuramente
}

void outGame(void) {
    // Lógica de sair
    CloseWindow();
    exit(0);
}