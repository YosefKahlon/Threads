CC = clang++



all: server client stack.o

server: server.o stack.h
	$(CC) -o server server.o -lpthread

stack: stack.o
	$(CC) -o stack stack.o

stack.o: stack.c stack.h
	$(CC) -c stack.c

server.o: server.cpp stack.h
	$(CC) -c server.cpp


client: client.cpp
	$(CC) client.cpp -o client

clean:
	rm -f *.o server client stack