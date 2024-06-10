cmake_minimum_required(VERSION 3.28)
project(SplayTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(SplayTree main.cpp
        splay_tree.h)

set(SANITIZER_FLAGS "-fsanitize=address,undefined,leak")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
