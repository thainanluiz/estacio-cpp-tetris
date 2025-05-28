#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include "constants/allegro_constants.h"
#include "components/block/block.h"
#include "components/cronometro/cronometro.h"
#include "components/placar/placar.h"

#define BLOCK_SIZE    20

#define FIELD_WIDTH  (SCREEN_WIDTH / BLOCK_SIZE)
#define FIELD_HEIGHT (SCREEN_HEIGHT / BLOCK_SIZE)

#define SPAWN_POS_X (FIELD_WIDTH / 2)
#define SPAWN_POS_Y (FIELD_HEIGHT - 2)

// 0 = vazio, >0 = cor do bloco
int field[FIELD_HEIGHT][FIELD_WIDTH] = {0};

// Checa colisão do tetromino com campo e bordas
int check_collision(Tetromino *tet) {
    for (int i = 0; i < 4; i++) {
        int x = tet->blocks[i].x;
        int y = tet->blocks[i].y;
        if (y < 0 || y >= FIELD_HEIGHT || x < 0 || x >= FIELD_WIDTH)
            return 1;
        if (field[y][x] != 0)
            return 1;
    }
    return 0;
}

// Fixa o tetromino no campo
void fix_tetromino(Tetromino *tet) {
    for (int i = 0; i < 4; i++) {
        int x = tet->blocks[i].x;
        int y = tet->blocks[i].y;
        if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH)
            field[y][x] = tet->blocks[i].color;
    }
}

// Mapeia cor para RGB
ALLEGRO_COLOR color_map(int color) {
    switch (color) {
        case 1: return al_map_rgb(220, 80, 80);    // Vermelho
        case 2: return al_map_rgb(80, 200, 120);   // Verde
        case 3: return al_map_rgb(80, 120, 220);   // Azul
        case 4: return al_map_rgb(240, 220, 120);  // Amarelo
        case 5: return al_map_rgb(180, 120, 220);  // Magenta
        case 6: return al_map_rgb(120, 220, 220);  // Ciano
        case 7: return al_map_rgb(240, 170, 80);   // Laranja
        default: return al_map_rgb(180, 180, 180); // Cinza claro
    }
}

int clear_full_lines() {
    int lines_cleared = 0;
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        int full = 1;
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (field[y][x] == 0) {
                full = 0;
                break;
            }
        }
        if (full) {
            // Move todas as linhas acima para baixo
            for (int yy = y; yy < FIELD_HEIGHT - 1; yy++) {
                for (int x = 0; x < FIELD_WIDTH; x++) {
                    field[yy][x] = field[yy + 1][x];
                }
            }
            // Limpa a última linha
            for (int x = 0; x < FIELD_WIDTH; x++) {
                field[FIELD_HEIGHT - 1][x] = 0;
            }
            // Verifica a mesma linha novamente (pois ela agora tem a linha de cima)
            y--;
            lines_cleared++;
        }
    }
    return lines_cleared;
}

bool run_game() {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    Cronometro cronometro = criar_cronometro();

    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    inicializar_placar();

    ALLEGRO_FONT *font = al_load_ttf_font(ALLEGRO_ARIAL, 24, 0); // Caminho e tamanho ajustáveis
    if (!font) {
        printf("Erro ao carregar a fonte!\n");
        al_destroy_font(font);
        return false;
    }

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        printf("Erro ao instanciar a tela!\n");
        return false;
    }

    background = al_load_bitmap("assets/images/game_bg_placeholder.png");
    if (!background) {
        printf("Erro ao carregar a imagem de fundo!\n");
        al_destroy_display(display);
        return false;
    }

    srand((unsigned int)time(NULL));

    timer = al_create_timer(1.0 / 60.0);
    if(!timer) {
        al_show_native_message_box(NULL, "Erro", "Erro crítico", "Erro ao criar o timer do jogo!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }
    al_start_timer(timer);

    al_start_timer(cronometro.timer);

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_timer_event_source(cronometro.timer));
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_install_mouse();
    al_register_event_source(queue, al_get_mouse_event_source());

    int cor_aleatoria = 1 + rand() % 7;
    Tetromino current = create_tetromino(
        rand() % TETROMINO_COUNT,
        SPAWN_POS_X,
        SPAWN_POS_Y,
        cor_aleatoria,
        0 // NÃO usar cores aleatórias por bloco
    );

    al_start_timer(timer);

    int running = 1;
    int accelerate = 0;
    int frame_counter = 0;
    int move_interval = 20; // quanto maior, mais devagar

    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = 0;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            Tetromino moved = current;
            if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
                for (int i = 0; i < 4; i++) moved.blocks[i].x -= 1;
                if (!check_collision(&moved)) current = moved;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
                for (int i = 0; i < 4; i++) moved.blocks[i].x += 1;
                if (!check_collision(&moved)) current = moved;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
                accelerate = 1;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
                accelerate = 0;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            Tetromino rotated = current;
            int pivot_x = current.blocks[1].x;
            int pivot_y = current.blocks[1].y;
            if (ev.mouse.button == 1) { // Esquerdo: horário
                rotate_tetromino(&rotated, 1, pivot_x, pivot_y);
                if (!check_collision(&rotated)) current = rotated;
            } else if (ev.mouse.button == 2) { // Direito: anti-horário
                rotate_tetromino(&rotated, -1, pivot_x, pivot_y);
                if (!check_collision(&rotated)) current = rotated;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == timer) {
            frame_counter++;

            int move_up_steps = 0;
            if (accelerate) { // Se 'W' está pressionado, move a cada frame
                move_up_steps = 1;
            } else if (frame_counter >= move_interval) {
                move_up_steps = 1;
                frame_counter = 0;
            }

            for (int step = 0; step < move_up_steps && running; step++) {
                Tetromino next_pos = current;
                for (int i = 0; i < 4; i++) {
                    next_pos.blocks[i].y -= 1; // Tenta mover para cima
                }

                if (check_collision(&next_pos)) {
                    // Colisão, a peça não pode subir mais
                    fix_tetromino(&current);
                    int linhas = clear_full_lines();
                    if (linhas > 0) {
                        adicionar_pontos(linhas);
                    }

                    // Gera novo tetromino
                    cor_aleatoria = 1 + rand() % 7;
                    current = create_tetromino(
                        rand() % TETROMINO_COUNT,
                        SPAWN_POS_X,
                        SPAWN_POS_Y,
                        cor_aleatoria,
                        0 // Tetramino com cor única
                    );

                    // Verifica Game Ove
                    if (check_collision(&current)) {
                        running = 0; // Game Over
                    }
                    break; // Sai do loop de 'steps', pois a peça foi fixada
                } else {
                    current = next_pos; // Movimento bem-sucedido
                }
            }

            if (running) { // Só desenha se o jogo ainda estiver rodando
                al_draw_bitmap(background, 0, 0, 0);

                // Desenha blocos fixos no campo
                for (int y_field = 0; y_field < FIELD_HEIGHT; y_field++) {
                    for (int x_field = 0; x_field < FIELD_WIDTH; x_field++) {
                        if (field[y_field][x_field] != 0) {
                            al_draw_filled_rectangle(
                                x_field * BLOCK_SIZE, y_field * BLOCK_SIZE,
                                x_field * BLOCK_SIZE + BLOCK_SIZE, y_field * BLOCK_SIZE + BLOCK_SIZE,
                                color_map(field[y_field][x_field])
                            );
                        }
                    }
                }

                // Desenha tetromino atual
                for (int i = 0; i < 4; i++) {
                    Block b = current.blocks[i];
                    al_draw_filled_rectangle(
                        b.x * BLOCK_SIZE, b.y * BLOCK_SIZE,
                        b.x * BLOCK_SIZE + BLOCK_SIZE, b.y * BLOCK_SIZE + BLOCK_SIZE,
                        color_map(b.color)
                    );
                }

                char tempo_str[16];
                snprintf(tempo_str, sizeof(tempo_str), "%02d:%02d", cronometro.minutos, cronometro.segundos);

                int text_width = al_get_text_width(font, tempo_str);
                int text_height = al_get_font_line_height(font);

                al_draw_text(font, al_map_rgb(255, 255, 255), 10, SCREEN_HEIGHT - text_height - 10, 0, tempo_str);
                desenhar_placar();

                al_flip_display();
            }
        } else if (ev.type == ALLEGRO_EVENT_TIMER && ev.timer.source == cronometro.timer) {
            atualizar_cronometro(&cronometro);
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(background);
    al_destroy_display(display);
    destruir_cronometro(&cronometro);
    return true;
}
