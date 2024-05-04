#include "liber_and_function.h"

void execute_setenv(char **args)
{
    if (args[1] == NULL || args[2] == NULL)
    {
        printf("Usage: setenv VAR VALUE\n");
    }
    else
    {
        if (setenv(args[1], args[2], 1) != 0)
        {
            perror("setenv");
        }
    }
}