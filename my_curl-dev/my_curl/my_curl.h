#ifndef CURL_LIB_H
#define CURL_LIB_H

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#endif


#ifndef BUF_s
#define BUF_s

#define size_buf 3000
char BUFF[size_buf];
#endif


#ifndef CURL_FUNC
#define CURL_FUNC
struct var_func
{
    int num;
    char* str;
}
var;

bool scan_str(char* src, char* sub);
int result_code(const char *buffer,int socked_fd);
char *scan_path_prot(char *link,int num);
void sys_scan(int fl, int fd);
int lan_to_name(char *local_name);
int mainly_func(int ac, char** av);

#endif

