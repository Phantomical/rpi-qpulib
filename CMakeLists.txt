
cmake_minimum_required(VERSION 3.1)

project(qpu-asm)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(libdis)
add_subdirectory(qpu-dis)

add_subdirectory(qpu-lib)


