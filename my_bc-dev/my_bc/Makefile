CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
SOURCES = my_Bc.c
TARGET = my_bc

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^
 
.PHONY: fclean

fclean:
	@rm -r $(TARGET)