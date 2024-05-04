#include "lib.h"

int is_valid_point(Labyrinth *labyrinth, int x, int y) {
    if (labyrinth) {
        return x >= 0 && x < labyrinth->rows && y >= 0 && y < labyrinth->cols;
    }
    return 0;
}