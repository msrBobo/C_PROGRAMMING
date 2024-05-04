CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = my_curl.h my_curl.c mainly_funcs.c find_system.c func_curl.c 
OUT = my_curl

.PHONY: all clean fclean re

run:
	$(CC) $(CFLAGS) -o $(OUT)  $(SRC)

fclean:
	rm -f $(OUT) *.o

re: fclean all