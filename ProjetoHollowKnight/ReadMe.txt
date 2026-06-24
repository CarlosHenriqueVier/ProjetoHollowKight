ATENÇÃO
PARA O ARQUIVO .BAT EM "MAKEFILE" FUNCIONAR CORRETAMENTE, COLOQUE CADA ARQUIVO NAS PASTA CORRETA

ALÉM DO TEMPLATE E DAS INSTRUÇÕES ABAIXO, É PRECISO BAIXAR O RAYLIB E COLOCAR DIRETAMENTE EM "C:\"
Ex: "C:\raylib"

Assets:
-Contém os arquivos de mídia do programa: texturas, áudios, fontes,...
-É possível criar pastas dentro, mas na utilização da mídia será preciso adicionar o primeiro diretório
Ex1: "...\assets\ataque.png"
Neste caso basta usar "personagem.png"
Ex2: "...\assets\personagem\ataque.png"
Neste caso é preciso usar o diretório "personagem\ataque.png"

Data: 
-Contém os arquivos de dados: saves, rankings,...

Include:
-Contém os headers do programa (.h)

Makefile:
-Contém o comando de compilação com flags
-Utilize ele para gerar um executável (.exe) na pasta principal/geral do programa

Maps:
-Contém os arquivos texto (.txt) de mapas do programa

Src:
Contém os arquivos fonte/códigos do programa (.c)