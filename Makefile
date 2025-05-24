# Define o compilador C
CC = gcc

# Define os arquivos fonte a serem compilados
SRC = src/main.c src/pages/game/game_page.c

# Define o nome e caminho do arquivo executável final
BIN = bin/lletris.exe

# Define os diretórios de inclusão de cabeçalhos
INCLUDES = -Ilibs/include -Isrc

# Define os diretórios das bibliotecas
LIBDIRS = -Llibs/lib

# Define as bibliotecas a serem linkadas
LIBS = -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives

# Alvo padrão: constrói o binário
all: $(BIN)

# Regra para construir o binário
# Esta regra agora usa a variável SRC para incluir todos os arquivos fonte definidos.
$(BIN): $(SRC)
	$(CC) $(SRC) -o $(BIN) $(INCLUDES) $(LIBDIRS) $(LIBS)

# Alvo para limpar os arquivos gerados
clean:
	# Comando para deletar no Windows. Use 'rm -f $(BIN)' para Linux/macOS
	del /Q bin\lletris.exe 2>NUL || (exit 0)

# Adicionando .PHONY para evitar conflitos com arquivos chamados 'all' ou 'clean'
.PHONY: all clean
