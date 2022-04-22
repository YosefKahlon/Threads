cmake_minimum_required(VERSION 3.16)
project(Threads C)

set(CMAKE_C_STANDARD 11)

add_executable(Threads
        stack.h stack.c client.c server.c queue.h queue.c test.c)
