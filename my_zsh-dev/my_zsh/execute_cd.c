#include "liber_and_function.h"

void execute_cd(char** args)
{
    var.index = 0;
    while (args[var.index] != NULL)
    {
        var.index++;
    }
    if (var.index > 2)
    {
        printf("cd: too many arguments\n");
        return;
    }
        var.path = args[1];
    if (var.path == NULL || strcmp(var.path, "") == 0)
    {
        var.path = getenv("HOME");
        if (var.path == NULL)
        {
            printf("cd: HOME not set\n");
            return;
        }
    }
    if (!strcmp(var.path, "-"))
    {
        var.path = getenv("OLDPWD");
        if (var.path == NULL)
        {
            printf("cd: OLDPWD not set\n");
            return;
        }
    }
    if (var.path[0] == '~')
    {
        char* username = var.path + 1;
        struct passwd* pw = getpwnam(username);
        if (pw == NULL)
        {
            printf("cd: no such user: %s\n", username);
            return;
        }
        var.path = pw->pw_dir;
    }
    if (chdir(var.path) == -1)
    {
        printf("cd: no such file or directory: %s\n", var.path);
        return;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", cwd, 1);
    }
    else
    {
        printf("cd: error getting current working directory\n");
        return;
    }
}
