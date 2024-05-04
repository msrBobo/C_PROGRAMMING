#include "liber_and_function.h"
void execute_unsetenv(char **args)
{
    if (args[1] == NULL)
    {
        printf("Usage: unsetenv VAR\n");
    } 
    else
    {
        if (unsetenv(args[1]) != 0)
        {
            perror("unsetenv");
        }
    }
}