cmake_minimum_required(VERSION 3.11)
project(allocatorLT)

set(CMAKE_CXX_STANDARD 14)

add_executable(allocatorLT main.cpp allocator.cpp allocator.h dl_list.h tests.cpp tests.h)