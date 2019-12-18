cmake_minimum_required(VERSION 3.15)
project(NERC_NF)

add_compile_options(-DLOCAL)
set(CMAKE_CXX_STANDARD 17)

add_executable(NERC_NF main.cpp)