#include "estruturas.h"

// Aqui cria e inicializa as variáveis de verdade

infoTela tela = { 
    1500, 
    800, 
    "Hollow Knight",
    { {0,0}, {0,0}, 0.0f, 2.0f }  // camera
};

infoEntidade personagem = {
    { 0, 0 },     // Será definido pelo 'J' no mapa
    { 0, 0 },     // posicaoInicial
    { 0 },        // imagem
    false,        // colidindo
    30,           // largura
    30,           // altura
    true,         // olhandoDireita 
    { 100, 50, false, true } // dados
};

// MODIFICADO: Inicializa o array de inimigos zerado. O mapa vai preencher cada um.
infoEntidade listaInimigos[MAX_INIMIGOS] = { 0 };
int quantidadeInimigos = 0;

infoMapa map = { 
    151, 
    16, 
    {"Mapa/Mapas/mapaInicial.txt"},
    nullptr
};

infoBloco bloco = { 
    30.0f, 
    30.0f 
};

infoMenu menuPrincipal = {
    4,          // totalOpcoes
    0,          // opcaoSelecionada
    { 300, 400, 500, 600 },  // botoesY
    200,        // botaoW
    50          // botaoH
};

infoMenu menuPause = {
    4,          // totalOpcoes
    0,          // opcaoSelecionada
    { 220, 290, 360, 430 },  // botoesY
    260,        // botaoW
    55          // botaoH
};

infoMenu menuConfiguracoes = {
    3,          // totalOpcoes
    0,          // opcaoSelecionada
    { 294, 361, 428 },  // botoesY
    200,        // botaoW
    50          // botaoH
};

constantes constantesJogo = {
    3.0f,   // velocidade
    0.5f,   // gravidade
    -10.0f,  // forcaPulo
    0.0f    // velocidadeY padrão
};