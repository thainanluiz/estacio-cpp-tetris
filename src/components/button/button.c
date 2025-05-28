#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro_primitives.h>
#include "components/button/button.h"

Button create_button(float x, float y, float width, float height, const char *text, ALLEGRO_FONT *font, ButtonAction action)
{
    Button btn;
    btn.x = x;
    btn.y = y;
    btn.width = width;
    btn.height = height;
    btn.text = text ? strdup(text) : NULL;
    btn.font = font;
    btn.action = action;

    btn.bg_color_normal = al_map_rgb(100, 100, 100);
    btn.bg_color_hover = al_map_rgb(150, 150, 150);
    btn.bg_color_pressed = al_map_rgb(50, 50, 50);
    btn.text_color = al_map_rgb(255, 255, 255);

    btn.is_hovered = false;
    btn.is_pressed = false;
    return btn;
}

void update_button_state(Button *button, ALLEGRO_MOUSE_STATE *mouse_state, ALLEGRO_EVENT_TYPE event_type)
{
    if (!button)
        return;

    bool mouse_over = (mouse_state->x >= button->x && mouse_state->x <= button->x + button->width &&
                       mouse_state->y >= button->y && mouse_state->y <= button->y + button->height);

    button->is_hovered = mouse_over;

    if (event_type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && mouse_state->buttons & 1 && mouse_over)
    {
        button->is_pressed = true;
    }
    else if (event_type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && button->is_pressed)
    {
        if (mouse_over)
        {
            handle_button_click(button);
        }
        button->is_pressed = false;
    }
    else if (!(mouse_state->buttons & 1))
    {
        button->is_pressed = false;
    }
}

void draw_button(Button *button)
{
    if (!button)
        return;

    ALLEGRO_COLOR current_bg_color = button->bg_color_normal;
    if (button->is_pressed)
    {
        current_bg_color = button->bg_color_pressed;
    }
    else if (button->is_hovered)
    {
        current_bg_color = button->bg_color_hover;
    }

    al_draw_filled_rectangle(button->x, button->y, button->x + button->width, button->y + button->height, current_bg_color);
    al_draw_rectangle(button->x, button->y, button->x + button->width, button->y + button->height, al_map_rgb(0, 0, 0), 2);

    if (button->text && button->font)
    {
        float text_width = al_get_text_width(button->font, button->text);
        float text_height = al_get_font_line_height(button->font);
        al_draw_text(button->font, button->text_color,
                     button->x + (button->width - text_width) / 2,
                     button->y + (button->height - text_height) / 2,
                     0, button->text);
    }
}

void handle_button_click(Button *button)
{
    if (button && button->action)
    {
        button->action();
    }
}