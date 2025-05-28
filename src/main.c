#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include "constants/allegro_constants.h"
#include "pages/menu/menu_page.h"
#include "pages/game/game_page.h"
#include "pages/game_over/game_over_page.h"
#include "components/field/field_utils.h"


int main()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT *font_main_buttons = NULL;

    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return -1;
    }

    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_uninstall_system();
        return -1;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        al_uninstall_system();
        return -1;
    }

    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_native_dialog_addon();

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display)
    {
        fprintf(stderr, "Falha ao criar a tela.\n");
        al_uninstall_system();
        return -1;
    }
    al_set_window_title(display, "Lletris");

    font_main_buttons = al_load_ttf_font(ALLEGRO_FONT_C, 24, 0);
    if (!font_main_buttons)
    {
        font_main_buttons = al_load_ttf_font(ALLEGRO_FONT_C, 24, 0);
        if (!font_main_buttons)
        {
            fprintf(stderr, "Falha ao carregar a fonte para os botões. Verifique o caminho 'assets/fonts/PixelOperator.ttf'.\n");
            al_destroy_display(display);
            al_uninstall_system();
            return -1;
        }
    }

    GameState current_app_state = GAME_STATE_MENU;

    while (current_app_state != GAME_STATE_EXIT)
    {
        if (current_app_state == GAME_STATE_MENU)
        {
            current_app_state = run_menu(display, font_main_buttons);
        }
        else if (current_app_state == GAME_STATE_PLAYING)
        {
            if (run_game(display))
            {
                current_app_state = GAME_STATE_MENU;
            }
            else
            {
                current_app_state = run_game_over(display, font_main_buttons);
            }
        }
    }

    if (font_main_buttons)
    {
        al_destroy_font(font_main_buttons);
    }
    if (display)
    {
        al_destroy_display(display);
    }

    printf("Jogo encerrado.\n");
    return 0;
}