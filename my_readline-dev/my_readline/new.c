#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define max_read 40

int main()
{
    int i=0;
    int fd;
    char* buff;
    char path[] = "baaxa.txt";
    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }
    buff = malloc(max_read);
    if (buff == NULL) {
        perror("malloc");
        exit(1);
    }
    while (i < max_read && read(fd, buff, max_read) > EOF) {
        // do something with the data in buff
        i += max_read;
        printf("%s",buff);
    }
    free(buff);
    close(fd);
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define BUFFER_SIZE 10

// char* read_line(FILE* file) {
//     char* line = NULL;
//     size_t line_len = 0;
//     ssize_t bytes_read;

    
//     char buffer[BUFFER_SIZE];

 
//     while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
//         char* newline_pos = strchr(buffer, '\n');
//         if (newline_pos != NULL) {
      
//             size_t prefix_len = newline_pos - buffer;
//             line = (char*) realloc(line, line_len + prefix_len + 1);
//             memcpy(line + line_len, buffer, prefix_len);
//             line[line_len + prefix_len] = '\0';
            
//             fseek(file, prefix_len - bytes_read + 1, SEEK_CUR);
//             return line;
//         }
//         else {
//             line = (char*) realloc(line, line_len + bytes_read + 1);
//             memcpy(line + line_len, buffer, bytes_read);
//             line_len += bytes_read;
//             line[line_len] = '\0';
//         }
//     }

//     if (line != NULL && line_len > 0) {
//         return line;
//     }
//     else {
//         return NULL;
//     }
// }

// int main() {
//     FILE* file = fopen("baaxa.txt", "r");
//     if (file == NULL) {
//         printf("Error opening file.\n");
//         return 1;
//     }

//     char* line = read_line(file);
//     while (line != NULL) {
//         printf("%s\n", line);
//         free(line);
//         line = read_line(file);
//     }

//     fclose(file);
//     return 0;
// }


// #include <stdio.h>
// #include <fcntl.h>
// #include <string.h>
// #include <unistd.h>
// #include <stdlib.h>

// int READLINE_READ_SIZE = 50;
// char *storage = NULL;
// int storage_size = 0;
// int storage_offset = 0;

// void init_my_readline() {
//     if (storage != NULL) {
//         free(storage);
//     }
//     storage_size = READLINE_READ_SIZE;
//     storage = malloc(storage_size * sizeof(char));
//     storage_offset = 0;
// }

// char *my_readline(int fd) {
//     char c = 0;
//     if (storage == NULL) {
//         init_my_readline();
//     }

//     while (read(fd, &c, 1) > 0) {
//         if (storage_offset >= storage_size) {
//             storage_size += READLINE_READ_SIZE;
//             char *temp = realloc(storage, storage_size * sizeof(char));
//             if (temp == NULL) {
//                 return NULL;
//             }
//             storage = temp;
//         }
//         storage[storage_offset++] = c;

//         if (c == '\n') {
//             char *line = malloc((storage_offset + 1) * sizeof(char));
//             memcpy(line, storage, storage_offset);
//             line[storage_offset] = '\0';
//             memmove(storage, storage + storage_offset, storage_size - storage_offset);
//             storage_offset = 0;
//             return line;
//         }
//     }

//     if (storage_offset == 0) {
//         return NULL;
//     }

//     char *line = malloc((storage_offset + 1) * sizeof(char));
//     memcpy(line, storage, storage_offset);
//     line[storage_offset] = '\0';
//     storage_offset = 0;

//     return line;
// }

// int main(int ac, char **av)
// {
//   char *str = NULL;

//   int fd = open("./baaxa.txt", O_RDONLY);
//   while ((str = my_readline(fd)) != NULL)
//   {
//       printf("%s\n", str);
//       free(str);
//   }
//   close(fd);
  
//   return 0;
// }
