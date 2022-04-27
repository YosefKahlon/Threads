//
// Created by 97252 on 4/22/2022.
//

#include "queue.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "malloc.c"

void enqueue(Queue **queue, char *text) {
    /* old malloc */
//    node *new_node = (node *) malloc(sizeof(node));
    /* new malloc */
    node *new_node = (node *) my_malloc(sizeof(node));
    strcpy(new_node->data, text);

    if ((*queue)->head == NULL) {
        (*queue)->head = new_node;

    } else {
        node *last = (*queue)->head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_node;
    }
    new_node->next = NULL;
    (*queue)->size++;


}

void dequeue(Queue **queue){
    if((*queue)->size == 0){
        perror("ERROR: Queue is empty");
        return;
    }

    node* top = (*queue)->head;
    (*queue)->head = (*queue)->head->next;
    /* old free */
//    free(top);
    /* new free */
    my_free(top);
    (*queue)->size--;

}

char *peek(Queue **queue){
    if((*queue)->size == 0){
        perror("ERROR: Queue is empty");
        return "ERROR: Queue is empty";
    }

    return (*queue)->head->data;
}

void print_queue(Queue **queue) {

    for (node *i = (*queue)->head; i != NULL; i = i->next) {
        printf("%s --> ", i->data);
    }
    printf("\n");
}

void free_queue(Queue** queue){
    while ((*queue)->size != 0) {
        dequeue(queue);
    }
    /* old free */
//    free((*queue));
    /* new free */
    my_free((*queue));
}


//int main() {
//
//    Queue *queue = (Queue *) malloc(sizeof(Queue));
//    queue->head = NULL;
//    enqeue(&queue, "hello");
//    enqeue(&queue, "hi");
//    enqeue(&queue, "bye");
//
//    printf("%s\n", top_q(&queue));
//
//    print_queue(&queue);
//    free_queue(&queue);
//}

