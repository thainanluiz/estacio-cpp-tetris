#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "constants/allegro_constants.h"
#include "pages/game/game_page.h"
#include "pages/menu/menu_page.h"
#include "components/button/button.h"

static GameState current_game_state;

void action_start_game()
{
  printf("Botão Iniciar Jogo clicado!\n");
  current_game_state = GAME_STATE_PLAYING;
}

void action_exit_game()
{
  printf("Botão Sair clicado!\n");
  current_game_state = GAME_STATE_EXIT;
}

GameState run_menu(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font_buttons)
{
  current_game_state = GAME_STATE_MENU;

  ALLEGRO_BITMAP *background = al_load_bitmap("assets/images/bg_m.png");
  if (!background)
  {
    fprintf(stderr, "Falha ao carregar a imagem de fundo do menu.\n");
  }

  ALLEGRO_SAMPLE *click_sound = al_load_sample("assets/sfx/btn.mp3");
  if (!click_sound)
  {
    fprintf(stderr, "Falha ao carregar o som de clique.\n");
  }

  ALLEGRO_EVENT_QUEUE *menu_event_queue = al_create_event_queue();
  if (!menu_event_queue)
  {
    fprintf(stderr, "Falha ao criar a fila de eventos do menu.\n");
    if (click_sound)
      al_destroy_sample(click_sound);
    return GAME_STATE_EXIT;
  }

  al_register_event_source(menu_event_queue, al_get_display_event_source(display));
  al_register_event_source(menu_event_queue, al_get_mouse_event_source());

  Button btn_start = create_button(
      SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50,
      200, 50,
      "Iniciar Jogo", font_buttons, action_start_game, click_sound);

  Button btn_exit = create_button(
      SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20,
      200, 50,
      "Sair", font_buttons, action_exit_game, click_sound);

  bool running_menu = true;
  while (running_menu && current_game_state == GAME_STATE_MENU)
  {
    ALLEGRO_EVENT ev;
    al_wait_for_event(menu_event_queue, &ev);

    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    update_button_state(&btn_start, &mouse_state, ev.type);
    update_button_state(&btn_exit, &mouse_state, ev.type);

    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      current_game_state = GAME_STATE_EXIT;
      running_menu = false;
    }

    if (background)
    {
      al_draw_bitmap(background, 0, 0, 0);
    }
    else
    {
      al_clear_to_color(al_map_rgb(30, 30, 30));
    }

    draw_button(&btn_start);
    draw_button(&btn_exit);
    al_flip_display();
  }

  al_destroy_event_queue(menu_event_queue);
  if (background)
  {
    al_destroy_bitmap(background);
  }

  return current_game_state;
}