#include "liber_and_function.h"
void execute_exit(char** args)
{
    if (args[1] != NULL)
    {
        var.index = atoi(args[1]);
        exit(var.index);
    }
    else
    {
        exit(0);
    }
}