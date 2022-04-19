//
// Created by 97252 on 4/19/2022.
//

#ifndef THREADS_STACK_H
#define THREADS_STACK_H

#define text_length 1024


typedef struct node {
    char* data;
    struct node *next;
} node;


typedef struct stack{
    node* head;
    int size;
} Stack;

void printStack(Stack** s);

char*top(Stack** stack);

void push(node** top ,char* text);

void pop(Stack** stack);
#endif //THREADS_STACK_H
