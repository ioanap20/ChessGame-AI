cmake_minimum_required(VERSION 3.10)

project(King_moves
  VERSION 1.0
  LANGUAGES CXX)

include_directories(.)

add_library(myLibExample reading.cpp)

add_executable(King_moves main.cpp)

#target_link_libraries(chess_proj PRIVATE myLibExample)