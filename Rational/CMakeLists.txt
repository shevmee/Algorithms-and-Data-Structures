cmake_minimum_required(VERSION 3.10)

project(Rational VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main main.cpp Rational.cpp)

target_compile_options(main PRIVATE -std=c++20)