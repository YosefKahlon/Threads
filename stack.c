//
// Created by 97252 on 4/19/2022.
//

#include "stack.h"
#include "stdio.h"
#include "stdlib.h"

void push(Stack **stack, char *text) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->data = (char *) malloc(text_length);
    new_node->data = text;


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
    node *top = (*stack)->head;
    (*stack)->head = (*stack)->head->next;
    free(top);
}

char *top(Stack **stack) {
    return (*stack)->head->data;
}

void free_stack(Stack **stack) {

//    while ((*stack)->size != 0 ) {
//        pop(stack);
//        (*stack)->size--;
//    }
//    free((*stack)->head->next);
//
//    free((*stack)->head);
//    free((*stack));
    free(stack);
}

void printStack(Stack **stack) {
    for (node *i = (*stack)->head; i != NULL; i = i->next) {
        printf("%s --> ", i->data);
    }
    printf("\n");
}


int main() {

    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->head = NULL;

//    push(&s,"ok");
//    push(&s,"bye");
//    printStack(&s);

    free_stack(&s);

    return 0;

}