cmake_minimum_required(VERSION 3.3)
project(Functors)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Werror -pedantic")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
#set(CMAKE_CXX_FLAGS_RELEASE "-O0 -ggdb")

add_executable(test_functors test_functors.cc)
