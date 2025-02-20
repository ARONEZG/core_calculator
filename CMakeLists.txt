cmake_minimum_required(VERSION 3.16)

project(calc_core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES calculator.h converter.h calculator.cpp converter.cpp main.cpp node.h node.cpp lexer.h parser.h)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

list(APPEND CMAKE_CXX_FLAGS "-Wall -Werror -Wsign-compare")

add_executable(calc_core ${SOURCE_FILES})

target_link_libraries(calc_core PRIVATE Qt6::Core)
