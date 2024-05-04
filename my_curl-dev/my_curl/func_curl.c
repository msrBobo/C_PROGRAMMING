#include "my_curl.h"
#define NUM 300
typedef struct
{
    char* url;
    char* way;
    char* name_of_host;
}
Request;

void *my_memset(void *ptr, int value, size_t num)
{
    unsigned char *p = ptr;
    while (num-- > 0)
        *p++ = (unsigned char)value;
    return ptr;
}
int my_close(int fd)
{
    int ret = 0;
    if (fd >= 0)
    {
        ret = close(fd);
    }
    return ret;
}

int mainly_func(int p1, char** p2)
{
    int fil_d;
    if (p1 < 2)
    {
        fprintf(stderr, "Error: Missing URL argument\n");
        exit(1);
    }
    Request request;
    request.url = strdup(p2[1]);
    request.name_of_host = scan_path_prot(strdup(request.url), 1);
    request.way = scan_path_prot(strdup(request.url), 0);
    if ((fil_d = lan_to_name(request.name_of_host)))
    {
        my_memset(BUFF, 0, NUM);
        sprintf(BUFF, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", request.way, request.name_of_host);
        result_code(BUFF,fil_d);
    
        my_close(fil_d);
    }
    return 0;
}