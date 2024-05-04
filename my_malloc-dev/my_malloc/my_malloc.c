#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "my_malloc.h"

memblock_info *head = NULL;
void *last_allocated_addr = NULL;

void make_free_mem_of_allocated_mem(memblock_info *cur, size_t requested_size)
{
    size_t aligned_requested_size = ALIGN_SIZE(requested_size);
    size_t aligned_info_size = ALIGN_SIZE(sizeof(memblock_info));
    size_t remaining_space = GET_SIZE(cur);
	remaining_space -= aligned_requested_size ;

    if(remaining_space >= aligned_info_size) {
        memblock_info *next_block = (memblock_info *)((char *)cur + aligned_info_size + aligned_requested_size);
        next_block->next = cur->next;

        GET_SIZE(next_block) = remaining_space - aligned_info_size;
		SET_UNUSED(next_block);

        cur->next = next_block;
    }
    GET_SIZE(cur) = requested_size;
}

memblock_info *allocate_new_page(size_t size)
{
	size_t aligned_size = ALIGN_SIZE(size);
	size_t aligned_info_size = ALIGN_SIZE(sizeof(memblock_info));
	size_t required_new_size = aligned_info_size + aligned_size;
	
    size_t num_pages = (required_new_size + PAGE_SIZE - 1) / PAGE_SIZE;
    size_t mmap_size = num_pages * PAGE_SIZE;

    memblock_info *new_block = mmap(last_allocated_addr, mmap_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if(new_block == MAP_FAILED) {
        return NULL;
    }

    last_allocated_addr = (char *)new_block + mmap_size;
    if(head == NULL) {
        head = new_block;
    }
    else {
        memblock_info *last = head;

        while (last && last->next) {
            last = last->next;
        }
        last->next = new_block;
    }
    new_block->next = NULL;
    GET_SIZE(new_block) = mmap_size  - ALIGN_SIZE(sizeof(memblock_info));;
	SET_UNUSED(new_block);

    return new_block;
}

void *my_malloc(size_t size)
{
    if(!size) {
        return NULL;
    }
	if(size > MAXMALLOCSIZE) {
		return NULL;
	}

    memblock_info *block = head;
    while(block) {
        if(IS_BLOCK_FREE(block) && GET_SIZE(block) >= size) {
            make_free_mem_of_allocated_mem(block, size);
            break;
        }
        block = block->next;
    }

    if(!block) {
		block = allocate_new_page(size);

		if(!block) {
			return NULL;
		}
		else {
			make_free_mem_of_allocated_mem(block, size);
		}
    }
	
    SET_USED(block);
	return PTR_FOR_USER(block);
}

void my_free(void *ptr)
{
    if(!ptr) {
        return;
    }
    memblock_info *block = PTR_MEMBLOCK_INFO_FROM_USER(ptr);
	GET_SIZE(block) = ALIGN_SIZE(GET_SIZE(block));
	SET_UNUSED(block);

    memblock_info *next_block = block->next;
    if(next_block && IS_BLOCK_FREE(next_block)) {
        GET_SIZE(block) += ALIGN_SIZE(sizeof(memblock_info)) + ALIGN_SIZE(GET_SIZE(next_block));
        block->next = next_block->next;
    }

    memblock_info *prev_block = head;
    if(block != head) {
        while (prev_block->next != block) {
            prev_block = prev_block->next;
        }
        if(IS_BLOCK_FREE(prev_block)) {
            GET_SIZE(prev_block) += ALIGN_SIZE(sizeof(memblock_info)) + GET_SIZE(block);
            prev_block->next = block->next;
        }
    }
}

void *my_calloc(size_t num, size_t size)
{
    size_t total_size = num * size;
    void *ptr = my_malloc(total_size);
	
    if(ptr) {
        memset(ptr, 0, total_size);
    }
	
    return ptr;
}

void *my_realloc(void *ptr, size_t size)
{

    if(!ptr) {
        return my_malloc(size);
    }
    if(size == 0) {
        my_free(ptr);
        return NULL;
    }

    memblock_info *cur_block = PTR_MEMBLOCK_INFO_FROM_USER(ptr);
    if(ALIGN_SIZE(GET_SIZE(cur_block)) >= size) {
		SET_SIZE(cur_block, size);

    	return PTR_FOR_USER(cur_block);
    }

    memblock_info *next_block = cur_block->next;
	if(IS_BLOCK_FREE(next_block)) {
		size_t aligned_cur_block_size = ALIGN_SIZE(GET_SIZE(cur_block));
		size_t aligned_next_block_size = GET_SIZE(next_block) + ALIGN_SIZE(sizeof(memblock_info));
		size_t total_available_size = aligned_cur_block_size + aligned_next_block_size;
		if(total_available_size >= size) {
			cur_block->next = next_block->next;
			GET_SIZE(cur_block) = total_available_size;
            DBG_PRINT_INT(total_available_size);
			make_free_mem_of_allocated_mem(cur_block, size);
			
			return PTR_FOR_USER(cur_block);
		}
	}

    void *new_ptr = my_malloc(size);
    if(!new_ptr) {
		return NULL;
	}
	memcpy(new_ptr, ptr, GET_SIZE(cur_block));
	my_free(ptr);

	return new_ptr;
}

void print_all_elems()
{
	memblock_info *cur = head;
	int count = 0;

#if 1   
	while (cur) {
		printf("memblock_info #%d\n", count);
		printf("  Address: %p\n", (void *)cur);
		printf("  Next: %p\n", (void *)cur->next);
		printf("  Size: %zu(%zu)\n", (size_t)GET_SIZE(cur), (size_t)ALIGN_SIZE((GET_SIZE(cur)) + ALIGN_SIZE(sizeof(memblock_info))));
		printf("  Ptr for the user: %p\n", PTR_FOR_USER(cur));
		printf("  Is free: %s\n", !(IS_BLOCK_FREE(cur)) ? "No" : "Yes");
		printf("\n");

		cur = cur->next;
		count++;
	}
    #endif
}

