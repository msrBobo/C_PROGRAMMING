#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int READLINE_READ_SIZE = 512;
char *storage = NULL;

void init_my_readline() {
    if (storage != NULL) {
        free(storage);
    }
    storage = malloc(READLINE_READ_SIZE * sizeof(char));
}

char *my_readline(int fd) {
    
    int i = 0;
    char c = 0;

    if (storage == NULL) {
        init_my_readline();
    }

    while (read(fd, &c, 1) > 0 && c != '\n') {
        if (i == READLINE_READ_SIZE) {
            READLINE_READ_SIZE *= 2;
            char *temp = realloc(storage, READLINE_READ_SIZE * sizeof(char));
            if (temp == NULL) {
                return NULL;
            }
            storage = temp;
        }
        storage[i++] = c;
    }

    if (i == 0 && c == 0) {
        return NULL;
    }

    char *line = malloc((i + 1) * sizeof(char));
    for (int j = 0; j < i; j++) {
        line[j] = storage[j];
    }
    line[i] = 0;

    return line;
}
int main(int ac, char **av) {
    char *str = NULL;
    int fd = open("./file.txt", O_RDONLY);
    while ((str = my_readline(fd)) != NULL) {
        printf("%s\n", str);
        free(str);
    }
    close(fd);
    return 0;
}
