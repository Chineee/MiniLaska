cmake_minimum_required(VERSION 3.17)
project(miniLaska_Project C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")

add_executable(miniLaska_Project main.c function_pvp.c function_pvp.h pvp.c pvp.h cpu_bot.c cpu_bot.h board.c
        board.h colors.c colors.h commands.c commands.h)

