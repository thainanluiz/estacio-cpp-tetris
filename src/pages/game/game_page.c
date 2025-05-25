#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "constants/allegro_constants.h"
#include "components/block/block.h"
#include "pages/game/game_page.h"

bool run_game() {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *background = NULL;

    al_init_primitives_addon();
    al_init_image_addon();

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        printf("Erro ao instanciar a tela!\n");
        return false;
    }

    background = al_load_bitmap("assets/images/game_bg_placeholder.png");
    if (!background) {
        printf("Erro ao carregar a imagem de fundo!\n");
        al_destroy_display(display);
        return false;
    }
    
    al_draw_bitmap(background, 0, 0, 0);

    Tetromino t = create_tetromino(TETROMINO_T, 5, 5, 2);

    for (int i = 0; i < 4; i++) {
        Block b = t.blocks[i];
        al_draw_filled_rectangle(
            b.x * 20, b.y * 20,
            b.x * 20 + 20, b.y * 20 + 20,
            al_map_rgb(255, 0, 0)
        );
    }

    al_flip_display();

    al_rest(TESTING_DELAY);

    al_destroy_bitmap(background);
    al_destroy_display(display);
    return true;
}