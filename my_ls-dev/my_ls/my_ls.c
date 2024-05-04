#include "my_ls.h"

size_t StrLen(const char *str1)
{
    size_t l1 = 0;
    while (str1[l1] != '\0') l1 += 1;
    return l1;
}


char *CopyStr(char *str1, const char *str2)
{
    if (str1 == NULL) return NULL;
    char *ptr = str1;
    while (*str2 != '\0')
    {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
    return ptr;
}

char *StrCat(char *str1, const char *str2)
{
    size_t l1 = StrLen(str1);
    size_t ix;
    for (ix = 0; str2[ix] != '\0'; ix++)
    {
        str1[l1 + ix] = str2[ix];
    }
    str1[l1 + ix] = '\0';
    return str1;
}

void PathCat(char *str1, const char *dir, const char *name)
{
    StrCat(str1, dir);
    if (dir[StrLen(dir) - 1] != '/')
    {
        StrCat(str1, "/");
    }
    StrCat(str1, name);
}

int SortLexical(char *str1, char *str2)
{
    int len1 = StrLen(str1);
    int len2 = StrLen(str2);
    int maxL = len1 > len2 ? len2 : len1;

    for (int ix = 0; ix < maxL; ix++)
    {
        if (str1[ix] > str2[ix]) return 1;
        if (str1[ix] < str2[ix]) return 0;
    }
    return len1 > len2 ? 1 : 0;
}

int SortTime(filedata *str1, filedata *str2)
{
    if (str1->sec < str2->sec)
    {
        return 1;
    } else if (str1->sec == str2->sec)
    {
        if (str1->nsec < str2->nsec)
        {
            return 1;
        } else if (str1->nsec == str2->nsec)
        {
            return SortLexical(str1->name, str2->name);
        }
    }
    return 0;
}

void sortFileList(filedata *fileList, int listLen, int opt_t)
{
    int req_sort = 1;
    while (req_sort)
    {
        req_sort = 0;
        for (int rix = 0; rix < listLen - 1; rix++) 
        {
            if (
                    opt_t
                    ? SortTime(&fileList[rix], &fileList[rix + 1])
                    : SortLexical(fileList[rix].name, fileList[rix + 1].name)
                    ) {
                filedata temp = fileList[rix];
                fileList[rix] = fileList[rix + 1];
                fileList[rix + 1] = temp;
                req_sort = 1;
            }
        }
    }
}

void my_ls(char *dir, int opt_a, int opt_t)
{
    DIR *directory = opendir(dir);
    if (!directory) return;

    struct dirent *entry;
    struct stat fileStat;

    int listLen = 0;
    filedata *fileList = malloc(sizeof(filedata) * 100);

    while ((entry = readdir(directory)) != NULL)
    {
        if (!opt_a && entry->d_name[0] == '.') continue;

        filedata temp;
        CopyStr(temp.name, entry->d_name);

        if (opt_t)
        {
            char dname[1024] = "";
            PathCat(dname, dir, entry->d_name);

            int statRes = lstat(dname, &fileStat);
            if (statRes == 0)
            {
                temp.sec = fileStat.st_mtim.tv_sec;
                temp.nsec = fileStat.st_mtim.tv_nsec;
            }
        }

        fileList[listLen] = temp;
        listLen++;
    }

    closedir(directory);

    sortFileList(fileList, listLen, opt_t);


    for (int iv = 0; iv < listLen; iv++) 
    {
        printf("%s\n", fileList[iv].name);
    }

    free(fileList);
}

void SortDirs(char **dirs, int dirsLen)
{
    char temp[256] = "";
    int req_sort = 1;

    while (req_sort)
    {
        req_sort = 0;
        for (int rix = 0; rix < dirsLen - 1; rix++)
        {
            if (SortLexical(dirs[rix], dirs[rix + 1]))
            {
                CopyStr(temp, dirs[rix]);
                CopyStr(dirs[rix], dirs[rix + 1]);
                CopyStr(dirs[rix + 1], temp);
                req_sort = 1;
            }
        }
    }
}

int main(int argc, char **argv)
{
    int opt_a = 0, opt_t = 0;
    char *dirs[100];

    int numDir = 0;
    for(int ai = 1; ai < argc; ai++)
    {
        if(argv[ai][0] == '-')
        {
            int pos = 1;
            while(argv[ai][pos] != '\0')
            {
                if (argv[ai][pos] == 'a') opt_a = 1;
                if (argv[ai][pos] == 't') opt_t = 1;
                pos++;
            }
        } 
        else
        {
            dirs[numDir] = argv[ai];
            numDir++;
        }
    }

    //default no arguments
    if(numDir == 0)
    {
        my_ls(".", opt_a, opt_t);
        return 0;
    }

    SortDirs(dirs, numDir);
    
    for (int dii = 0; dii < numDir - 1; dii++)
    {
        printf("%s:\n", dirs[dii]);
        my_ls(dirs[dii], opt_a, opt_t);
        printf("\n");
    }

    if (numDir > 1)
    {
        printf("%s:\n", dirs[numDir - 1]);
    }

    my_ls(dirs[numDir - 1], opt_a, opt_t);

    return 0;
}