#include "liber_and_function.h"

void execute_which(char** args)
{
    var.command = args[0];
    var.path = getenv("PATH");
    size_t pathlen, cmdlen;
     struct stat statbuf;
    
    if (var.path == NULL)
    {
        printf("which: PATH environment variable not set\n");
        return;
    }

    pathlen = strlen(var.path);
    cmdlen = strlen(var.command);
    var.fullpath = malloc(pathlen + cmdlen + 2);
    if (var.fullpath == NULL)
    {
        perror("malloc");
        return;
    }
    char n = '\0';
    var.dir = var.path;
    while (var.dir != &n)
    {
        var.end = strchr(var.dir, ':');
        if (var.end == NULL)
        {
            var.end = var.dir + strlen(var.dir);
        }
        strncpy(var.fullpath, var.dir, var.end - var.dir);
        var.fullpath[var.end - var.dir] = '/';
        strcpy(var.fullpath + (var.end - var.dir) + 1, var.command);
        if (stat(var.fullpath, &statbuf) == 0 && S_ISREG(statbuf.st_mode) &&
            (statbuf.st_mode & S_IXUSR || statbuf.st_mode & S_IXGRP ||
             statbuf.st_mode & S_IXOTH))
            {
            printf("%s\n", var.fullpath);
            free(var.fullpath);
            return;
        }
        char k = ':';
        var.dir = (var.end == &k) ? var.end + 1 : var.end;
    }
    printf("%s: command not found\n", var.command);
    free(var.fullpath);
}