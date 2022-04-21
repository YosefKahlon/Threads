//
// Created by 97252 on 4/14/2022.
//

/*
** client.c -- a stream socket client demo
*/

#define EQUAL 0

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define PORT "3490" // the port client will be connecting to

#define MAXDATASIZE 100 // max number of bytes we can get at once

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int desc = dup(1); // close stout
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("client: received '%s'\n",buf);



    dup2(sockfd,1);
    while (1) {
        char *command = NULL;

        size_t size = 0;

        //s-size_t type to be able to receive value -1 // size of the input  line
        ssize_t line_size = getline(&command, &size, stdin);
        command[line_size - 1] = '\0';
        if(strcmp("EXIT", command) == EQUAL) {
            break;
        }
        if (strcmp("TOP", command) == EQUAL) {
//            printf("%s", command);

            /* send the TOP command to the server */
            send(sockfd,command,1024,0);
            char top[1024];
            size_t numb;
            dup2(desc,1);

            /* recieve the top stack value from server shared stack.
             * IN CASE of empty stack -> return ERROR reply */
            if ((numb = recv(sockfd, top, 1024, 0)) == -1) {
                perror("recv");
                exit(1);
            }
            top[numb] = '\0';

            /* check if the reply is an error or valid output (for prefix management)*/
            if (strncmp("ERROR", top,  5) == EQUAL) {
                printf("%s\n", top);
            } else {
                printf("OUTPUT: %s\n", top);
            }
        }
        else if (strcmp("POP", command) == EQUAL || strncmp("PUSH",command, 4) == EQUAL) {
            send(sockfd,command,1024,0);
        }
    }

    close(sockfd);

    return 0;
}
