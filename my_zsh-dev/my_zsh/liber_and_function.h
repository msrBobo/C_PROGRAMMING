#ifndef zsh_header_lib
#define zsh_header_lib

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>
#include <limits.h>
#include <libgen.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#endif

#define MAX_LINE 80
#define MAX_ARGS 10
#define PATH_MAX 4096

#ifndef varbs_func
#define varbs_func

 struct varbs
 {
    int should_run;
    int index;
    char *args[MAX_ARGS + 1];
    char line[MAX_LINE + 1];
    char *command;
    char *token;
    char *path;
    char *end;
    char *dir;
    char *fullpath;
    }
var;

struct command
{
    char *comands;
    char *env;
    char *setenv;
    char *exit;
    char *echo;
    char *cd;
    char *unsetenv;
    char *pwd;
}
coman;
#endif

#ifndef function_void
#define function_void
void execute_which(char **args);
void execute_pwd(char **args);
void execute_env(char **args);
void execute_cd(char **args);
void execute_echo(char **args);
void execute_exit(char **args);
void execute_executable(char *command, char **args, char **envp);
char *find_executable(char *command);
void execute_setenv(char **args);
void execute_unsetenv(char **args);
#endif