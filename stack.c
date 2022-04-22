//
// Created by 97252 on 4/19/2022.
//

#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>


//void *my_malloc(size_t size) {
//    printf("address %zu \n", size);
//    void *memory;
//    node *new_node;
//    memory = sbrk((sizeof(size)));
//    printf("address %p \n", memory);
//    return memory;
//}
//
//void* my_free(size_t size){
//
//
//
//
//}


void push(Stack **stack, char *text) {
    node *new_node = (node *) malloc(sizeof(node));
    strcpy(new_node->data, text);

    if ((*stack)->head == NULL) {
        (*stack)->head = new_node;
        new_node->next = NULL;

    } else {
        new_node->next = (*stack)->head;
        (*stack)->head = new_node;
    }
    (*stack)->size++;

}


void pop(Stack **stack) {
    if ((*stack)->head == NULL) {
        printf("Empty stack \n");
        return;
    }

    if ((*stack)->head->next == NULL) {
        free((*stack)->head);
        (*stack)->head = NULL;
    } else {
        node *top = (*stack)->head;
        (*stack)->head = (*stack)->head->next;
        free(top);
    }
    (*stack)->size--;
}

char *top(Stack **stack) {
    if ((*stack)->size == 0) {

    }
    return (*stack)->head->data;
}

void free_stack(Stack **stack) {

    while ((*stack)->size != 0) {
        pop(stack);
    }

    free((*stack));
}

void printStack(Stack **stack) {
    for (node *i = (*stack)->head; i != NULL; i = i->next) {
        printf("%s --> ", i->data);
    }
    printf("\n");
}


//int main() {
//
//
//    Stack *new_n = (Stack *) my_malloc(sizeof(Stack));
//   // new_n->head = (node *) my_malloc(sizeof(node));
//    // new_n->head->next = NULL;
//    //strcpy(new_n->head->data, "ddd");
//
//    //printf("data %s \n", new_n->head->data);
////    Stack *s = (Stack *) malloc(sizeof(Stack));
////    s->head = NULL;
////
////    push(&s, "ok");
////    push(&s,"bye");
////    printStack(&s);
////
////    free_stack(&s);
//
//    return 0;
//
//}