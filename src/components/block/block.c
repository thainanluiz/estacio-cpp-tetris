#include "components/block/block.h"

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

Tetromino create_tetromino(TetrominoType type, int x, int y, int color) {
    Tetromino t;
    t.type = type;
    for (int i = 0; i < 4; i++) {
        t.blocks[i].x = x + tetromino_offsets[type][i][0];
        t.blocks[i].y = y + tetromino_offsets[type][i][1];
        t.blocks[i].color = color;
    }
    return t;
}