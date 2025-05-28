#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "constants/allegro_constants.h"
#include "components/placar/placar.h"

static int pontuacao = 0;
static ALLEGRO_FONT *fonte_placar = NULL;

void inicializar_placar()
{
    fonte_placar = al_load_ttf_font(ALLEGRO_ARIAL, 24, 0);
    if (!fonte_placar)
    {
        al_show_native_message_box(NULL, "Erro", "Fonte", "Não foi possível carregar a fonte do placar!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }
    pontuacao = 0;
}

void adicionar_pontos(int linhas_completas)
{
    switch (linhas_completas)
    {
    case 1:
        pontuacao += 100;
        break;
    case 2:
        pontuacao += 300;
        break;
    case 3:
        pontuacao += 500;
        break;
    case 4:
        pontuacao += 800;
        break;
    default:
        pontuacao += linhas_completas * 100;
        break;
    }
}

void desenhar_placar()
{
    if (fonte_placar)
    {
        char texto[64];
        snprintf(texto, sizeof(texto), "Pontos: %d", pontuacao);
        int largura_texto = al_get_text_width(fonte_placar, texto);
        int altura_texto = al_get_font_line_height(fonte_placar);
        al_draw_text(fonte_placar, al_map_rgb(255, 255, 255),
                     SCREEN_WIDTH - largura_texto - 10,
                     SCREEN_HEIGHT - altura_texto - 10,
                     0, texto);
    }
}
