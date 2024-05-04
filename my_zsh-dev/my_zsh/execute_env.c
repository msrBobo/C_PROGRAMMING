#include "liber_and_function.h"
void execute_env(char **args)
{
    var.index = 0;
    while (args[var.index] != NULL)
    {
        printf("%s\n", args[var.index]);
        var.index++;
    }
}