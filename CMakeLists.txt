cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_FLAGS "-std=c++20")

project(chess_and_the_city
  VERSION 1.0
  LANGUAGES CXX)


add_library(lib_chess_and_the_city
  reading.cpp
  chess_board.cpp
  piece.cpp
  algo.cpp
  castling.cpp
  check.cpp
  promotion.cpp
  en_passant.cpp
)

add_executable(chess_and_the_city
  main.cpp
)

target_link_libraries(chess_and_the_city PRIVATE lib_chess_and_the_city)
