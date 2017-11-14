cmake_minimum_required(VERSION 3.8)
project(cs450_hw3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        boardvalidate.c
        boardvalidate.h
        chan.c
        chan.h
        main.c
        makefile
        parsetools.c
        parsetools.h
        queue.c
        queue.h)

add_executable(cs450_hw3 ${SOURCE_FILES})