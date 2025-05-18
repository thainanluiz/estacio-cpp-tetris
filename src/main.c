#include <stdio.h>
#include <allegro5/allegro.h>

int main(int argc, char **argv) {
    if (!al_init()) {
        printf("Erro ao inicializar o Allegro!\n");
        return -1;
    }

    printf("Allegro inicializado com sucesso!\n");
    printf("Pressione Enter para sair...");
    getchar();

    return 0;
}
