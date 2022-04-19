//
// Created by 97252 on 4/19/2022.
//

#include "stack.h"
#include "stdio.h"
#include "stdlib.h"

void push(node **head, char *text) {

    node *new_node = (node *) malloc(sizeof(node));
    new_node->data = (char *) malloc(text_length);
    new_node->data = text;

    new_node->next = NULL;
    if((*head) == NULL){
         // new_node->next = (*head);
        (*head) = new_node;


    }else {
        (*head)->next = new_node;
    }


}
 void pop(Stack** stack){
    node *temp= (*stack)->head;
    node *prev =(*stack)->head;
    while (temp != NULL ){
        temp = temp->next;
    }

    free(temp);
}

char*top(Stack** stack){
    node *temp= (*stack)->head;
    while (temp->next != NULL ){
        temp = temp->next;
    }

    return temp->data;
}

void printStack(Stack **stack) {
    for (node *i = (*stack)->head; i != NULL; i = i->next) {
        printf("%s --> ", i->data);
    }

}