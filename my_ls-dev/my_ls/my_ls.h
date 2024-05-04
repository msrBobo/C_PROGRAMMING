#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h> //Used for handling directory files
#include <sys/stat.h>
#include <errno.h> //defines the integer variable errno, used to indicate what went wrong

typedef struct Filedata
{   
    char name[255];
    long sec;
    long nsec;
}filedata;

void my_ls(char *dir, int opt_a, int opt_t);
char *CopyStr(char *str1, const char *str2);
char *StrCat(char *str1, const char *str2);
size_t StrLen(const char *str1);
void PathCat(char *str1, const char *dir, const char *name);
int SortLexical(char *str1, char *str2);
int SortTime(filedata *str1, filedata *str2);
void sortFileList(filedata *fileList, int listLen, int opt_t);
void sortDirs(char **dirs, int dirsLen);
int main(int argc, char **argv);

