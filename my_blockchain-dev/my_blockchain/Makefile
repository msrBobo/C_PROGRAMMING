CC = gcc
CFLAGC = -Wall -Wextra -Werror 
SOURCES = my_blockchain.c 
TARGET = my_blockchain

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGC) -o $@ $^

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all

