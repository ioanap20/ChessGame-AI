cmake_minimum_required(VERSION 3.10)

project(chess_proj
  VERSION 1.0
  LANGUAGES CXX)

include_directories(.)

#add_library(myLibExample main.cpp)

add_executable(chess_proj reading.cpp)

target_link_libraries(chess_proj PRIVATE)