cmake_minimum_required(VERSION 3.17)
project(Maze_Example)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Maze_Example MazeExample.cpp)