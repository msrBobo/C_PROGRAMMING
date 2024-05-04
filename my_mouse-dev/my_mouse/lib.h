#ifndef LIB_H
#define LIB_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#define MAX_SIZE 1000

typedef struct {
    int x, y;
} Point;

typedef struct {
    char **labyrinth;
    int **steps;
    Point entrance;
    Point exit;
    int rows;
    int cols;
} Labyrinth;

Labyrinth *init_labyrinth(char *filename);
void free_labyrinth(Labyrinth *labyrinth);
int is_valid_point(Labyrinth *labyrinth, int x, int y);
void print_error();
int calculate_steps(Labyrinth *labyrinth);
Point find_nearest_exit(Labyrinth *labyrinth);
void find_shortest_path(Labyrinth *labyrinth);
void print_labyrinth(Labyrinth *labyrinth);

#endif // LIB_H
