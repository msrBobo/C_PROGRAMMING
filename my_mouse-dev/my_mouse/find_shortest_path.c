#include "lib.h"

void find_shortest_path(Labyrinth *labyrinth) {
    if (!labyrinth) {
        return;
    }

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    labyrinth->steps[labyrinth->entrance.x][labyrinth->entrance.y] = 1;

    Point queue[MAX_SIZE * MAX_SIZE];
    int front = 0, rear = 0;

    queue[rear++] = labyrinth->entrance;

    while (front < rear) {
        Point pos = queue[front++];

        for (int i = 0; i < 4; i++) {
            int x = pos.x + dx[i];
            int y = pos.y + dy[i];

            if (is_valid_point(labyrinth, x, y) && labyrinth->labyrinth[x][y] != '*' && labyrinth->steps[x][y] > labyrinth->steps[pos.x][pos.y] + 1) {
                labyrinth->steps[x][y] = labyrinth->steps[pos.x][pos.y] + 1;
                queue[rear++] = (Point){x, y};

                if (labyrinth->labyrinth[x][y] == '2' && (labyrinth->steps[labyrinth->exit.x][labyrinth->exit.y] == MAX_SIZE || labyrinth->steps[x][y] < labyrinth->steps[labyrinth->exit.x][labyrinth->exit.y])) {
                    labyrinth->exit = (Point){x, y};
                }
            }
        }
    }
}