CFLAGS = -Wall -Wextra -Werror

SRC = main.c init_labyrinth.c free_labyrinth.c is_valid_point.c print_error.c \
calculate_steps.c find_nearest_exit.c find_shortest_path.c print_labyrinth.c

OUT = my_mouse

my_mouse: $(SRC)
	gcc $(CFLAGS) -o $(OUT) $(SRC)

fclean:
	rm -f $(OUT) *.o
