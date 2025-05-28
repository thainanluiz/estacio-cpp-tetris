#ifndef MENU_PAGE_H
#define MENU_PAGE_H

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

typedef enum
{
  GAME_STATE_MENU,
  GAME_STATE_PLAYING,
  GAME_STATE_GAME_OVER,
  GAME_STATE_EXIT
} GameState;

GameState run_menu(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font_buttons);

#endif