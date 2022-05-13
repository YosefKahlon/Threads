//
// Created by barak on 15/04/2022.
//

//
// Created by 97252 on 4/14/2022.
//

/*
** server.c -- a stream socket server demo
*/
#define EQUAL 0

#include <stdio.h>
#include "stack.h"
//#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "stack.c"
#include "queue.h"
#include "queue.c"
#include "assert.h"

#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10     // how many pending connections queue will hold
Stack *shared_st;
Stack *test_st;
Queue *shared_qu;
int server_running = 1;
int sockfd;
int new_fd[BACKLOG];

/* Stack Thread safety handlers */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t con_top = PTHREAD_COND_INITIALIZER;
pthread_cond_t con_pop = PTHREAD_COND_INITIALIZER;
pthread_cond_t con_push = PTHREAD_COND_INITIALIZER;
int resource_counter = 0;

/* Queue Thread safety handlers */
pthread_mutex_t q_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t con_peek = PTHREAD_COND_INITIALIZER;
pthread_cond_t con_dequeue = PTHREAD_COND_INITIALIZER;
pthread_cond_t con_enqueue = PTHREAD_COND_INITIALIZER;
int queue_resource_counter = 0;

int test() {

    test_st = (Stack *) malloc(sizeof(Stack));

    /* checking allocation correctness */
    void * new_address= sbrk(0);
    assert((int *)test_st != (int *)new_address);

    printf("Passed Allocation tests\n");
    /* push one string to stack.
     * check if the top of the stack matches the last value pushed, expected --> "test1"*/
    push(&test_st, "test1");
    assert(strcmp(top(&test_st), "test1") == 0);
    /* push another string to the stack.
     * check if the top value updated, expected --> "test2".
     * check if the size updated, expected --> 2.*/
    push(&test_st, "test2");
    assert(test_st->size == 2);
    assert(strcmp(top(&test_st), "test2") == 0);


    /* POP until stack is empty
     * check size, expected --> 0
     * check top on empty stack, expected --> ERROR message on empty stack*/
    pop(&test_st);
    pop(&test_st);
    assert(test_st->size == 0);
    assert(strcmp(top(&test_st),"ERROR: Stack is empty") == EQUAL);

    /* check case when call pop on empty stack,
     * expected --> no change on stack, return string with ERROR prefix*/
    pop(&test_st);
    assert(test_st->size == 0);
    assert(strcmp(top(&test_st),"ERROR: Stack is empty") == EQUAL);

    free_stack(&test_st);
    printf("Passed all stack tests.\n");
    printf("server initializing...\n");
    return 1;
}

void sig_handler(int signum) {
    free_stack(&shared_st);
    free_queue(&shared_qu);
    server_running = 0;
    for (int i = 1; i < BACKLOG; ++i) {
        close(new_fd[i]);
    }
    close(sockfd);


        //destroy the lock
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&q_mutex);
        //destroy the pthread conditions
    pthread_cond_destroy(&con_push);
    pthread_cond_destroy(&con_top);
    pthread_cond_destroy(&con_pop);
    pthread_cond_destroy(&con_peek);
    pthread_cond_destroy(&con_dequeue);
    pthread_cond_destroy(&con_enqueue);

    exit(1);
}

void sigchld_handler(int s) {
    (void) s; // quiet unused variable warning

    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

void *send_hello(void *arg) {
    int *s = (int *) arg;
    if (send(*s, "Hello, world!", 13, 0) == -1) {
        perror("send");
    }
    return 0;
}

void *server_listener(void *arg) {
    pthread_detach(pthread_self());
    int *s = (int *) arg;
    if (send(*s, "Hello, world!", 13, 0) == -1) {
        perror("send");
    }
    char client_msg[text_length] = {0}; // '\0'

    while (1) {
        memset(client_msg, 0, text_length);
        size_t r;
        if ((r = recv(*s, client_msg, sizeof(client_msg), 0)) == -1) {
            perror("recv");
            exit(1);
        }
        if (r != 0) {

            /** --------------------------------- STACK SECTION ---------------------------------*/

            /**------------ TOP ------------*/
            /* if the given command is TOP, the server will send the client the top value in the shared stack.*/
            if (strcmp("TOP", client_msg) == EQUAL) {
                pthread_mutex_lock(&mutex); // lock the stack
                while (resource_counter < 0) {
                    printf("Waiting On READ DATA\n");
                    pthread_cond_wait(&con_top, &mutex);
                }
                resource_counter++;
                pthread_mutex_unlock(&mutex);

                /* ~START~ READ DATA CRITICAL SECTION */

                printf("READER NUM: %d\n", resource_counter);
                char *buff = top(&shared_st);
                if (send(*s, buff, strlen(buff), 0) == -1) {
                    perror("send");
                }
                /* ~END~ READ DATA CRITICAL SECTION */

                pthread_mutex_lock(&mutex);
                printf("finish READER NUM: %d\n", resource_counter);
                resource_counter--;
                if (resource_counter == 0) {
                    pthread_cond_signal(&con_pop);
                    pthread_cond_signal(&con_push);
                }
                pthread_mutex_unlock(&mutex); //unlock the stack
            }
                /**------------ POP ------------*/
                /* if the given command is POP, the server will pop the top value in the shared stack */
            else if (strcmp("POP", client_msg) == EQUAL) {

                pthread_mutex_lock(&mutex); // lock the stack
                while (resource_counter != 0) {
                    printf("Waiting on POP DATA\n");
                    pthread_cond_wait(&con_pop, &mutex);
                }
                resource_counter = -1;
                pthread_mutex_unlock(&mutex);

                /* ~START~ Delete DATA CRITICAL SECTION */

                printf("POPING\n");
                pop(&shared_st);
                /* ~END~ Delete DATA CRITICAL SECTION */

                pthread_mutex_lock(&mutex); // lock the mutex

                resource_counter = 0;
                pthread_cond_broadcast(&con_top);
                pthread_cond_signal(&con_pop);
                pthread_cond_signal(&con_push);

                pthread_mutex_unlock(&mutex); //unlock the stack
            }
                /**------------ PUSH ------------*/
                /* if the given command is PUSH,
                 * the server will push the attached text after the command to the shared stack.*/
            else if (strncmp("PUSH", client_msg, 4) == EQUAL) {
                pthread_mutex_lock(&mutex); // lock the stack
                while (resource_counter != 0) {
                    printf("waiting on push data\n");
                    pthread_cond_wait(&con_push, &mutex);
                }
                resource_counter = -2;

                pthread_mutex_unlock(&mutex);

                /* ~START~ Write DATA CRITICAL SECTION */

                printf("WRITING DATA\n");
                char text[text_length];
                strncpy(text, client_msg + 5, strlen(client_msg) - 4);
                push(&shared_st, text);
                /* ~END~ Write DATA CRITICAL SECTION */

                pthread_mutex_lock(&mutex);
                resource_counter = 0;
                // notify all other waiting threads
                pthread_cond_broadcast(&con_top);
                pthread_cond_signal(&con_pop);
                pthread_cond_signal(&con_push);

                pthread_mutex_unlock(&mutex); //unlock the stack
            }

            /** --------------------------------- QUEUE SECTION ---------------------------------*/

            /**------------ PEEK ------------*/
            /* if the given command is PEEK, the server will send the client the first value in the shared Queue.*/
            if (strcmp("PEEK", client_msg) == EQUAL) {
                pthread_mutex_lock(&q_mutex); // lock the Queue
                while (queue_resource_counter < 0) {
                    printf("Waiting On READ DATA\n");
                    pthread_cond_wait(&con_peek, &q_mutex);
                }
                queue_resource_counter++;
                pthread_mutex_unlock(&q_mutex);

                /* ~START~ READ DATA CRITICAL SECTION */

                printf("READER NUM: %d\n", queue_resource_counter);
                char *buff = peek(&shared_qu);
                if (send(*s, buff, strlen(buff), 0) == -1) {
                    perror("send");
                }
                /* ~END~ READ DATA CRITICAL SECTION */

                pthread_mutex_lock(&q_mutex);
                printf("finish READER NUM: %d\n", queue_resource_counter);
                queue_resource_counter--;
                if (queue_resource_counter == 0) {
                    pthread_cond_signal(&con_enqueue);
                    pthread_cond_signal(&con_dequeue);
                }
                pthread_mutex_unlock(&q_mutex); //unlock the Queue
            }
                /**------------ Dequeue ------------*/
                /* if the given command is Dequeue, the server will delete the first value in the shared Queue */
            else if (strcmp("DEQUEUE", client_msg) == EQUAL) {

                pthread_mutex_lock(&q_mutex); // lock the Queue
                while (queue_resource_counter != 0) {
                    printf("Waiting on DEQUEUE DATA\n");
                    pthread_cond_wait(&con_dequeue, &q_mutex);
                }
                queue_resource_counter = -1;
                pthread_mutex_unlock(&q_mutex);

                /* ~START~ Delete DATA CRITICAL SECTION */

                printf("DEQUEUING\n");
                dequeue(&shared_qu);
                /* ~END~ Delete DATA CRITICAL SECTION */

                pthread_mutex_lock(&q_mutex); // lock the mutex

                queue_resource_counter = 0;
                pthread_cond_broadcast(&con_peek);
                pthread_cond_signal(&con_dequeue);
                pthread_cond_signal(&con_enqueue);

                pthread_mutex_unlock(&q_mutex); //unlock the Queue
            }

                /**------------ Enqueue ------------*/
                /* if the given command is ENQUEUE,
                 * the server will Poll the attached text after the command to the shared Queue.*/
            else if (strncmp("ENQUEUE", client_msg, 7) == EQUAL) {
                pthread_mutex_lock(&q_mutex); // lock the Queue
                while (queue_resource_counter != 0) {
                    printf("waiting on enqueue data\n");
                    pthread_cond_wait(&con_enqueue, &q_mutex);
                }
                queue_resource_counter = -2;

                pthread_mutex_unlock(&q_mutex);

                /* ~START~ Write DATA CRITICAL SECTION */

                printf("WRITING QUEUE DATA\n");
                char text[text_length];
                strncpy(text, client_msg + 8, strlen(client_msg) - 7);
                enqueue(&shared_qu, text);
                /* ~END~ Write DATA CRITICAL SECTION */

                pthread_mutex_lock(&q_mutex);
                queue_resource_counter = 0;
                // notify all other waiting threads
                pthread_cond_broadcast(&con_peek);
                pthread_cond_signal(&con_dequeue);
                pthread_cond_signal(&con_enqueue);

                pthread_mutex_unlock(&q_mutex); //unlock the Queue
            }
        } else {
            break;
        }
    }
}


int main(void) {
    int test_status = test();
    /* INIT the server shared stack */
    shared_st = (Stack *) malloc(sizeof(Stack));
    shared_st->head = NULL;

    shared_qu = (Queue *) malloc(sizeof(Queue));
    shared_qu->head = NULL;


    int status;

    /* Connection methods start here -> */
    // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        printf(" hello from PID: %d\n", getpid());
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    signal(SIGINT, sig_handler);

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    /* initializing array of threads with size of 10(the max of concurrency clients).
     * also init unsigned long thread_num to be the index of each thread
     * that will serve the current connection with the client*/
    pthread_t client_h[BACKLOG];
    unsigned long thread_num = 1;

    while (server_running) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd[thread_num] = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
        if (new_fd[thread_num] == -1) {
            perror("accept");
            continue;
        }


        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *) &their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        /* in case we had more that 10 clients total(not at the same time) we can go point back to the previous threads
         * by module the curr index with backlog.*/
        thread_num %= BACKLOG;
        printf("SOCK NUM : %d\n", new_fd[thread_num]);
        /*create new executable thread to handle the connection with the client (to reply hello world...)*/

        pthread_create(&client_h[thread_num], NULL, &server_listener, &new_fd[thread_num]);
        /* increasing the counter for next pthread in the queue*/
        thread_num++;
    }
//    free_stack(&shared_st);




    wait(&status);
//    close(new_fd);

    return 0;
}
