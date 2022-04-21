//
// Created by 97252 on 4/19/2022.
//

#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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
    } else {
        node *top = (*stack)->head;
        (*stack)->head = (*stack)->head->next;
        free(top);
    }
    (*stack)->size--;
}

char *top(Stack **stack) {
    if ((*stack)->size == 0) {
        perror("ERROR: Stack is empty");
        return "ERROR: Stack is empty";
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
//    Stack *s = (Stack *) malloc(sizeof(Stack));
//    s->head = NULL;
//
//    push(&s, "ok");
//    push(&s,"bye");
//    printStack(&s);
//
//    free_stack(&s);
//
//    return 0;
//
//}