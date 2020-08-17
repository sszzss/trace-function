cmake_minimum_required(VERSION 3.17)

project(trace_function VERSION 1.0.0)

add_executable(trace draw.c stack.c symbols.c trace.c)

add_subdirectory(sample)