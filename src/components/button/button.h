#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

typedef struct Button Button;

typedef void (*ButtonAction)(void);

struct Button
{
  float x, y, width, height;
  char *text;
  ALLEGRO_FONT *font;
  ALLEGRO_COLOR bg_color_normal;
  ALLEGRO_COLOR bg_color_hover;
  ALLEGRO_COLOR bg_color_pressed;
  ALLEGRO_COLOR text_color;
  bool is_hovered;
  bool is_pressed;
  ButtonAction action;
  ALLEGRO_SAMPLE *click_sound;
};

Button create_button(float x, float y, float width, float height, const char *text, ALLEGRO_FONT *font, ButtonAction action, ALLEGRO_SAMPLE *click_sound);
void update_button_state(Button *button, ALLEGRO_MOUSE_STATE *mouse_state, ALLEGRO_EVENT_TYPE event_type);
void draw_button(Button *button);
void handle_button_click(Button *button);

#endif