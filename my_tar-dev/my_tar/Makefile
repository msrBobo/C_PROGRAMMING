TARGET := my_tar
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
CFLAGS := -Wall -Wextra -Werror #-g3 -fsanitize=address

all : $(TARGET) $(OBJ)

$(TARGET) : $(OBJ)
		gcc $(CFLAGS) -o $(TARGET) $(OBJ)
$(OBJ) : $(SRC)
		gcc $(CFLAGS) -c $(SRC)

clean:
		rm -f *.o

fclean: clean
		rm -f $(TARGET)

re: fclean all
