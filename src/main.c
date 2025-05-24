#include <stdio.h>
#include <allegro5/allegro.h>
#include "pages/game/game_page.h"

int main(int argc, char **argv) {
    if (!al_init()) {
        printf("Erro ao inicializar o Allegro!\n");
        return -1;
    }

    run_game();

    return 0;
}