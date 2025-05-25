# Define o compilador C
CC = gcc

# Define os arquivos fonte a serem compilados
SRC = src/main.c src/pages/game/game_page.c src/components/block/block.c

# Define o nome e caminho do arquivo executável final
BIN = bin/lletris.exe

# Define os diretórios de inclusão de cabeçalhos
INCLUDES = -Ilibs/include -Isrc

# Define os diretórios das bibliotecas
LIBDIRS = -Llibs/lib

# Define as bibliotecas a serem linkadas
LIBS = -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives

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
	@echo Copiando assets de $(ASSETS_SRC_DIR) para $(ASSETS_DEST_DIR)...
	@REM Cria o diretório de destino dos assets se não existir
	@if not exist "$(subst /,\,$(ASSETS_DEST_DIR))" ( mkdir "$(subst /,\,$(ASSETS_DEST_DIR))" )
	@REM Copia os arquivos e pastas de assets para o diretório de destino
	@xcopy "$(subst /,\,$(ASSETS_SRC_DIR))" "$(subst /,\,$(ASSETS_DEST_DIR))\" /E /I /S /Y /Q
	@echo Assets copiados com sucesso.

# Regra para construir o binário
# Adiciona 'prepare_assets' como um pré-requisito.
# Isso garante que os assets sejam copiados antes da compilação, se necessário,
# ou pelo menos antes que 'all' seja concluído.
$(BIN): $(SRC) prepare_assets
	@echo Compilando o projeto...
	$(CC) $(SRC) -o $(BIN) $(INCLUDES) $(LIBDIRS) $(LIBS)
	@echo Projeto compilado: $(BIN)

# Alvo para limpar os arquivos gerados
clean:
	@echo Limpando arquivos de build...
	@REM Comando para deletar o executável no Windows.
	@if exist "$(subst /,\,$(BIN))" ( del /F /Q "$(subst /,\,$(BIN))" ) else ( echo Arquivo $(BIN) nao encontrado. )
	@REM Comando para remover o diretório de assets copiado no Windows
	@if exist "$(subst /,\,$(ASSETS_DEST_DIR))" ( rmdir /S /Q "$(subst /,\,$(ASSETS_DEST_DIR))" && echo Diretorio $(ASSETS_DEST_DIR) removido. ) else ( echo Diretorio $(ASSETS_DEST_DIR) nao encontrado. )
	@echo Limpeza concluida.

# Adicionando .PHONY para evitar conflitos com arquivos chamados 'all', 'clean', ou 'prepare_assets'
# e para garantir que as regras sejam executadas mesmo que arquivos com esses nomes existam.
.PHONY: all clean prepare_assets
