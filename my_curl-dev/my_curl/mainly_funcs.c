#include "my_curl.h"

#define size_st 8
#define size_st1 7
char *scan_path_prot(char *link,int num)
{

    char *st="https://";
    char *st1="http://";
    
    if (scan_str(link, st))  link += size_st;
    else if (scan_str(link, st1)) link += size_st1;
    for(int i=0; link[i]!=0; i++){
        if (num == 0 && link[i] == '/') return &link[i+1];
        else if (num == 1 && link[i] == '/') { link[i] = '\0'; break; }
    }
    return num == 0 ? "-1" : link;
}

