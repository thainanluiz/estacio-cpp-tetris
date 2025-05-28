# Define o compilador C
CC = gcc

# Define os arquivos fonte a serem compilados
SRC = src/main.c
SRC += src/pages/game/game_page.c
SRC += src/components/block/block.c
SRC += src/components/cronometro/cronometro.c
SRC	+= src/components/placar/placar.c

# Define o nome e caminho do arquivo executável final
BIN = bin/lletris.exe

# Define os diretórios de inclusão de cabeçalhos
INCLUDES = -Ilibs/include -Isrc

# Define os diretórios das bibliotecas
LIBDIRS = -Llibs/lib

# Define as bibliotecas a serem linkadas
LIBS = -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_dialog

# Define o diretório de origem dos assets
ASSETS_SRC_DIR = assets

# Define o diretório de destino dos assets no build
# $(dir $(BIN)) pega o diretório de BIN (ex: "bin/") e concatena com "assets"
ASSETS_DEST_DIR = $(dir $(BIN))assets

# Alvo padrão: constrói o binário (que agora depende dos assets)
all: $(BIN)

# Regra para preparar/copiar os assets
# Esta regra será uma dependência para o binário
# Usamos $(subst /,\, ...) para converter barras normais em barras invertidas para comandos do Windows
prepare_assets:
	@echo "Copiando assets de $(ASSETS_SRC_DIR) para $(ASSETS_DEST_DIR)..."
	@if [ ! -d "$(ASSETS_DEST_DIR)" ]; then mkdir -p "$(ASSETS_DEST_DIR)"; fi
	@cp -r "$(ASSETS_SRC_DIR)/." "$(ASSETS_DEST_DIR)/"
	@echo "Assets copiados com sucesso."

# Regra para construir o binário
# Adiciona 'prepare_assets' como um pré-requisito.
# Isso garante que os assets sejam copiados antes da compilação, se necessário,
# ou pelo menos antes que 'all' seja concluído.
$(BIN): $(SRC) prepare_assets
	@echo "Compilando o projeto..."
	$(CC) $(SRC) -o $(BIN) $(INCLUDES) $(LIBDIRS) $(LIBS)
	@echo "Projeto compilado: $(BIN)"

# Alvo para limpar os arquivos gerados
clean:
	@echo "Limpando arquivos de build..."
	@if [ -f "$(BIN)" ]; then rm -f "$(BIN)"; else echo "Arquivo $(BIN) não encontrado."; fi
	@if [ -d "$(ASSETS_DEST_DIR)" ]; then rm -rf "$(ASSETS_DEST_DIR)"; echo "Diretório $(ASSETS_DEST_DIR) removido."; else echo "Diretório $(ASSETS_DEST_DIR) não encontrado."; fi
	@echo "Limpeza concluída."

# Adicionando .PHONY para evitar conflitos com arquivos chamados 'all', 'clean', ou 'prepare_assets'
# e para garantir que as regras sejam executadas mesmo que arquivos com esses nomes existam.
.PHONY: all clean prepare_assets
