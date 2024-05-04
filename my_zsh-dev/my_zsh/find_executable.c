// #include "liber_and_function.h"
// char *find_executable(char *command)
// {
//     var.path = getenv("PATH");
//     size_t pathlen, cmdlen;
//     struct stat statbuf;

//     if (var.path == NULL)
//     {
//         return NULL;
//     }

//     pathlen = strlen(var.path);
//     cmdlen = strlen(command);
//     var.fullpath = malloc(pathlen + cmdlen + 2);
//     if (var.fullpath == NULL)
//     {
//         return NULL;
//     }
//     char n = '\0';
//     var.dir = var.path;
//     while (var.dir != &n)
//     {
//         char *end = strchr(var.dir, ':');
//         if (end == NULL)
//         {
//             end = var.dir + strlen(var.dir);
//         }
//         strncpy(var.fullpath, var.dir, end - var.dir);
//         var.fullpath[end - var.dir] = '/';
//         strcpy(var.fullpath + (end - var.dir) + 1, command);

//         if (stat(var.fullpath, &statbuf) == 0 && S_ISREG(statbuf.st_mode) &&
//             (statbuf.st_mode & S_IXUSR || statbuf.st_mode & S_IXGRP ||
//              statbuf.st_mode & S_IXOTH))
//             {
//             return var.fullpath;
//         }
//         var.dir = (*end == ':') ? end + 1 : end;
//     }
//     free(var.fullpath);
//     return NULL;
// }
#include "liber_and_function.h"
char *find_executable(char *command)
{
    char *path = getenv("PATH");
    char *dir, *fullpath;
    size_t pathlen, cmdlen;
    struct stat statbuf;

    if (path == NULL)
    {
        return NULL;
    }

    pathlen = strlen(path);
    cmdlen = strlen(command);
    fullpath = malloc(pathlen + cmdlen + 2);
    if (fullpath == NULL)
    {
        return NULL;
    }

    dir = path;
    while (*dir != '\0')
    {
        char *end = strchr(dir, ':');
        if (end == NULL) 
        {
            end = dir + strlen(dir);
        }
        strncpy(fullpath, dir, end - dir);
        fullpath[end - dir] = '/';
        strcpy(fullpath + (end - dir) + 1, command);

        if (stat(fullpath, &statbuf) == 0 && S_ISREG(statbuf.st_mode) &&
            (statbuf.st_mode & S_IXUSR || statbuf.st_mode & S_IXGRP ||
             statbuf.st_mode & S_IXOTH))
            {
            return fullpath;
        }
        dir = (*end == ':') ? end + 1 : end;
    }
    free(fullpath);
    return NULL;
}
