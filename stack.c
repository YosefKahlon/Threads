//
// Created by 97252 on 4/19/2022.
//

#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include "malloc.h"
//#include "malloc.c"


void push(Stack **stack, char *text) {
    /*old malloc */
//    node *new_node = (node *) malloc(sizeof(node));
    /*new malloc*/
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
//        printf("Empty stack \n");
        return;
    }

    if ((*stack)->head->next == NULL) {
        /*old free*/
//        free((*stack)->head);
        /*new free*/
        free((*stack)->head);
        (*stack)->head = NULL;
    } else {
        node *top = (*stack)->head;
        (*stack)->head = (*stack)->head->next;
        /*old free*/
//        free(top);
        /*new free*/
        free(top);
    }
    (*stack)->size--;
}

char *top(Stack **stack) {
    if((*stack)->size == 0){
//        perror("ERROR: Stack is empty");
        return "ERROR: Stack is empty";
    }
    return (*stack)->head->data;
}

void free_stack(Stack **stack) {

    while ((*stack)->size != 0) {
        pop(stack);
    }
    /*old free*/
//    free((*stack));
    /*new free*/
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
//    Stack *new_n = (Stack *) malloc(sizeof(Stack));
//    new_n->head = (node *) malloc(sizeof(node));
//    new_n->head->next = NULL;
//    strcpy(new_n->head->data, "ddd");
//
//    printf("data %s \n", new_n->head->data);
//    node *p = new_n->head;
//    //free(new_n->head);
//
//
//
//    printf("data %s \n", p->data);
//    new_n->head = (node *) malloc(sizeof(node));
//    strcpy(new_n->head->data, "test");
//
//
//
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