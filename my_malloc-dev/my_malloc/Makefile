MY_OBJS = my_malloc.o
MY_CFILES = $(MY_OBJS:.o=.c)
MY_HEADERFILES = $(MY_OBJS:.o=.h)

CC = gcc
CFLAGS =
TARGET = test

all: $(MY_LIBNAME) $(TARGET)

$(TARGET): $(TARGET).c  $(MY_OBJS)
	$(CC) -o $(TARGET) $(TARGET).c $(MY_OBJS)

$(TARGET).o: $(TARGET).c $(MY_HEADERFILES)
	$(CC) -c $(TARGET).c

$(MY_OBJS) : $(MY_CFILES) $(MY_HEADERFILES)
	$(CC) -c $(MY_CFILES)

clean:
	rm -f *.o
	rm -f $(TARGET)