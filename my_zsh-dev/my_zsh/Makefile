CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = my_Zsh.c execute_cd.c  execute_pwd.c  execute_echo.c execute_env.c execute_executable.c execute_exit.c execute_unsetenv.c execute_which.c find_executable.c execute_setenv.c
OUT = my_zsh

run:
	$(CC) $(CFLAGS) -o $(OUT)  $(SRC)

fclean:
	rm -f $(OUT) *.o