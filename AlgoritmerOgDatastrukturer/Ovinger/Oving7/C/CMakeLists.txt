cmake_minimum_required(VERSION 3.26)
project(Oppgave1 C)

set(CMAKE_C_STANDARD 17)

add_executable(Oppgave1 main.c
        weightedgraph.h
        test.c)
