#include "stdio.h"
#include "stack.h"
#include "stdlib.h"


void init(node **pNode);

int main() {

    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->head = NULL;

    node a, b, c;
    a.data = "hello";
    b.data = "world";
    c.data = "yes";
//    s->head = &a;
////    a.next = &b;
////    b.next = &c;
//    a.next = NULL;


    // s->head = NULL;


    push(&s->head,"ok");
    push(&s->head,"bye");
   // printStack(&s);
   // pop(&s);
    printf( "%s \n", top(&s));
    //printStack(&s);
    return 0;

}

