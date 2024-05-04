#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "my_malloc.h"

char *src = "hello";
char *dest = NULL;

#define DEFTESTCASE(n) case n: testfun_##n(); break

#define PRINTARR(v, n) \
    printf(#v" = \n");\
    for(int i = 0; i < (n); ++i) {\
        printf("%d ", (v)[i]);\
    }\
    printf("\n");\

void testfun_0(void)
{
	printf("=====================================================\n");
	dest = my_malloc(strlen(src) + 1);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");

	dest = my_malloc(strlen(src) + 1);
    print_all_elems();
	printf("-----------------------------------\n");
}

void testfun_1(void)
{
	printf("=====================================================\n");
	char *dest1 = my_malloc(strlen(src) + 1);
    DBG_PRINT_PTR(dest1);
    print_all_elems();
	printf("-----------------------------------\n");

	my_free(dest1);
    DBG_PRINT_PTR(dest1);
    print_all_elems();
	printf("-----------------------------------\n");

	dest1 = my_malloc(strlen(src) + 1);
    DBG_PRINT_PTR(dest1);
    print_all_elems();
	printf("-----------------------------------\n");

	char *dest2 = my_malloc(strlen(src) + 1);
    DBG_PRINT_PTR(dest2);
    print_all_elems();
	printf("-----------------------------------\n");

	my_free(dest1);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");
}

void testfun_2(void)
{
	printf("=====================================================\n");
	dest = my_malloc(strlen(src) + 1);
    DBG_PRINT_PTR(dest);
    print_all_elems();
    PRINTARR(dest, strlen(src));
    strcpy(dest, src);
    PRINTARR(dest, strlen(src));
    printf("%s\n", dest);

	my_free(dest);

	dest = my_calloc(1, strlen(src) + 1);
    print_all_elems();
    PRINTARR(dest, strlen(src));
	printf("-----------------------------------\n");
}

void testfun_3(void)
{
	printf("=====================================================\n");
	dest = my_malloc(4096 - 16 -16);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");
}

void testfun_4(void)
{
	printf("=====================================================\n");
	dest = my_malloc(1);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");
	dest = my_realloc(dest, 2);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");
	dest = my_realloc(NULL, 0);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");
}

void testfun_5(void)
{
	printf("=====================================================\n");
	dest = my_malloc(1);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");
	dest = my_realloc(dest, 20);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");
	dest = my_realloc(dest, 0);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");
	dest = my_realloc(NULL, 10);
    DBG_PRINT_PTR(dest);
    print_all_elems();
	printf("-----------------------------------\n");
}

void testfun_6(void)
{
	printf("=====================================================\n");
	char *dest1 = my_malloc(1);
    DBG_PRINT_PTR(dest1);
    print_all_elems();
	printf("-----------------------------------\n");
	char *dest2 = my_malloc(1);
    DBG_PRINT_PTR(dest2);
    print_all_elems();
	printf("-----------------------------------\n");
	char *dest3 = my_malloc(1);
    DBG_PRINT_PTR(dest3);
    print_all_elems();
	printf("-----------------------------------\n");
    my_free(dest2);
    DBG_PRINT_PTR(dest2);
    print_all_elems();
	printf("-----------------------------------\n");
	char *dest4 = my_realloc(dest1, 10);
    DBG_PRINT_PTR(dest4);
    print_all_elems();
	printf("-----------------------------------\n");
	char *dest5 = my_realloc(dest1, 20);
    DBG_PRINT_PTR(dest5);
    print_all_elems();
	printf("-----------------------------------\n");
	char *dest6 = my_realloc(dest5, 33);
    DBG_PRINT_PTR(dest5);
    print_all_elems();
	printf("-----------------------------------\n");
}

void testfun_7(void)
{
	printf("=====================================================\n");
	char *dest1 = my_malloc(10);
    DBG_PRINT_PTR(dest1);
    print_all_elems();
    strcpy(dest1, "12345");
    DBG_PRINT_STR(dest1);
	printf("-----------------------------------\n");
	char *dest2 = my_malloc(10);
    DBG_PRINT_PTR(dest2);
    print_all_elems();
    DBG_PRINT_STR(dest1);
	printf("-----------------------------------\n");
	char *dest3 = my_realloc(dest1, 20);
    DBG_PRINT_PTR(dest3);
    print_all_elems();
    DBG_PRINT_STR(dest3);
	printf("-----------------------------------\n");
}

void testfun_8(void)
{
	printf("=====================================================\n");
	char *dest1 = my_malloc(4000);
    DBG_PRINT_PTR(dest1);
    print_all_elems();
	printf("-----------------------------------\n");
	char *dest2 = my_malloc(1000);
    DBG_PRINT_PTR(dest2);
    print_all_elems();
	printf("-----------------------------------\n");
}

int main(int argc, char *argv[])
{
    int testnum = 99;
	printf("memblock_info : %lu\n", ALIGN_SIZE(sizeof(memblock_info)));

    if(argc ==2) {
        testnum = atoi(argv[1]);
    }
 
    switch(testnum) {
        DEFTESTCASE(0);
        DEFTESTCASE(1);
        DEFTESTCASE(2);
        DEFTESTCASE(3);
        DEFTESTCASE(4);
        DEFTESTCASE(5);
        DEFTESTCASE(6);
        DEFTESTCASE(7);
        DEFTESTCASE(8);
        default:
            testfun_0();
            testfun_1();
            testfun_2();
            testfun_3();
    }

	return 0;
}