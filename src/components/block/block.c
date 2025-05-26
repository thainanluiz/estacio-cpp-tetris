#include "components/block/block.h"
#include <stdlib.h>

static const int tetromino_offsets[TETROMINO_COUNT][4][2] = {
    // I
    { {0,0}, {1,0}, {2,0}, {3,0} },
    // O
    { {0,0}, {1,0}, {0,1}, {1,1} },
    // T
    { {1,0}, {0,1}, {1,1}, {2,1} },
    // S
    { {1,0}, {2,0}, {0,1}, {1,1} },
    // Z
    { {0,0}, {1,0}, {1,1}, {2,1} },
    // J
    { {0,0}, {0,1}, {1,1}, {2,1} },
    // L
    { {2,0}, {0,1}, {1,1}, {2,1} }
};

Tetromino create_tetromino(TetrominoType type, int x, int y, int color, int random_colors) {
    Tetromino t;
    t.type = type;
    for (int i = 0; i < 4; i++) {
        t.blocks[i].x = x + tetromino_offsets[type][i][0];
        t.blocks[i].y = y + tetromino_offsets[type][i][1];
        if (random_colors)
            t.blocks[i].color = 1 + rand() % 7; // 1 a 7
        else
            t.blocks[i].color = color;
    }
    return t;
}

void rotate_tetromino(Tetromino *tet, int direction, int pivot_x, int pivot_y) {
    if (tet->type == TETROMINO_O) return;
    for (int i = 0; i < 4; i++) {
        int rel_x = tet->blocks[i].x - pivot_x;
        int rel_y = tet->blocks[i].y - pivot_y;
        int new_x, new_y;
        if (direction == 1) {
            new_x = -rel_y;
            new_y = rel_x;
        } else {
            new_x = rel_y;
            new_y = -rel_x;
        }
        tet->blocks[i].x = pivot_x + new_x;
        tet->blocks[i].y = pivot_y + new_y;
    }
}