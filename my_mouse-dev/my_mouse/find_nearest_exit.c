#include "lib.h"

Point find_nearest_exit(Labyrinth *labyrinth) {
    Point nearestExit = {-1, -1};

    if (!labyrinth) {
        return nearestExit;
    }

    int minDistance = MAX_SIZE;

    for (int i = 0; i < labyrinth->rows; i++) {
        for (int j = 0; j < labyrinth->cols; j++) {
            if (labyrinth->labyrinth[i][j] == '2') {
                int distance = abs(labyrinth->entrance.x - i) + abs(labyrinth->entrance.y - j);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestExit = (Point){i, j};
                }
            }
        }
    }

    return nearestExit;
}