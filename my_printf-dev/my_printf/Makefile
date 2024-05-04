CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: my_printf

my_printf: my_printf.c
    $(CC) $(CFLAGS) -o $@ $^

clean:
    rm -f my_printf

fclean: clean