# Threads

ID: 209011840 ID: 206795841

This project represent a shared Stack/Queue using multi-threaded system
over Server/Client .

Here is the instruction of how to use:

- Before you start
<div dir='ltr'>

    make all
    ./server
    ./client localhost
</div>

The main goal is to understand how the OS implements malloc and free on multi-threaded system and how we implement mutexes.




### Implement a multi-threaded lock free stack using POSIX methods


PUSH will push <text> into the stack.

POP will pop text from the stack.

TOP will display (output) the stack top.

EXIT kill this dialog with the server.

### Implement a multi-threaded lock free queue using POSIX methods

ENQUEUE <text>\n: insert to the tail. (Otherwise same as PUSH)

DEQUEUE\n: remove the tail. (Otherwise same as POP)

PEEK will display (output) the queue top.

EXIT kill this dialog with the server.


### Server
Server, open socket and listen for up to 10 client (multi-threads)
The server handles the client request for a stack / queue
Using mutex to synchronize between the client.

### client
Client, send request to server to use stack / queue.



### how to use :

open terminal for the server and run it with ./server
open few more terminals for client ./client localhost
now in the client terminal write the command in uppercase and wait for the server response.
