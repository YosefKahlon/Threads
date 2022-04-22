//
// Created by 97252 on 4/22/2022.
//

#ifndef THREADS_MALLOC_H
#define THREADS_MALLOC_H


struct block_meta {
    size_t size;
    struct block_meta *next;
    int free;
    int magic; // For debugging only. TODO: remove this in non-debug mode.
};

struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *request_space(struct block_meta* last, size_t size);
void *my_malloc(size_t size);
struct block_meta *get_block_ptr(void *ptr);
void my_free(void *ptr);



#endif //THREADS_MALLOC_H
