#include <stdio.h>
#include <allegro5/allegro.h>
#include "pages/game/game_page.h"

int main(int argc, char **argv)
{
    if (!al_init())
    {
        printf("Erro ao inicializar o Allegro!\n");
        getchar();
        return -1;
    }
    printf("Allegro iniciado com sucesso!\n");

    if (!run_game())
    {
        printf("Erro ao iniciar a tela principal do jogo!\n");
        getchar();
        return -1;
    }

    printf("run_game finalizado normalmente\n");
    getchar();
    return 0;
}
