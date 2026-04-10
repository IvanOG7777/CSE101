cmake_minimum_required(VERSION 3.28)
project(CSE101 C)

set(CMAKE_C_STANDARD 17)

include_directories(pa2)

#add_executable(ListTest
#        pa1/List.h
#        pa1/List.c
#        pa1/ListTest.c
#)
#
#add_executable(Words
#        pa1/List.h
#        pa1/List.c
#        pa1/Words.c
#)

add_executable(GraphTest
        pa2/Graph.h
        pa2/Graph.c
        pa2/List.c
        pa2/List.h
        pa2/GraphTest.c
)
add_executable(FindPath
        pa2/Graph.h
        pa2/Graph.c
        pa2/List.c
        pa2/List.h
        pa2/FindPath.c
)
