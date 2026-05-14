#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

void MostraTeste(void);

Vector2 movimentaPersoangem(Vector2);



struct infoTela
{
	const int largura = 1200;//pixel
	const int altura = 800;//pixel
	char titulo[14] = { "Hollow Knight" };
}tela;

struct infoMapa
{

}map;

struct infoPersonagem
{
	const int largura = 175;//pixel
	const int altura = 175;//pixel
	Vector2 posicao =
	{
		10,//x 
		700,//y -> (tela.altura - personagem.altura)
	};
	int quantidadeVida = 4;
	int vida = 100;
	int energia = 0;
	Texture2D imagem;
}personagem;

int main(void)
{
	InitWindow(tela.largura, tela.altura, tela.titulo);

	MostraTeste();
	CloseWindow();
	
	return 0;
}
Vector2 movimentaPersoangem(Vector2 personagemPosicao) {
	if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
		if(personagemPosicao.x > 5){
		personagemPosicao.x -= 4.0f;
		}
	}
	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
		if (personagemPosicao.x < 1030) {
			personagemPosicao.x += 7.0f;
		}
	}
	if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
		if (personagemPosicao.y > 100){
		personagemPosicao.y -= 7.0f;
		}
	}
	if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
		if(personagemPosicao.y < 700)
		personagemPosicao.y += 7.0f;
	}
	return personagemPosicao;
}

void MostraTeste(void) {

	personagem.imagem = LoadTexture("Texturas/Personagem/Personagem1.png");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		personagem.posicao = movimentaPersoangem(personagem.posicao);

		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangle(10, 10, 100, 20, RED);
		DrawRectangle(10, 30, 100, 20, BLUE);

		DrawTextureEx(
			personagem.imagem,
			personagem.posicao,
			0.0f,
			0.5f,
			WHITE
		);
		EndDrawing();
	}
	UnloadTexture(personagem.imagem);
}
/*
void leituraMapa(void) {
	FILE* abreMapa;
	abreMapa = fopen("Mapas\MapaTeste.txt", "r");
	if (abreMapa == NULL) {
		if (abreMapa == NULL) {
			printf("Erro ao abrir o mapa.\n");
		}
	}
	printf("");
	fclose(abreMapa);
}
*/