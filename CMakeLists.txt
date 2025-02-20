cmake_minimum_required(VERSION 3.16)

project(calc_core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES calculator.h converter.h calculator.cpp converter.cpp node.h node.cpp lexer.h parser.h)

list(APPEND CMAKE_CXX_FLAGS "-Wall -Werror -Wsign-compare")

add_library(calc_core STATIC ${SOURCE_FILES})

