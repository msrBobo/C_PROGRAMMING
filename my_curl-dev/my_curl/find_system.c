#include "my_curl.h"
#define NUM 10
#define NUM1 300
#define NUM2 500
#define SOCKET_TIMEOUT NUM

struct total
{
    struct hostent *url;
    struct sockaddr_in ad_res;
};

#if linux || APPLE
int len_z = 1;
#elif _WIN64
int time_len = SOCKET_TIMEOUT * NUM1;

    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

#endif

void sys_scan(int num_f, int num_g)
{
    int time_len1;
    struct timeval time_co;
    if (num_f == 1)
    {
        time_co.tv_sec = 1;
        time_co.tv_usec = 0;
        setsockopt(num_g, SOL_SOCKET, SO_RCVTIMEO, (char *)&time_co, sizeof(time_co));
    }
    else if (num_f == 2)
    {
        time_len1 = SOCKET_TIMEOUT * NUM2;
        setsockopt(num_g, SOL_SOCKET, SO_RCVTIMEO, (char *)&time_len1, sizeof(time_len1));
    }
}

bool scan_str(char *str, char *str2)
{
    for (int i = 0; str2[i] != 0; i++)
    {
        if (str[i] != str2[i])
            return false;
    }
    return true;
}

int lan_to_name(char *name_url)
{
    struct total total;
    int num_d;
    int of_port;
    if ((num_d = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket failure");
        return -1;
    }
    if ((total.url = gethostbyname(name_url)) == NULL)
    {
        fprintf(stderr, "could not resolve host: %s\n", name_url);
        return -1;
    }
    total.ad_res.sin_family = AF_INET;

    total.ad_res.sin_addr = *((struct in_addr *)total.url->h_addr);
    
    of_port = 80;
    total.ad_res.sin_port = ntohs(of_port);
    memset(&total.ad_res.sin_zero, '\0', sizeof(total.ad_res.sin_zero));
    sys_scan(len_z, num_d);
    if (connect(num_d, (struct sockaddr *)&total.ad_res, sizeof(struct sockaddr)) == -1)
    {
        perror("cannot connect with link\n");
        return -1;
    }
    return num_d;
}