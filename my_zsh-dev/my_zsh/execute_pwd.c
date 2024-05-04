#include "liber_and_function.h"

void execute_pwd(char** args)
{
    char current_dir[PATH_MAX];

    if (args[1] != NULL)
    {
        printf("pwd: too many arguments\n");
        return;
    }
    if (getcwd(current_dir, PATH_MAX) == NULL)
    {
        perror("getcwd() error");
        return;
    }

    printf("%s\n", current_dir);
}