#include "lib.h"

void free_labyrinth(Labyrinth *labyrinth) {
    if (labyrinth) {
        if (labyrinth->labyrinth) {
            for (int i = 0; i < labyrinth->rows; i++) {
                if (labyrinth->labyrinth[i]) {
                    free(labyrinth->labyrinth[i]);
                }
            }
            free(labyrinth->labyrinth);
        }

        if (labyrinth->steps) {
            for (int i = 0; i < labyrinth->rows; i++) {
                if (labyrinth->steps[i]) {
                    free(labyrinth->steps[i]);
                }
            }
            free(labyrinth->steps);
        }

        free(labyrinth);
    }
}