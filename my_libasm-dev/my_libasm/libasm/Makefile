AS = nasm
ASFLAGS = -felf64

MY_LIBNAME = my_libasm.a
MY_LIBOBJS = my_strlen.o my_strchr.o my_memset.o my_memcpy.o my_strcmp.o my_memmove.o my_strncmp.o  my_strcasecmp.o  my_index.o  my_read.o my_write.o
MY_LIBASMS = $(MY_LIBOBJS:.o=.c)

CC = gcc
CFLAGS =
TARGET = test

all: $(MY_LIBNAME) $(TARGET)

$(TARGET): $(TARGET).c  $(MY_LIBNAME)
	$(CC) -o $(TARGET) $(TARGET).c $(MY_LIBNAME)
	
$(TARGET).o: $(TARGET).c
	$(CC) -c $(TARGET).c

$(MY_LIBNAME) : $(MY_LIBOBJS)
	ar rc $(MY_LIBNAME) $(MY_LIBOBJS)

clean:
	rm -f *.o
	rm -f *.a
	rm -f $(TARGET)