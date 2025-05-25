#include <stdio.h>
#include <allegro5/allegro.h>
#include "pages/game/game_page.h"

int main(int argc, char **argv) {
    if (!al_init()) {
        printf("Erro ao inicializar o Allegro!\n");
        scanf("%*s");
        return -1;
    }

    if (!run_game()) {
        printf("Erro ao iniciar a tela principal do jogo!\n");
        scanf("%*s");
        return -1;
    }

    return 0;
}