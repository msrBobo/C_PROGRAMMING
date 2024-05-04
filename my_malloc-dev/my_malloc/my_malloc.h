#ifndef MY_MALLOC_H
#define MY_MALLOC_H
#pragma once
#include <unistd.h>

#define ALIGNMENT 16
#define PAGE_SIZE 4096
#define MAXMALLOCSIZE 16711568

typedef struct memblock_info {
    struct memblock_info *next;
	struct {
		size_t used_size:63;
		size_t used:1;
	} s_size;
} memblock_info;


#define SET_USED(b) (b)->s_size.used = 1
#define SET_UNUSED(b) (b)->s_size.used = 0

#define GET_SIZE(b) ((b)->s_size.used_size)
#define SET_SIZE(b, s) (b)->s_size.used_size = (s)

#define IS_BLOCK_FREE(b) ((b)->s_size.used == 0)
#define USEDMASK 0x8000000000000000

#define ALIGN_SIZE(s) (size_t)(((s) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#define PTR_FOR_USER(b) ((char *)(b) + ALIGN_SIZE(sizeof(memblock_info)))

#define PTR_MEMBLOCK_INFO_FROM_USER(p) ((memblock_info *)((char *)(p) - ALIGN_SIZE(sizeof(memblock_info))))

void *my_malloc(size_t size);
void my_free(void *ptr);
void *my_calloc(size_t num, size_t size);
void *my_realloc(void *ptr, size_t size);

void print_all_elems();

#define DBG_FUNLINE() printf("%s %d \n",__FUNCTION__, __LINE__);
#define DBG_PRINT_PTR(v) printf(#v" = %p\n", v)
#define DBG_PRINT_INT(v) printf(#v" = %ld\n", v)
#define DBG_PRINT_STR(v) printf(#v" = %s\n", v)

#endif  // MY_MALLOC
