cmake_minimum_required(VERSION 3.21)
project(adc_coursework C)

set(CMAKE_C_STANDARD 99)

add_executable(adc_coursework main.c adc.h adc.c io.h io.c stats.h stats.c)
