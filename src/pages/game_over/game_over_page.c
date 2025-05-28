#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "constants/allegro_constants.h"
#include "pages/game/game_page.h"
#include "pages/menu/menu_page.h"
#include "components/button/button.h"

static GameState current_game_state;

void action_return_menu(){
    current_game_state = GAME_STATE_MENU;
}

GameState run_game_over(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font_buttons) {
    current_game_state = GAME_STATE_GAME_OVER;

    ALLEGRO_BITMAP *background = al_load_bitmap("assets/images/bg_m.png");
    if (!background){
        fprintf(stderr, "Falha ao carregar a imagem de fundo do game over.\n");
    }
    
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    if (!event_queue){
        fprintf(stderr, "Falha ao criar a fila de eventos do game over.\n");
        return GAME_STATE_EXIT;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    Button btn_menu = create_button(
        SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 40, 200, 50, 
        "Voltar ao menu", font_buttons, action_return_menu);

    bool running = true;
    while(running && current_game_state == GAME_STATE_GAME_OVER){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        ALLEGRO_MOUSE_STATE mouse_state;
        al_get_mouse_state(&mouse_state);

        update_button_state(&btn_menu, &mouse_state, ev.type);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            current_game_state = GAME_STATE_EXIT;
            running = false;
        }

        if(background){
            al_draw_bitmap(background, 0,0,0);
        } else {
            al_clear_to_color(al_map_rgb(50,0,0));
        }

        al_draw_text(font_buttons, al_map_rgb(255,0,0), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60, ALLEGRO_ALIGN_CENTRE,
         "GAME OVER");

         draw_button(&btn_menu);
         al_flip_display();
    }

    al_destroy_event_queue(event_queue);
    if(background){
        al_destroy_bitmap(background);
    }

    return current_game_state;

}