CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCE = my_readline.c
TARGET = my_readline

$(TARGET):$(SOURCE)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)