#include "lib.h"

int calculate_steps(Labyrinth *labyrinth) {
    int total_steps = labyrinth->steps[labyrinth->exit.x][labyrinth->exit.y] - 3;
    if (total_steps % 2 != 0) {
        total_steps++;
    } else {
        total_steps += 1;
    }
    return total_steps;
}