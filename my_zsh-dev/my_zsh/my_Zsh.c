#include "liber_and_function.h"

int main(int argc, char **argv, char **envp)
{
    coman.unsetenv="unsetenv";
    coman.pwd="pwd";
    coman.cd="cd";
    coman.echo="echo";
    coman.exit="exit";
    coman.setenv="setenv";
    coman.env="env";

    var.should_run=1;
    (void)argc;
    (void)argv;
    while (var.should_run)
    {
        fflush(stdout);
        if (fgets(var.line, sizeof(var.line), stdin) == NULL)
        {
            break;
        }
        if (var.line[strlen(var.line) - 1] == '\n')
        {
            var.line[strlen(var.line) - 1] = '\0';
        }
         var.token = strtok(var.line, " ");
         var.index= 0;
        while ( var.token != NULL && var.index < MAX_ARGS) {
            var.args[var.index++] =  var.token;
             var.token = strtok(NULL, " ");
        }
       var.args[var.index] = NULL;
        if (var.args[0] == NULL) {
        } else if (strcmp(var.args[0],coman.cd) == 0) {
            execute_cd(var.args);
        } else if (strcmp(var.args[0],coman.echo) == 0) {
            execute_echo(var.args);
        } else if (strcmp(var.args[0], coman.exit) == 0) {
            execute_exit(var.args);
            var.should_run = 0;
        } else if (strcmp(var.args[0], coman.setenv) == 0) {
            execute_setenv(var.args);
        }else if (strcmp(var.args[0], coman.pwd) == 0) {
            execute_pwd(var.args);
        }else if (strcmp(var.args[0], coman.unsetenv) == 0) {
            execute_unsetenv(var.args);
        }else if (strcmp(var.args[0], coman.env) == 0) {
            execute_env(envp);
        } else {
             var.command = find_executable(var.args[0]);
            if ( var.command == NULL)
            {
                puts("Segmentation fault\n");
            } else {
                execute_executable( var.command, var.args,envp);
            }
        }
    }

    return 0;
}