#ifndef MY_LIBASM_H
#define MY_LIBASM_H
#pragma once
#include <unistd.h>

size_t my_strlen(const char *str);
char* my_strchr(const char *str, int c);
void* my_memset(void* ptr, int value, size_t num);
void* my_memcpy(void *dest, const void *src, size_t count);
int my_strcmp(const char *string1, const char *string2);
void* my_memmove(void* dest, const void* source, size_t num);
int my_strncmp(const char* str1, const char* str2, size_t n);
int my_strcasecmp(const char *s1, const char *s2);
char* my_index(const char *s, int c);
ssize_t my_read(int fd, void *buf, size_t nbytes);
ssize_t my_write(int fd, const void *buf, size_t nbytes);

#endif  // MY_LIBASM_H