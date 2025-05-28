#ifndef CRONOMETRO_H
#define CRONOMETRO_H

#include <allegro5/allegro.h>

typedef struct
{
    ALLEGRO_TIMER *timer;
    int segundos;
    int minutos;
} Cronometro;

Cronometro criar_cronometro(void);
void atualizar_cronometro(Cronometro *c);
void destruir_cronometro(Cronometro *c);

#endif
