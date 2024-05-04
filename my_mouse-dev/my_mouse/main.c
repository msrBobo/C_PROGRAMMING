#include "lib.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_error();
        return 1;
    }
    if (access(argv[1], F_OK) != 0) {
        print_error();
        return 1;
    }
    Labyrinth *labyrinth = init_labyrinth(argv[1]);
    if (!labyrinth) {
        print_error();
        return 1;
    }
    find_shortest_path(labyrinth);
    print_labyrinth(labyrinth);
    free_labyrinth(labyrinth);

    return 0;
}
