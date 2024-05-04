#include "liber_and_function.h"
void execute_executable(char* command, char** args, char** envp)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        if (execve(command, args, envp) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
    }
        else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}