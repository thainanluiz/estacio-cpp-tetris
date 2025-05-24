#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "pages/game/game_page.h"
#include "constants/allegro_constants.h"

void run_game() {
    ALLEGRO_DISPLAY *display = NULL;

    al_init();
    al_init_primitives_addon();

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        printf("Erro ao instanciar a tela!\n");
        return;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    al_rest(5.0);

    al_destroy_display(display);
}