//
// Created by 97252 on 4/22/2022.
//

#ifndef THREADS_MALLOC_H
#define THREADS_MALLOC_H
#include <stddef.h>

struct block_meta {
    size_t size;
    struct block_meta *next;
    int free;
};

struct block_meta *search_for_free_block(struct block_meta **last, size_t size);
struct block_meta *ask_for_space(struct block_meta* last, size_t size);
void *malloc(size_t size);
struct block_meta *get_block_pointer(void *ptr);
void free(void *ptr);
void *calloc(size_t nelem, size_t elsize);
void *realloc(void *ptr, size_t size);


#endif //THREADS_MALLOC_H
