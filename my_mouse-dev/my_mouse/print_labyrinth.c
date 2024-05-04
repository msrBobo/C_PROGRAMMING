#include "lib.h"

void print_labyrinth(Labyrinth *labyrinth) {
    if (!labyrinth) {
        return;
    }

    int distance = labyrinth->steps[labyrinth->exit.x][labyrinth->exit.y];
    Point pos = labyrinth->exit;

    while (distance > 1) {
        labyrinth->labyrinth[pos.x][pos.y] = 'o';
        distance--;

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int x = pos.x + dx[i];
            int y = pos.y + dy[i];

            if (is_valid_point(labyrinth, x, y) && labyrinth->steps[x][y] == distance) {
                pos = (Point){x, y};
                break;
            }
        }
    }

    labyrinth->labyrinth[labyrinth->entrance.x][labyrinth->entrance.y] = '1';
    labyrinth->labyrinth[labyrinth->exit.x][labyrinth->exit.y] = '2';

    printf("%dx%d* o12\n", labyrinth->rows, labyrinth->cols);

    for (int i = 0; i < labyrinth->rows; i++) {
        for (int j = 0; j < labyrinth->cols; j++) {
            printf("%c", labyrinth->labyrinth[i][j]);
        }
        printf("\n");
    }

    printf("%d STEPS!\n", calculate_steps(labyrinth));
}