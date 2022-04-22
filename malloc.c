//
// Created by 97252 on 4/22/2022.
//
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "malloc.h"

//top of the memory heap
void *global_base = NULL;

#define META_SIZE sizeof(struct block_meta)


/**
 *
 *  For our malloc, we'll want to re-use free space if possible, allocating space when we can't re-use existing space.
 *  Given that we have this linked list structure, checking if we have a free block and returning it is straightforward.
 *  When we get a request of some size, we iterate through our linked list to see if there's a free block that's large enough.
 *
 */
struct block_meta *find_free_block(struct block_meta **last, size_t size) {
    struct block_meta *current = global_base;
    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

/**
 *
 * Method to ask for space in the linked list :
 *
 * if we don't find a free block, we'll have to request space
 * from the OS using sbrk and add our new block to the end of the linked list.
 *
 */
struct block_meta *request_space(struct block_meta *last, size_t size) {
    struct block_meta *block;
    block = sbrk(0);
    void *request = sbrk(size + META_SIZE);
    assert((void *) block == request); // Not thread safe.
    if (request == (void *) -1) {
        return NULL; // sbrk failed.
    }

    if (last) { // NULL on first request.
        last->next = block;
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;
    return block;
}

/**
 * Method to ask for for memory from the heap using sbrk
 *
 If our global base pointer is NULL, we need to request space and
 set the base pointer to our new block. If it's not NULL,
 we check to see if we can re-use any existing space.
 If we can, then we do;
 if we can't, then we request space and use the new space.
 */
void *my_malloc(size_t size) {
    struct block_meta *block;

    if (size <= 0) {
        return NULL;
    }

    if (!global_base) { // First call.
        block = request_space(NULL, size);
        if (!block) {
            return NULL;
        }
        global_base = block;
    } else {
        struct block_meta *last = global_base;
        block = find_free_block(&last, size);
        if (!block) { // Failed to find free block.
            block = request_space(last, size);
            if (!block) {
                return NULL;
            }
        } else {      // Found free block
            block->free = 0;

        }
    }

    return (block + 1);
}

/**
 * Method to get the address of our struct in multiple places in our code.
 */
struct block_meta *get_block_ptr(void *ptr) {
    return (struct block_meta *) ptr - 1;
}


/**
 * Free - let as to use memory from the heap again after finish .
 * by using a linked list to save free block after we used them .
 *
 */
void my_free(void *ptr) {
    if (!ptr) {
        return;
    }

    struct block_meta *block_ptr = get_block_ptr(ptr);
    assert(block_ptr->free == 0);
    block_ptr->free = 1;

}






void *my_realloc(void *ptr, size_t size) {
    if (!ptr) {
        // NULL ptr. realloc should act like malloc.
        return my_malloc(size);
    }

    struct block_meta *block_ptr = get_block_ptr(ptr);
    if (block_ptr->size >= size) {
        // We have enough space. Could free some once we implement split.
        return ptr;
    }

    // Need to really realloc. Malloc new space and free old space.
    // Then copy old data to new space.
    void *new_ptr;
    new_ptr = my_malloc(size);
    if (!new_ptr) {
        return NULL;
    }
    memcpy(new_ptr, ptr, block_ptr->size);
    my_free(ptr);
    return new_ptr;
}


/**
 *
 * Calloc is just malloc that initializes the memory to 0
 */
void *my_calloc(size_t nelem, size_t elsize) {
    size_t size = nelem * elsize;
    void *ptr = my_malloc(size);
    memset(ptr, 0, size);
    return ptr;
}




/* Resources https://danluu.com/malloc-tutorial/ */