//
// Created by 97252 on 4/22/2022.
//

#ifndef THREADS_QUEUE_HPP
#define THREADS_QUEUE_HPP

#include "stack.h"
#include "malloc.h"
//#include "malloc.c"


typedef struct Queue {
    char data[text_length];
    node *head;
    int size;

} Queue;

void enqueue(Queue** queue , char* text);

void dequeue(Queue**  queue);

char* peek(Queue**  queue);

void print_queue(Queue** queue);

void free_queue(Queue** queue);

#endif //THREADS_QUEUE_HPP
