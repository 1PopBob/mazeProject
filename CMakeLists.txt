cmake_minimum_required(VERSION 3.23)
project(PA3)

set(CMAKE_CXX_STANDARD 14)

add_executable(PA3 main.cpp)
add_executable(maze maze.cpp mazeio.cpp mazeio.h)
add_executable(queue_test queue_test.cpp queue.cpp queue.h)