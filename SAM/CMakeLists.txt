cmake_minimum_required(VERSION 3.14)
project(SAM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static -D LOCAL")

add_executable(SAM main.cpp)