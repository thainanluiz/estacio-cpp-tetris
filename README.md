# Lletris — Tetris Invertido em C

Projeto feito para a disciplina de Programação de Software Básico em C na Estácio.

## Como funciona?

- As peças aparecem embaixo e vão subindo.
- Você controla igual ao Tetris normal (setas do teclado).
- Se a pilha chegar no topo, perdeu.

## O que você precisa pra rodar

- Windows com MinGW-w64 instalado ([download disponível neste link](https://www.mingw-w64.org/))
- Allegro 5 já baixado e configurado (as DLLs e includes estão na pasta `libs`)
- Terminal com `mingw32-make` funcionando

## Como compilar

Abra o terminal na pasta do projeto e rode:

```bash
mingw32-make
```

Se tudo der certo, vai aparecer o executável em `bin/lletris.exe`.

## Como jogar

Depois de compilar, é só rodar:

```bash
./bin/lletris.exe
```

Ou dar dois cliques no arquivo pelo Windows Explorer.

## Estrutura do projeto

```
assets/      # Imagens e sons
bin/         # Executável
libs/        # Bibliotecas Allegro
src/         # Código-fonte em C
Makefile     # Script pra compilar
README.md    # Este arquivo
```

## Observações

- O projeto está em desenvolvimento.
- Se der erro de Allegro 5, confira se as DLLs estão na pasta `bin` ou no PATH do Windows.
