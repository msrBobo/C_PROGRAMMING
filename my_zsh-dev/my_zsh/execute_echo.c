#include "liber_and_function.h"

void execute_echo(char **args)
{
    var.index = 1;
    while (args[var.index] != NULL)
    {
        printf("%s ", args[var.index++]);
    }
    printf("\n");
}