#include "lib.h"

Labyrinth *init_labyrinth(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    Labyrinth *labyrinth = (Labyrinth *)malloc(sizeof(Labyrinth));
    if (!labyrinth) {
        fclose(file);
        return NULL;
    }

    fscanf(file, "%dx%d* o12", &labyrinth->rows, &labyrinth->cols);

    labyrinth->labyrinth = (char **)malloc(labyrinth->rows * sizeof(char *));
    labyrinth->steps = (int **)malloc(labyrinth->rows * sizeof(int *));

    if (!labyrinth->labyrinth || !labyrinth->steps) {
        fclose(file);
        free_labyrinth(labyrinth);
        return NULL;
    }

    for (int i = 0; i < labyrinth->rows; i++) {
        labyrinth->labyrinth[i] = (char *)malloc(labyrinth->cols * sizeof(char));
        labyrinth->steps[i] = (int *)malloc(labyrinth->cols * sizeof(int));
        if (!labyrinth->labyrinth[i] || !labyrinth->steps[i]) {
            fclose(file);
            free_labyrinth(labyrinth);
            return NULL;
        }
    }

    bool entrance_found = false, exit_found = false;
    char ch;

    for (int i = 0; i < labyrinth->rows; i++) {
        for (int j = 0; j < labyrinth->cols; j++) {
            ch = fgetc(file);
            while (ch == '\n' || ch == '\r') {
                ch = fgetc(file);
            }
            labyrinth->labyrinth[i][j] = ch;
            labyrinth->steps[i][j] = MAX_SIZE;

            if (labyrinth->labyrinth[i][j] == '1') {
                labyrinth->entrance = (Point){i, j};
                entrance_found = true;
            } else if (labyrinth->labyrinth[i][j] == '2') {
                exit_found = true;
            }
        }   
        ch = fgetc(file); 
    }

    fclose(file);

    Point nearest_exit = find_nearest_exit(labyrinth);
    labyrinth->exit = nearest_exit;

    if (!entrance_found || !exit_found || labyrinth->rows > MAX_SIZE || labyrinth->cols > MAX_SIZE) {
        free_labyrinth(labyrinth);
        return NULL;
    }

    return labyrinth;
}