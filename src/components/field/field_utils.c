#include "constants/allegro_constants.h" 
#include "components/field/field_utils.h"

extern int field[FIELD_HEIGHT][FIELD_WIDTH];

void clear_field(void) {
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            field[y][x] = 0;
        }
    }
}