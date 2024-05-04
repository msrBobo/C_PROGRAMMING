#include "my_curl.h"
#define high_size 1024
typedef struct
{
    char *res;
    char resp[256];
    int bytes_read;
    int content_len;
    int base;
} 
HttpResult;
int main(int argc, char** argv)
{

    if (argc > 2) exit(1);
    mainly_func(argc, argv);
    return 0;
}

size_t my_strlen(const char *s)
{
    size_t len = 0;
    while (*s++ != '\0') len++;
    return len;
}

char *my_strchr(const char *s, int c)
{
    while (*s != '\0' && *s != c) s++;
    return (*s == c) ? (char *)s : NULL;
}

int my_strncmp(const char *s1, const char *s2, size_t n)
{
    for (; n > 0 && *s1 == *s2; n--, s1++, s2++)
        if (*s1 == '\0' || n == 1) return 0;
    return (*s1 < *s2) ? -1 : 1;
}

char *my_strstr(const char *haystack, const char *needle)
{
    size_t len = my_strlen(needle);
    if (len == 0) return (char *)haystack;
    for (; (haystack = my_strchr(haystack, *needle)) != NULL; haystack++)
        if (my_strncmp(haystack, needle, len) == 0) return (char *)haystack;
    return NULL;
}

int result_code(const char *str,int num)
{
    HttpResult result = {0};
    result.res = (char *)malloc(high_size);
    send(num, str, my_strlen(str), 0);

    while ((result.bytes_read = recv(num, result.resp, sizeof(result.resp), 0)) > 0)
    {
        while (result.content_len < result.bytes_read) {
            result.res[result.content_len + result.base] = result.resp[result.content_len];
            result.content_len++;
        }
        result.base = result.content_len + result.base;
        result.res = realloc(result.res, result.base + high_size);
        result.content_len = 0;
    }

    char *pointer = my_strstr(result.res, "Content-Length:");
    if (pointer != NULL) {
        int n = atoi(pointer + 16);
        if (strcmp("200 OK", result.res + result.base - n) == 0)
        {
            fprintf(stdout, "Success");
        } else {
            fprintf(stdout, "%s", result.res + result.base - n);
        }
    }

    free(result.res);

    return 0;
}