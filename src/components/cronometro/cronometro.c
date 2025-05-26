#include "cronometro.h"
#include <stdio.h>

Cronometro criar_cronometro(void) {
    Cronometro c;
    c.timer = al_create_timer(1.0); // timer 1 segundo
    if (!c.timer) {
        fprintf(stderr, "Falha ao criar o timer do cronômetro.\n");
        exit(EXIT_FAILURE);
    }
    c.segundos = 0;
    c.minutos = 0;
    return c;
}

void atualizar_cronometro(Cronometro *c) {
    c->segundos++;
    if (c->segundos >= 60) {
        c->segundos = 0;
        c->minutos++;
    }
}

void destruir_cronometro(Cronometro *c) {
    if (c->timer) {
        al_destroy_timer(c->timer);
        c->timer = NULL;
    }
}
