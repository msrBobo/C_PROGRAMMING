#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "my_libasm.h"

int main(void)
{
    char *a = "qwasar";
    char *b = "qwasarquest";
    unsigned char c[] = {0,0,0,0};

    //Replace 0 with 1 to test:

#if 0
    printf("my_strlen()====================\n");

    printf("%ld\n", my_strlen(a));
    printf("%ld\n", my_strlen(b));
#endif

#if 0
    printf("my_strchr()====================\n");
    {
       char *a = "aaa";
       char *b = "aaabbbccc";
       unsigned char c[] = {0,0,0,0};

       printf("%p - %p\n", a, my_strchr(a, 'b'));
       printf("%p - %p\n", a, my_strchr(a, 'a'));
       printf("%p - %p\n", b, my_strchr(b, 'a'));
       printf("%p - %p\n", b, my_strchr(b, 'b'));
       printf("%p - %p\n", b, my_strchr(b, 'c'));
       printf("%p - %p\n", b, my_strchr(b, 'd'));
    }

#endif

#if 0
    printf("my_memset()====================\n");

    void *ret_my_memset = my_memset(c, 1, sizeof(c));
    printf("ret_my_memset = %p(%p)\n", ret_my_memset, c);
    for(int i = 0; i < sizeof(c)/sizeof(c[0]); ++i) {
        printf("%d - %d : ", i, c[i]);
    }
    printf("\n");
    my_memset(c, 255, sizeof(c));
    for(int i = 0; i < sizeof(c)/sizeof(c[0]); ++i) {
        printf("%d - %d : ", i, c[i]);
    }
    printf("\n");
#endif

#if 0

char source[] = "Qwasar project!";

    char destination[20];
    my_memcpy(destination, source, sizeof(source));
    printf("Copied string: %s\n", destination);

#endif
 
 #if 0
     printf("my_strcmp()====================\n");
     {
         char *s1 = "abc";
         char *s2 = "abc";
         char *s3 = "abcd";
         char *s4 = "abcc";
         char *s5 = "abcce";
         char *s6 = "ab";

         printf("%d %d %d %d %d %d\n", strcmp(s1, s2), strcmp(s2, s3), strcmp(s3, s4), strcmp(s3, s5), strcmp(s4, s5), strcmp(s1, s6));
         printf("%d %d %d %d %d %d\n", my_strcmp(s1, s2), my_strcmp(s2, s3), my_strcmp(s3, s4), my_strcmp(s3, s5), my_strcmp(s4, s5), my_strcmp(s1, s6));
     }
#endif

#if 0

    printf("my_memmove()====================\n");

    char str[20] = "Hello, World!";
    printf("%s\n", b);
    my_memmove(str + 7, b, 6);
    
    printf("After memmove: %s\n", str);
    
#endif

#if 0
    printf("my_strncmp()====================\n");
    {
          char *s1 = "abc";
         char *s2 = "abc";
         char *s3 = "abcd";
         char *s4 = "abcc";
         char *s5 = "abcce";
         char *s6 = "ab";

         printf("%d %d %d %d %d %d\n", strncmp(s1, s2, 100), strncmp(s2, s3, 100), strncmp(s3, s4, 100), strncmp(s3, s5, 100), strncmp(s4, s5, 100), strncmp(s1, s6, 100));
         printf("%d %d %d %d %d %d\n", my_strncmp(s1, s2, 100), my_strncmp(s2, s3, 100), my_strncmp(s3, s4, 100), my_strncmp(s3, s5, 100), my_strncmp(s4, s5, 100), my_strncmp(s1, s6, 100));
         printf("%d %d %d %d %d %d\n", strncmp(s1, s6, 2), strncmp(s2, s3, 3), strncmp(s3, s4, 3), strncmp(s3, s5, 100), strncmp(s4, s5, 3), strncmp(s1, s6, 0));
         printf("%d %d %d %d %d %d\n", my_strncmp(s1, s6, 2), my_strncmp(s2, s3, 3), my_strncmp(s3, s4, 3), my_strncmp(s3, s5, 100), my_strncmp(s4, s5, 3), my_strncmp(s1, s6, 0));
   }
#endif

#if 0
    printf("my_strcasecmp()====================\n");
    {
        char s1[] = "abc";
        char s2[] = "abc";
        char s3[] = "abcd";
        char s4[] = "abcc";
        char s5[] = "abcce";
        char s6[] = "ab";

        printf("%d %d %d %d %d %d\n", strcasecmp(s1, s2), strcasecmp(s2, s3), strcasecmp(s3, s4), strcasecmp(s3, s5), strcasecmp(s4, s5), strcasecmp(s1, s6));
        printf("%d %d %d %d %d %d\n\n", my_strcasecmp(s1, s2), my_strcasecmp(s2, s3), my_strcasecmp(s3, s4), my_strcasecmp(s3, s5), my_strcasecmp(s4, s5), my_strcasecmp(s1, s6));

        s1[0] = 'A';
        printf("%d %d %d %d %d %d\n", strcasecmp(s1, s2), strcasecmp(s2, s3), strcasecmp(s3, s4), strcasecmp(s3, s5), strcasecmp(s4, s5), strcasecmp(s1, s6));
        printf("%d %d %d %d %d %d\n\n", my_strcasecmp(s1, s2), my_strcasecmp(s2, s3), my_strcasecmp(s3, s4), my_strcasecmp(s3, s5), my_strcasecmp(s4, s5), my_strcasecmp(s1, s6));

        s1[1] = 'B';
        printf("%d %d %d %d %d %d\n", strcasecmp(s1, s2), strcasecmp(s2, s3), strcasecmp(s3, s4), strcasecmp(s3, s5), strcasecmp(s4, s5), strcasecmp(s1, s6));
        printf("%d %d %d %d %d %d\n\n", my_strcasecmp(s1, s2), my_strcasecmp(s2, s3), my_strcasecmp(s3, s4), my_strcasecmp(s3, s5), my_strcasecmp(s4, s5), my_strcasecmp(s1, s6));

        s1[2] = 'C';
        printf("%d %d %d %d %d %d\n", strcasecmp(s1, s2), strcasecmp(s2, s3), strcasecmp(s3, s4), strcasecmp(s3, s5), strcasecmp(s4, s5), strcasecmp(s1, s6));
        printf("%d %d %d %d %d %d\n\n", my_strcasecmp(s1, s2), my_strcasecmp(s2, s3), my_strcasecmp(s3, s4), my_strcasecmp(s3, s5), my_strcasecmp(s4, s5), my_strcasecmp(s1, s6));

        s1[2] = 'd';
        printf("%d %d %d %d %d %d\n", strcasecmp(s1, s2), strcasecmp(s2, s3), strcasecmp(s3, s4), strcasecmp(s3, s5), strcasecmp(s4, s5), strcasecmp(s1, s6));
        printf("%d %d %d %d %d %d\n\n", my_strcasecmp(s1, s2), my_strcasecmp(s2, s3), my_strcasecmp(s3, s4), my_strcasecmp(s3, s5), my_strcasecmp(s4, s5), my_strcasecmp(s1, s6));
   }
#endif

#if 0
    printf("my_index()====================\n");
     {
        char *a = "aaa";
        char *b = "aaabbbccc";
        unsigned char c[] = {0,0,0,0};

        printf("%p - %p\n", a, my_index(a, 'b'));
        printf("%p - %p\n", a, my_index(a, 'a'));
        printf("%p - %p\n", b, my_index(b, 'a'));
        printf("%p - %p\n", b, my_index(b, 'b'));
        printf("%p - %p\n", b, my_index(b, 'c'));
        printf("%p - %p\n", b, my_strchr(b, 'd'));
   }
#endif

#if 0
    printf("my_read()====================\n");
    {

#define RW_SIZE 10
        int fd;
        char buf[100];
        int size = RW_SIZE;
        ssize_t ret_read;
        ssize_t ret_write;

        fd = open("./sample.txt", O_RDWR);
        ret_read = my_read(fd, buf, size);
        printf("read 1 - %ld : %s\n", ret_read, buf);

        for(int i = 0; i < RW_SIZE; ++i) {
            buf[i]++;
        }

        lseek(fd, 0, SEEK_SET);

        ret_write = my_write(fd, buf, size);
        printf("write 1 - %ld : %s\n", ret_write, buf);

        lseek(fd, 0, SEEK_SET);

        ret_read = my_read(fd, buf, size);
        printf("read 2 - %ld : %s\n", ret_read, buf);

        for(int i = 0; i < RW_SIZE; ++i) {
            buf[i]--;
        }

        lseek(fd, 0, SEEK_SET);

        ret_write = my_write(fd, buf, size);
        printf("write 2 - %ld : %s\n", ret_write, buf);

        close(fd);
    }
#endif

}