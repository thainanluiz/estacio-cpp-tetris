#ifndef BLOCK_H
#define BLOCK_H

typedef struct
{
    int x, y;
    int color;
} Block;

typedef enum
{
    TETROMINO_I,
    TETROMINO_O,
    TETROMINO_T,
    TETROMINO_S,
    TETROMINO_Z,
    TETROMINO_J,
    TETROMINO_L,
    TETROMINO_COUNT
} TetrominoType;

typedef struct
{
    Block blocks[4];
    TetrominoType type;
} Tetromino;

Tetromino create_tetromino(TetrominoType type, int x, int y, int color, int random_colors);
void rotate_tetromino(Tetromino *tet, int direction, int pivot_x, int pivot_y);

#endif